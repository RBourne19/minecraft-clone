#include "Skybox.h"
#include "AssetManager.h"
#include "BlockMesh.h"

Skybox::Skybox()
{
	
}

void Skybox::init() {
	va = new VertexArray();
	

	va->setAttribute(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	va->setAttribute(1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

Skybox::~Skybox()
{

}


void Skybox::update(const glm::mat4& projection, const glm::mat4& cameraView, float deltaTime) {
	rotation += 1 * deltaTime;
	transform = projection * glm::mat4(glm::mat3(cameraView));
}

void Skybox::render(glm::mat4& mvp) {
	glDisable(GL_DEPTH_TEST);
	va->bind();

	AssetManager::getInstance().getTexture("skybox")->bindTexture();

	std::shared_ptr<Shader> s = AssetManager::getInstance().getShader("skybox");
	s->use();


	s->setMat4("transform", glm::rotate(transform, glm::radians(rotation), glm::vec3(1, 0, 0)));
	std::vector<GLfloat> vertices = {
		   0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		   1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		   1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		   1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		
	};

	size_t vertexCount = vertices.size() / 5;

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	va->unbind();
};