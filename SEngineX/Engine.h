//
//  Engine.h
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Engine__
#define __SEngineX__Engine__


#include <glm/vec3.hpp>
#include <FreeImage.h>

#include "Renderer.h"

#include <iostream>


namespace SEngineX {
    
    class Engine {
    public:
        static Engine& Instance() {
            static Engine instance;
            return instance;
        }
        
        std::shared_ptr<Renderer> renderer;
        
        void Init(std::string title, int width, int height);
        
        ~Engine() {
            glfwTerminate();
            FreeImage_DeInitialise();
        }
        
        GLFWwindow *window;
        
    private:
        Engine() {
            
        }

        //delete these to enforce singleton
        Engine(Engine const&)          = delete;
        void operator=(Engine const&)  = delete;
    };
    
}

#endif /* defined(__SEngineX__Engine__) */
