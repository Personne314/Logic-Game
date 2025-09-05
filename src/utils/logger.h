#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <format>
#include <ctime>
#include <iomanip>
#include <chrono>


void init_logger(std::string path = "");
void quit_logger();



void print_error(const std::string &str);
void print_warning(const std::string &str);
void print_info(const std::string &str);
#ifndef NDEBUG
void print_debug(const std::string &str);
#endif



/**
 * @namespace Color
 * @brief Contains definition of constants for ANSI color codes.
 */
namespace Color {

	const std::string RED		= "\033[31m";
	const std::string GREEN		= "\033[32m";
	const std::string YELLOW	= "\033[33m";
	const std::string BLUE		= "\033[34m";
	const std::string MAGENTA	= "\033[35m";
	const std::string CYAN		= "\033[36m";
	const std::string RESET		= "\033[0m";

}
