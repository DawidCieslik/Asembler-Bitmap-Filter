#include "JA_Projekt.h"

int main()
{
	std::string input_path = "Wejsciowy.bmp";
	std::string output_path = "Wynikowy.bmp";

	int threads_count = set_threads_count();
	char choice = '0';
	bool end = false;
	clear_screen();

	while (!end)
	{
		std::cout << "Obecna ilosc watkow: " << threads_count << std::endl
			<< "Obecna sciezka do pliku wejsciowego: " << input_path << std::endl
			<< "Obecna sciezka do pliku wynikowego: " << output_path << std::endl << std::endl
			<< "Wybierz opcje: " << std::endl
			<< "1 - Filtruj obraz (Asm)" << std::endl
			<< "2 - Filtruj obraz (C++)" << std::endl
			<< "3 - Zmien ilosc watkow" << std::endl
			<< "4 - Zmien sciezke do pliku wejsciowego" << std::endl
			<< "5 - Zmien sciezke do pliku wynikowego" << std::endl
			<< "6 - Koniec" << std::endl;
		choice = _getch();
		switch (choice)
		{
		case '1':
			clear_screen();
			if (!call_proc(input_path, output_path, threads_count, choice))
				std::cout << "Blad pliku" << std::endl << std::endl;
			break;
		case '2':
			clear_screen();
			if (!call_proc(input_path, output_path, threads_count, choice))
				std::cout << "Blad pliku" << std::endl << std::endl;
			break;
		case '3':
			clear_screen();
			threads_count = set_threads_count();
			break;
		case '4':
			clear_screen();
			std::cout << "Podaj sciezke do bitmapy: ";
			std::getline(std::cin, input_path);
			break;
		case '5':
			clear_screen();
			std::cout << "Podaj sciezke pliku wynikowego: ";
			std::getline(std::cin, output_path);
			break;
		case '6':
			end = true;
			break;
		default:
			clear_screen();
			std::cout << "Wybierz opcje istniejaca!" << std::endl << std::endl;
			break;
		}
	}
	return 0;
}