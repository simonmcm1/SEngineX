//
//  PointLight.h
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__PointLight__
#define __SEngineX__PointLight__

#include <iostream>

#include "Light.h"

namespace SEngineX {
    class PointLight : public Light {
    public:
        float constant;
        float linear;
        float quadratic;
        
        PointLight(glm::vec3 position, glm::vec3 color);
    };
}

#endif /* defined(__SEngineX__PointLight__) */
