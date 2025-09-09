#include "window.h"

using namespace std::chrono_literals;



#define FRAME_CAP 60



/**
 * @brief Construct a window.
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param name The name of the window.
 */
Window::Window(uint32_t width, uint32_t height, const std::string& name) : 
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
		print_error("Failed to create the window : {}", SDL_GetError());
		return;
	}

	// Init GLEW and the OpenGL context.
	if (!initGL()) return;

	// Create the game.
	m_events = std::make_unique<Events>();
	m_game = std::make_unique<Game>(*m_events, width, height);
	m_init = m_game->isInit();

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
bool Window::initGL()
{

	// Initialize the OpenGL context and setup OpenGL attributes.
	print_debug("Init OpenGL...");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context) {
		print_error("Failed to create the OpenGL context : {}", SDL_GetError());
		return false;   
	} 

	// Init GLEW.
	print_debug("Init GLEW...");
	GLenum initGLEW = glewInit();
	if (initGLEW != GLEW_OK) {
		print_error(
			"Failed to initialize GLEW : {}",
			reinterpret_cast<const char*>(glewGetErrorString(initGLEW))
		);
		return false;
	}

	// Activate depth test, alpha blending and define clear color.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0,0, m_width, m_height);
	SDL_GL_SetSwapInterval(0);

	// Print OpenGL infos.
	#ifndef NDEBUG
	print_debug("OpenGL version : {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	print_debug("GLSL version {}: ", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
	print_debug("Renderer : {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	print_debug("Vendor : {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	#endif
	
	return true;

}

/**
 * @brief Contains the main loop of the game.
 */
void Window::loop()
{

	// Timer.
	auto frame_time = std::chrono::high_resolution_clock::now();
	auto second_time = frame_time;
	double frame_duration = 0.0;
	uint32_t frame = 0;
	uint32_t fps = 0;

	// Main game loop.
	while (!m_events->close()) {
		auto now = std::chrono::high_resolution_clock::now();

		// Render a frame.
		if ((frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
				now-frame_time).count()
			) >= 1000.0/FRAME_CAP 
		) {
			frame_time = now;
			++frame;

			// Process all new events.
			m_events->poll();

			// Render a new frame.
			m_game->render(frame_duration / 1000.0f);
			SDL_GL_SwapWindow(m_window);
	
		// Delay when there is nothing to do.
		} else std::this_thread::sleep_for(100us);

		// Measure the FPS.
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now-second_time).count() >= 1000) {
			second_time = now;
			fps = frame;
			frame = 0;
			#ifndef NDEBUG
			print_debug("FPS ({})", fps);
			#endif
		}

	}

}
