#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <learnopengl/camera.h>
#include <learnopengl/shader.h>
#include "model.h"

class GameObject {
public:
	// object state
	std::string Name;
	bool Visible;
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Color;
	glm::vec3 Rotation;
	// object resources
	Model * Resources;
	// constructor
	GameObject();
	GameObject(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 color);
	// bind resources
	bool BindResources(const std::string & path);
	// draw object
	virtual void Draw(Shader & shader, Camera & camera, float ratio);
};