#include "object.h"

GameObject::GameObject(): Name("default"), Position(0.0f), Scale(1.0f), Color(1.0f), Rotation(1.0f) {
	Resources = nullptr;
	Visible = true;
}

GameObject::GameObject(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 color): Name(name), Position(pos), Scale(scale), Color(color) {
	Resources = nullptr;
	Visible = true;
}

bool GameObject::BindResources(const std::string & path) {
	if (Resources != nullptr)
		delete Resources;
	Resources = new Model(path);
	return true;
}

void GameObject::Draw(Shader & shader, Camera & camera, float ratio) {
	// enable shader
	shader.use();

	// view/projection transformations
	shader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), ratio, 0.1f, 100.0f));
	shader.setMat4("view", camera.GetViewMatrix());

	// model transformations
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->Position);
	model = glm::scale(model, this->Scale);
	shader.setMat4("model", model);

	// color
	shader.setVec3("color", this->Color);
	
	// draw model
	Resources->Draw(shader);
}