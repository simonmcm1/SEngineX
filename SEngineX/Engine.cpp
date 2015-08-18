//
//  Engine.cpp
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Engine.h"

float SEngineX::Time::deltaTime = 0.0f;
float SEngineX::Time::currentTime = 0.0f;

void SEngineX::Engine::Init(std::string title, int width, int height) {
    
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
        
        for(auto go : gameObjects) {
            go->Update();
        }
        
        this->renderer->Render();
        this->uIRenderer->Render();
        
        glfwSwapBuffers(this->window);
        glfwPollEvents();
        
        this->frameCount++;
    }
}