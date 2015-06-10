//
//  DirectionalLight.cpp
//  SEngineX
//
//  Created by Simon McMahon on 8/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "DirectionalLight.h"
#include "Engine.h"

SEngineX::DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 rotation) : Light(glm::vec3(), color, LightCasterType::DIRECTIONAL)
{
    this->transform->eulerRotation = rotation;
    Engine::Instance().renderer->AddLight(*this);
}