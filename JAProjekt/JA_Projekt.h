#pragma once

#include "bitmap.h"
#include "framework.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <regex>
#include <sstream>

unsigned int set_threads_count();
bool call_proc(std::string& input_path, std::string& output_path, int threads_count, char choice);
void clear_screen();