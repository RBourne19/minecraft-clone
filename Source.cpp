#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "App.h"
#include "Vertex.h"
// this file has a lot of duct tape holding it up
App app(NULL);
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    app.mouseHandler(window, xpos, ypos);
}



void init() {

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    app.keyboardHandler(key, scancode, action, mods);
}

void mouseInputCallback(GLFWwindow* window, int button, int action, int mods) {
    app.mouseInputHandler(window, button, action, mods);
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) {
        std::cerr << "Failed to get primary monitor" << std::endl;
        glfwTerminate();
        return -1;
    }

    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if (!videoMode) {
        std::cerr << "Failed to get video mode" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "MINECRAFT_CLONE", primaryMonitor, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;

    }
    app.displayHeight = videoMode->height;
    app.displayWidth = videoMode->width;
    app.setWindow(window);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
   


    glEnable(GL_DEPTH_TEST);

    app.init();
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseInputCallback);



    glClearColor(.43, .177, 1, .5f);
    while (!glfwWindowShouldClose(window)) { 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        app.update();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetCursorPos(window, 400, 300);
    }



    glfwTerminate();
    return 0;
}