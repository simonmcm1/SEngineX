//
//  Light.h
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Light__
#define __SEngineX__Light__

#include <iostream>

#ifdef _WINDOWS
	#include <memory>
#endif

#include "Object.h"
#include "Transform.h"

namespace SEngineX {
    
    enum LightCasterType {DIRECTIONAL, POINT};
    
    class Light : public Object {
        
    public:
        std::shared_ptr<Transform> transform;
        glm::vec3 color;
        LightCasterType lightType;
        Light(glm::vec3 position, glm::vec3 color, LightCasterType type);
    };
}

#endif /* defined(__SEngineX__Light__) */
