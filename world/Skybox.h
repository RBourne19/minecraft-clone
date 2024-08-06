#pragma once
#ifndef SKY_H
#define SKY_H
#include "GameHeaders.h"
#include "VertexArray.h"
#include <glm/gtc/matrix_transform.hpp>

class Skybox
{
public:
	Skybox();
	void init();
	~Skybox();
	void render(glm::mat4& mvp);
	void update(const glm::mat4& projection, const glm::mat4& cameraView, float deltaTime);
private:
	VertexArray* va;
	glm::mat4 transform{ 1 };
	float rotation;
};



#endif 
