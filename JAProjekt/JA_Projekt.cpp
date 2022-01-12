#include "JA_Projekt.h"

typedef void (*func) (unsigned char*, unsigned char*, int, int, int, int);

unsigned int set_threads_count()
{
	const unsigned int processor_count = std::thread::hardware_concurrency();
	unsigned int threads_count = 0;
	std::string line;
	std::cout << "Twoj procesor obsluguje " << processor_count << " watkow." << std::endl;
	std::cout << "Wybierz ilosc watkow: ";
	while (true)
	{
		std::getline(std::cin, line);
		if (!line.empty())
		{
			std::stringstream s(line);
			if (s >> threads_count && s.eof() && (threads_count >= 1 && threads_count <= 64))
				break;
		}
		std::cout << "Niepoprawna ilosc watkow, podaj ponownie: ";
	}
	return threads_count;
}

bool call_proc(std::string& input_path, std::string& output_path, int threads_count, char choice)
{
	Bitmap bitmap;
	std::regex bmp_reg("[[:print:]]*.bmp");
	if (!std::regex_match(input_path, bmp_reg) || !bitmap.load_bitmap(input_path))
		return false;
	int offset = bitmap.get_allocated_size() / threads_count;	//Dzielenie bitmapy na części odpowiadające liczbie wątków
	int rest = bitmap.get_allocated_size() % threads_count;		//Reszta z dzielenia zostaje przydzielona dodatkowo ostatniemu wątkowi
	int width = (int)bitmap.get_info_header()->bV5Width * 3;
	int height = (int)bitmap.get_info_header()->bV5Height;
	
	HINSTANCE hInstance;
	std::vector<std::thread> threads_vector;
	func fun;
	if (choice == '1')
		hInstance = LoadLibrary(L"DLL_Asm.dll");
	else
		hInstance = LoadLibrary(L"DLL_Cpp.dll");
	if (hInstance)
	{
		fun = (func)GetProcAddress(hInstance, "Filtration");
		if (fun)
		{
			unsigned char* result = new unsigned char[width * height];

			memset(result, 0, width * height);

			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < threads_count - 1; i++)
			{
				threads_vector.push_back(std::thread(fun, bitmap.get_pixels(), result, offset * i - 3, offset, width, height));
			}
			
			threads_vector.push_back(std::thread(fun, bitmap.get_pixels(), result, offset * (threads_count - 1), offset + rest, width, height));

			for (int i = 0; i < threads_count; i++)
				threads_vector[i].join();

			auto finish = std::chrono::high_resolution_clock::now();
			std::cout << "Czas wykonania: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n" << std::endl;
			
			delete[] bitmap.get_pixels();
			bitmap.set_pixels(result);
		}
		else
			std::cout << "Nie udalo sie poprawnie zaladowac procedury" << std::endl;
		FreeLibrary(hInstance);
	}
	else
		std::cout << "Nie udalo sie poprawnie zaladowac biblioteki" << std::endl;
	bitmap.save_bitmap(output_path);
	return true;
}

void clear_screen()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}