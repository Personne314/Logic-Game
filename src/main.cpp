#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>
#include <unistd.h>

#include "utils/logger.h"



/**
 * @brief Return the path of this executable.
 */
std::filesystem::path get_exe_path() {

	char buffer[4096];
	ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
	if (len == -1) {
		throw std::runtime_error("Error: Unable to read /proc/self/exe.");
	}
	buffer[len] = '\0';
	return std::filesystem::path(buffer).parent_path();

}

/**
 * @brief Initialize the SDL and its modules.
 */
bool initSDL()
{

	// Init all SDL2 modules.
	print_info("Init SDL2...");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		print_error("Failed to initialize SDL2 : " + std::string(SDL_GetError()));
		return false;
	}
	atexit(SDL_Quit);

	// Init SDL_Image for image manipulation.
	print_info("Init SDL_Image...");
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		print_error("Failed to initialize SDL_Image : " + std::string(IMG_GetError()));
		return false;
	}
	atexit(IMG_Quit);

	// Init SDL_Mixer for sound managment.
	print_info("Init SDL_Mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		print_error("Failed to initialize SDL_Mixer : " + std::string(Mix_GetError()));
		return false;
	}
	atexit(Mix_Quit);

	// Init SDL_TTF for text rendering.
	print_info("Init SDL_TTF...");
	if (TTF_Init() < 0) {
		print_error("Failed to initialize SDL_TTF : " + std::string(TTF_GetError()));
		return false;
	}
	atexit(TTF_Quit);

	// Init completed.
	return true;

}



/**
 * @brief Entry point. Create the window and start the game.
 */
int main(int argc, char* argv[]) {
	(void)argc; (void)argv;

	// Change the current path to this executable path.
	try {
		std::filesystem::path path = get_exe_path();
		std::filesystem::current_path(path);
	} catch (const std::exception &e) {
		std::stringstream ss;
		ss << "Error: " << e.what();
		throw std::runtime_error(ss.str());
	}

	// Setup the logger and the SDL2.
	init_logger();
	if (!initSDL()) return EXIT_FAILURE; 
	
	// Get window size.
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		std::cerr << "Erreur lors de la récupération des dimensions du bureau : " 
			<< SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	// Create the window and launch the game.
	// Window window(dm.w, dm.h, "Logic Game");
	// window.start();

	// Quitting the game.
	print_info("Quitting the game...");
	return 0;

}
