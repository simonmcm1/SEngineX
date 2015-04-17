//
//  Texture.h
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Texture__
#define __SEngineX__Texture__

#include <iostream>
#include <FreeImage.h>

#include "Object.h"


namespace SEngineX {
    class Texture2D : public Object {
    private:
        FIBITMAP *bitmap;
        
    public:
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        GLuint glTex;
        
        void Bind(int textureUnit);
        
        Texture2D(std::string filepath);
        ~Texture2D();
        
        
    };
}

#endif /* defined(__SEngineX__Texture__) */
