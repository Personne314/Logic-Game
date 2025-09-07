#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <format>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>



/**
 * @namespace Color
 * @brief Contains definition of constants for ANSI color codes.
 */
namespace Color
{
	inline const std::string RED      = "\033[31m";
	inline const std::string GREEN    = "\033[32m";
	inline const std::string YELLOW   = "\033[33m";
	inline const std::string BLUE     = "\033[34m";
	inline const std::string MAGENTA  = "\033[35m";
	inline const std::string CYAN     = "\033[36m";
	inline const std::string RESET    = "\033[0m";
}

// Define the logger colors.
#define ERROR_COLOR Color::RED
#define WARNING_COLOR Color::YELLOW
#ifndef NDEBUG
#define DEBUG_COLOR Color::CYAN
#endif



/** * @brief Singleton for the logger state. 
 */
inline auto& _logger_state() {
	struct LoggerState {
		bool logger_init = false;
		bool first_init  = true;
		bool file_open   = false;
		std::ofstream file;
	};
	static LoggerState state;
	return state;
}



/**
 * @brief Free the logger.
 * @param path The path where to store the log file or empty to log into the console.
 */
inline void quit_logger()
{
	if (!_logger_state().logger_init) return;
	if (_logger_state().file_open) {
		_logger_state().file.close();
		_logger_state().file_open = false;
	}
}

/**
 * @brief Setup the logger.
 * @param path The path where to store the log file or empty to log into the console.
 */
inline void init_logger(std::string path = "")
{
	if (_logger_state().logger_init) return;
	_logger_state().logger_init = true;
	if (path.size()) {
		_logger_state().file.open(path);
		_logger_state().file_open = _logger_state().file.is_open(); 
	}
	if (_logger_state().first_init) atexit(quit_logger);
	_logger_state().first_init = false;
}



/**
 * @brief Print the header and return the given ostream.
 * @param stream The stream to use for printing.
 * @return The given stream.
 */
inline std::ostream &print_header(std::ostream &stream)
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return stream << "[" << std::put_time(std::localtime(&now), "%T") << "] ";
}



/**
 * @brief Print a error message.
 * @param str The content of the message.
 */
template<typename... Args>
inline void print_error(const std::format_string<Args...> str, Args&&... args)
{
	if (!_logger_state().logger_init) return;
	std::string msg = std::format(str, std::forward<Args>(args)...);
	if (_logger_state().file_open) print_header(_logger_state().file << ERROR_COLOR) 
		<< "Error: " << msg << Color::RESET << std::endl;
	else print_header(std::cerr << ERROR_COLOR) << "Error: " << msg << Color::RESET << std::endl;
}

/**
 * @brief Print a warning message.
 * @param str The content of the message.
 */
template<typename... Args>
inline void print_warning(const std::format_string<Args...> str, Args&&... args)
{
	if (!_logger_state().logger_init) return;
	std::string msg = std::format(str, std::forward<Args>(args)...);
	if (_logger_state().file_open) print_header(_logger_state().file << WARNING_COLOR) 
		<< "Warning: " << msg << Color::RESET << std::endl;
	else print_header(std::cerr << WARNING_COLOR) << "Warning: " << msg << Color::RESET << std::endl;
}

/**
 * @brief Print a info message.
 * @param str The content of the message.
 */
template<typename... Args>
inline void print_info(const std::format_string<Args...> str, Args&&... args)
{
	if (!_logger_state().logger_init) return;
	std::string msg = std::format(str, std::forward<Args>(args)...);
	if (_logger_state().file_open) print_header(_logger_state().file) << "Info: " << msg << std::endl;
	else print_header(std::cout) << "Info: " << msg << std::endl;
}

/**
 * @brief Print a debug message.
 * @param str The content of the message.
 */
#ifndef NDEBUG
template<typename... Args>
inline void print_debug(const std::format_string<Args...> str, Args&&... args)
{
	if (!_logger_state().logger_init) return;
	std::string msg = std::format(str, std::forward<Args>(args)...);
	if (_logger_state().file_open) print_header(_logger_state().file << DEBUG_COLOR) 
		<< "Debug: " << msg << Color::RESET << std::endl;
	else print_header(std::cerr << DEBUG_COLOR) << "Debug: " << msg << Color::RESET << std::endl;
}
#endif
