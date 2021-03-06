//
//  Camera.h
//  SEngineX
//
//  Created by Simon McMahon on 20/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Camera__
#define __SEngineX__Camera__

#include <iostream>
#include "Object.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _WINDOWS
	#include <memory>
#endif

namespace SEngineX {
    class ViewProjector {
    public:
        virtual glm::mat4 GetViewMatrix() = 0;
        virtual glm::mat4 GetProjectionMatrix() = 0;
    };
    
    class Camera : public Object, public ViewProjector {
    private:
        glm::mat4 projectionMatrix;
    public:
        float fov;
        float aspectRatio;
        std::shared_ptr<Transform> transform;
        float nearClip;
        float farClip;
        glm::vec4 clearColor;
        
        Camera(float fov, float aspect, float nearClip, float farClip) {
            this->fov = fov;
            this->aspectRatio = aspect;
            this->nearClip = nearClip;
            this->farClip = farClip;
            transform = std::shared_ptr<Transform>(new Transform());
            projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearClip, this->farClip);
            
            //set some defaults
            clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            
        }
        
        virtual glm::mat4 GetViewMatrix() {
            return glm::lookAt(transform->position,
                               transform->position + glm::vec3(transform->GetForward()),
                               glm::vec3(transform->GetUp()));
        }
        
        virtual glm::mat4 GetProjectionMatrix() {
            return this->projectionMatrix;
        }        
    };
    
}


#endif /* defined(__SEngineX__Camera__) */
