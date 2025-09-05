#include "logger.h"



#define ERROR_COLOR Color::RED			// Color to use for error messages.
#define WARNING_COLOR Color::YELLOW		// Color to use for warning messages.
#ifndef NDEBUG
#define DEBUG_COLOR Color::CYAN			// Color to use for debug messages.
#endif



bool logger_init = false;	// Logger state.
bool first_init = true;		// true until the fisrt logger_init call.



bool file_open = false;	// true if the content must be written in a file.
std::ofstream file;		// The file to use.



/**
 * @brief Setup the logger.
 * @param path The path where to store the log file or empty to log into the console.
 */
void init_logger(std::string path)
{
	if (logger_init) return;
	logger_init = true;
	if (path.size()) {
		file.open(path);
		file_open = file.is_open(); 
	}
	if (first_init) atexit(quit_logger);
	first_init = false;
}

/**
 * @brief Free the logger.
 * @param path The path where to store the log file or empty to log into the console.
 */
void quit_logger()
{
	if (!logger_init) return;
	if (file_open) {
		file.close();
		file_open = false;
	}
}



/**
 * @brief Print the header and return the given ostream.
 * @param stream The stream to use for printing.
 * @return The given stream.
 */
std::ostream &print_header(std::ostream &stream)
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return stream << "[" << std::put_time(std::localtime(&now), "%T") << "] ";
}



/**
 * @brief Print a error message.
 * @param str The content of the message.
 */
void print_error(const std::string &str)
{
	if (!logger_init) return;
	if (file_open) print_header(file << ERROR_COLOR) << "Error: " << str << Color::RESET << std::endl;
	else print_header(std::cerr << ERROR_COLOR) << "Error: " << str << Color::RESET << std::endl;
}

/**
 * @brief Print a warning message.
 * @param str The content of the message.
 */
void print_warning(const std::string &str)
{
	if (!logger_init) return;
	if (file_open) print_header(file << WARNING_COLOR) << "Warning: " << str << Color::RESET << std::endl;
	else print_header(std::cerr << WARNING_COLOR) << "Warning: " << str << Color::RESET << std::endl;
}

/**
 * @brief Print a info message.
 * @param str The content of the message.
 */
void print_info(const std::string &str)
{
	if (!logger_init) return;
	if (file_open) print_header(file) << "Info: " << str << std::endl;
	else print_header(std::cout) << "Info: " << str << std::endl;
}

/**
 * @brief Print a debug message.
 * @param str The content of the message.
 */
#ifndef NDEBUG
void print_debug(const std::string &str)
{
	if (!logger_init) return;
	if (file_open) print_header(file << DEBUG_COLOR) << "Debug: " << str << Color::RESET << std::endl;
	else print_header(std::cerr << DEBUG_COLOR) << "Debug: " << str << Color::RESET << std::endl;
}
#endif
