//
//  Light.cpp
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Light.h"
#include "Engine.h"

SEngineX::Light::Light(glm::vec3 position, glm::vec3 color, LightCasterType type){
    
    this->transform = std::shared_ptr<Transform>(new Transform());
    transform->position = position;
    this->color = color;
    
    this->lightType = type;
}