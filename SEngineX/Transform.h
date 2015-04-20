//
//  Transform.h
//  SEngineX
//
//  Created by Simon McMahon on 17/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Transform__
#define __SEngineX__Transform__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"


namespace SEngineX {
    
    class Transform : public Object {
    public:
        glm::vec3 position;
        glm::vec3 eulerRotation;
        glm::vec3 scale;
        
        std::shared_ptr<glm::mat4> GetMatrix() {
            glm::mat4 m;
            m = glm::translate(m, position);
            m = glm::rotate(m, glm::radians(eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            m = glm::scale(m, scale);
            std::shared_ptr<glm::mat4> mat(new glm::mat4(m));            
            return mat;
        }
        
        glm::vec3 GetForward() {
            glm::mat4 m;
            m = glm::rotate(m, glm::radians(eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            return glm::normalize(glm::vec3(m *(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f))));
        }
        
        glm::vec3 GetUp() {
            glm::mat4 m;
            m = glm::rotate(m, glm::radians(eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            m = glm::rotate(m, glm::radians(eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            
            return glm::normalize(glm::vec3(m * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
        }
        
        Transform() {
            position = glm::vec3(0.0f, 0.0f, 0.0f);
            eulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
            scale = glm::vec3(1.0f, 1.0f, 1.0f);
        }
    };
    
}


#endif /* defined(__SEngineX__Transform__) */
