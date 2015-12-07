//
//  Engine.cpp
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Engine.h"
#include "Input.h"

float SEngineX::Time::deltaTime = 0.0f;
float SEngineX::Time::currentTime = 0.0f;

void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		SEngineX::Input::SetKeyDown((SEngineX::Key)key, action == GLFW_PRESS);
	}

	// exit on escape 
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	SEngineX::Input::SetMousePosition(xpos, ypos);
}

bool SEngineX::Engine::Init(std::string title, int width, int height) {
    
    FreeImage_Initialise();
    
    if (glfwInit() != GL_TRUE) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }
    
    // Create a rendering window with OpenGL 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    
    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }
    
    //disable vsync for testing
    glfwSwapInterval(0);

	//register input callbacks
	glfwSetKeyCallback(window, keypress_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
    
    this->renderer = std::shared_ptr<Renderer>(new Renderer());
    this->uIRenderer = std::shared_ptr<UIRenderer>(new UIRenderer());
    
    this->screenWidth = width;
    this->screenHeight = height;
    
    this->frameCount = 0;
    
    Time::deltaTime = 0.0f;
    
    return true;
}

void SEngineX::Engine::StartGameLoop() {

    Time::currentTime = glfwGetTime();
    
    while(!glfwWindowShouldClose(this->window))
    {
        float newTime = glfwGetTime();
        Time::deltaTime = newTime - Time::currentTime;
        Time::currentTime = newTime;
        
		Input::ProcessEvents();

        for(auto go : gameObjects) {
            go->Update();
        }
        
        this->renderer->Render(this->screenWidth, this->screenHeight);
        this->uIRenderer->Render();
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();
        
        this->frameCount++;
    }
}