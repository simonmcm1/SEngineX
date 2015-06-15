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
    
    //TODO: linker error when using automatic IDs
    class Object {
    private:
//        static unsigned int idCounter;
//        unsigned int id;
        
    public:
        std::string name;
        
        Object() {
            name = "Object";
//            id = idCounter++;
        }
        
//        unsigned int GetId() {
//            return id;
//        }
        
    };
    
    
    class GameObject : Object {
        std::string name;
        
    public:
        virtual void Update() {}
        virtual void Awake() {}
    
        
    };
}




#endif /* defined(__SEngineX__Object__) */
