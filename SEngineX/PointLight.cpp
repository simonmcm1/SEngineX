//
//  PointLight.cpp
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "PointLight.h"
#include "Engine.h"

SEngineX::PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(position, color, LightCasterType::POINT)
{
    constant = 1.0f;
    linear = 0.06f;
    quadratic = 0.02f;
    Engine::Instance().renderer->AddLight(*this);
}
