//
//  DirectionalLight.h
//  SEngineX
//
//  Created by Simon McMahon on 8/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__DirectionalLight__
#define __SEngineX__DirectionalLight__

#include <iostream>
#include "Light.h"


namespace SEngineX {
    class DirectionalLight : public Light {
    public:
        DirectionalLight(glm::vec3 color, glm::vec3 rotation);
    };
}
#endif /* defined(__SEngineX__DirectionalLight__) */
