#include "engine.h"

extern Engine * engine;

Engine::Engine(std::string name, int width, int height):Name(name), ScreenWidth(width), ScreenHeight(height) {
	// game status
	Status = GAME_MENU;
	Frame = NO_LOCK;
	// music engine
	_musicEngine = irrklang::createIrrKlangDevice();
}

void Engine::Create() {
	// global variable
	// ---------------
	deltaTime = lastFrame = 0.0f;
	firstMouse = true;
	CurMoved = false;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	_window = glfwCreateWindow(ScreenWidth, ScreenHeight, Name.c_str(), NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, _framebuffer_size_callback);
	glfwSetMouseButtonCallback(_window, _mouse_callback);
	glfwSetScrollCallback(_window, _scroll_callback);
	glfwSetKeyCallback(_window, _key_callback);
	glfwSetCursorPosCallback(_window, _cursor_pos_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile default shader
	DefaultShader = new Shader("../Engine/shader.vs", "../Engine/shader.fs");

	// game init
	Init();
}

void Engine::Run() {
	// render loop
	while (!glfwWindowShouldClose(_window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		if (Frame == LOCK30) {
			while (deltaTime < 0.033f) {
				currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
			}
		}
		else if (Frame == LOCK60) {
			while (deltaTime < 0.016f) {
				currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
			}
		}
		lastFrame = currentFrame;
		glfwPollEvents();

		// input
		// -----
		ProcessInput(deltaTime);

		// update
		// ------
		Update(deltaTime);
		CurMoved = false;

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Render();

		glfwSwapBuffers(_window);
	}

	// release
	// -------
	delete DefaultShader;

	glfwTerminate();
}

void Engine::_framebuffer_size_callback(GLFWwindow * window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void Engine::_mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button >= 0 && button < 8) {
		if (action == GLFW_PRESS)
			engine->Mouse[button] = true;
		else if (action == GLFW_RELEASE)
			engine->Mouse[button] = false;
	}
}

void Engine::_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

void Engine::_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// escape key, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// other keys
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			engine->Keys[key] = true;
		else if (action == GLFW_RELEASE)
			engine->Keys[key] = false;
	}
}

void Engine::_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (engine->firstMouse) {
		engine->CurX = xpos;
		engine->CurY = ypos;
		engine->firstMouse = false;
	}
	// set offset
	engine->Xoffset = xpos - engine->CurX;
	engine->Yoffset = engine->CurY - ypos;
	// cursor postion
	engine->CurX = xpos;
	engine->CurY = ypos;

	engine->CurMoved = true;
}

void Engine::ProcessInput(float dt) {
	// create this to support that: not realizing the ProcessInput function
}

void Engine::Render() {
	// iterate object list
	for (GameObject * obj : this->_objetList)
		if (obj->Visible)
			obj->Draw(*DefaultShader, *_camera, (float)ScreenWidth / (float)ScreenHeight);
}

void Engine::BindCamera(Camera * camera) {
	this->_camera = camera;
}

void Engine::BindObject(GameObject * object) {
	this->_objetList.push_back(object);
}

void Engine::PlayMusic(const std::string path, bool isRepead) {
	_musicEngine->play2D(path.c_str(), isRepead);
}