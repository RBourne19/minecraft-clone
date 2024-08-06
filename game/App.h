#pragma once
#include "Shader.h"
#include "Game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "Texture.h"


class App {
	public:
		App(GLFWwindow* window);
		void update();
		void mouseHandler(GLFWwindow* window, double x, double y);
		void setWindow(GLFWwindow* window);
		void init();
		void keyboardHandler(int key, int scancode, int action, int mods);
		void mouseInputHandler(GLFWwindow* window, int button, int action, int mods);

		float displayWidth, displayHeight;

	private:
		Keyboard keyboard;
		Mouse mouse;
		Game game;
		GLFWwindow* window;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		glm::mat4 projection;
		glm::mat4 model = glm::mat4(1.0f); // Identity matrix
};