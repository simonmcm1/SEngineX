//
//  Engine.h
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Engine__
#define __SEngineX__Engine__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <FreeImage.h>

#include <iostream>


namespace SEngineX {
    
    class Engine {
    public:
        static std::unique_ptr<Engine> Init(std::string title, int width, int height) {
            return std::unique_ptr<Engine>(new Engine(title, width, height));
        }
        ~Engine() {
            glfwTerminate();
            FreeImage_DeInitialise();
        }
        
        GLFWwindow *window;
    private:
        Engine(std::string title, int width, int height);
    };
    
}

#endif /* defined(__SEngineX__Engine__) */
