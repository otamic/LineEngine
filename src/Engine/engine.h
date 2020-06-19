#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <irrklang/irrKlang.h>
#include "model.h"
#include "object.h"

#include <iostream>
#include <vector>

enum GameStatus {
	GAME_ACTIVE,
	GAME_MENU
};

enum GameFrame {
	LOCK30,
	LOCK60,
	NO_LOCK
};

class Engine {
public:
	// settings
	int ScreenWidth, ScreenHeight;
	// status
	GameStatus Status;
	GameFrame Frame;
	// keyboard and Mouse Status
	bool Keys[1024];
	bool Mouse[8];
	bool CurMoved;
	float CurX, CurY;
	float Xoffset, Yoffset;
	
	// initialize basis
	void Create();
	void Run();		// render loop

	// game procedure
	virtual void Init() = 0;
	virtual void ProcessInput(float dt);
	virtual void Update(float dt) = 0;
	virtual void Render();
	
	// constructor
	Engine(std::string name = "default", int width = 800, int height = 600);

protected:
	Shader * DefaultShader;

	// game logic
	void BindCamera(Camera * camera);
	void BindObject(GameObject * object);
	void PlayMusic(const std::string path, bool isRepead);
private:
	// info
	std::string Name;
	// timing
	float deltaTime;
	float lastFrame;
	bool firstMouse;

	// bind window
	GLFWwindow * _window;

	// main camera
	Camera * _camera;
	// music engine
	irrklang::ISoundEngine * _musicEngine;
	
	// all object
	vector<GameObject *> _objetList;

	static void _framebuffer_size_callback(GLFWwindow * window, int width, int height);
	static void _mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void _cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
};

// Global Engine
extern Engine * engine;

#define DECLARE_MAIN(UserDefinedEngine) \
	Engine * engine;	\
	int main() { \
		engine = new UserDefinedEngine(); \
		engine->Create(); \
		engine->Run(); \
		return 0;	\
	}