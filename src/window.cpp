#include "window.h"



#define FPS_CAP 60



/**
 * @brief Construct a window.
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param name The name of the window.
 */
Window::Window(int width, int height, const std::string& name) : 
	m_init(false), 
	m_context(nullptr), 
	m_window(nullptr), 
	m_width(width), 
	m_height(height)
{
	
	// Create the SDL2 window.
	print_info("Creating window...");
	m_window = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
	);
	if (!m_window) {
		print_error("Failed to create the window : " + std::string(SDL_GetError()));
		return;
	}

	// Init GLEW and the OpenGL context.
	if (!initGL()) return;


	m_init = true;

}

/**
 * @brief Destroy the Window and its SDL2 window/OpenGL context.
 */
Window::~Window()
{
	if (m_context) SDL_GL_DeleteContext(m_context);
	if (m_window) SDL_DestroyWindow(m_window);
}

/**
 * @brief Launch the game if everything is fine.
 */
void Window::start()
{
	if (m_init) {
		print_info("Starting the game...");
		loop();
	}
}



/**
 * @brief Setup GLEW and the OpenGL context.
 */
bool Window::initGL() {

	// Initialize the OpenGL context and setup OpenGL attributes.
	print_debug("Init OpenGL...");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context) {
		print_error("Failed to create the OpenGL context : " + std::string(SDL_GetError()));
		return false;   
	} 

	// Initialisation de GLEW.
	GLenum initGLEW = glewInit();
	if (initGLEW != GLEW_OK) {
		std::cerr << "Erreur lors de l'initialisation de GLEW : "
			<< std::string(reinterpret_cast<const char*>(glewGetErrorString(initGLEW)))
			<< std::endl;
		return false;
	}

	// Active le Depth Test, l'Alpha Blending et définit la couleur de nettoyage.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	SDL_GL_SetSwapInterval(0);

	// Initialisation terminée.
	std::cout << "OpenGL Initialisée !" << std::endl;
	return true;

}

/**
 * @brief Contains the main loop of the game.
 */
void Window::loop() {


	
	int i = 0;


	// Main game loop.
	uint32_t time = SDL_GetTicks();
	while (i < 60) {
		if (SDL_GetTicks() - time > 1000/FPS_CAP) {
			time = SDL_GetTicks();


			// DO SOME SHIT
			++i;

			// Swap the frame buffers.
			SDL_GL_SwapWindow(m_window);
		} else SDL_Delay(1);
	}

}
