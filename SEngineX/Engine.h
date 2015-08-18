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
#include "UIRenderer.h"
#include "Object.h"

#include <iostream>


namespace SEngineX {
    
    class Time {
    public:
        static float deltaTime;
        static float currentTime;
    };
    
    
    class Engine {
    private:
        Engine() {
            
        }
        
        vector<std::shared_ptr<GameObject>> gameObjects;
        
        //delete these to enforce singleton
        Engine(Engine const&)          = delete;
        void operator=(Engine const&)  = delete;
        
        int screenWidth;
        int screenHeight;
        long frameCount;
        
    public:
        
        static Engine& Instance() {
            static Engine instance;
            return instance;
        }
        
        std::shared_ptr<Renderer> renderer;
        std::shared_ptr<UIRenderer> uIRenderer;
        
        std::pair<int, int> GetScreenSize() {
            return std::pair<int, int>(screenWidth, screenHeight);
        }
        
        void Init(std::string title, int width, int height);
        
        ~Engine() {
            glfwTerminate();
            FreeImage_DeInitialise();
        }
        
        void AddGameObject(std::shared_ptr<GameObject> go) {
            gameObjects.push_back(go);
        }
        
        void StartGameLoop();
        
        GLFWwindow *window;
        

    };
    
    class GameObjectFactory {
    public:
        template<typename T> static std::shared_ptr<T> Create();
    };
}

template<typename T> std::shared_ptr<T> SEngineX::GameObjectFactory::Create() {
    auto obj = std::make_shared<T>();
    obj->Awake();
    SEngineX::Engine::Instance().AddGameObject(obj);
    return obj;
}

#endif /* defined(__SEngineX__Engine__) */
