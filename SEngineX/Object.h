//
//  Object.h
//  SEngineX
//
//  Created by Simon McMahon on 15/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Object__
#define __SEngineX__Object__

#include <iostream>
#include <GL/glew.h>

namespace SEngineX {
    
    class Object {
    public:
        std::string name;
        
        Object() {
            name = "Object";
        }
        
    };
}

#endif /* defined(__SEngineX__Object__) */
