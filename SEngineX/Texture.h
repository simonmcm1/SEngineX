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
#include <map>

#ifdef _WINDOWS
	#include <memory>
#endif

#include "Object.h"
#include "Texture.h"

#include "Resources.h"
#include "util.h"

namespace SEngineX {
    
    enum class TextureWrapMode {DEFAULT, REPEAT, CLAMP};
    
    class Texture2D : public Object {
    private:
        FIBITMAP *bitmap;
        
    public:
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        GLuint glTex;
        
        void Bind(int textureUnit);
        
        
        Texture2D(std::string folder, std::string filepath, bool gammaCorrect);
        Texture2D(std::string folder, std::string filepath) : Texture2D(folder, filepath, true) {
            
        }
        Texture2D(std::string filePath) : Texture2D(resourcePath(), filePath, true) {
            
        }
        
        void SetWrapMode(TextureWrapMode x, TextureWrapMode  y);
        void SetWrapMode(TextureWrapMode  x) {
            SetWrapMode(x, x);
        }

        static TextureWrapMode WrapModeFromString(std::string str);
        
        ~Texture2D();
    };
    
    class TextureManager {
        std::map<std::string, std::shared_ptr<Texture2D>> textures;
        
        TextureManager() {}
        
        //delete these to enforce singleton
        TextureManager(TextureManager const&)          = delete;
        void operator=(TextureManager const&)  = delete;
        
    public:
        static TextureManager& Instance() {
            static TextureManager instance;
            return instance;
        }
        
        std::shared_ptr<Texture2D> GetTexture(const std::string folder, const std::string texture, bool gammaCorrect);
        std::shared_ptr<Texture2D> GetTexture(const std::string texture);
        
    };
}

#endif /* defined(__SEngineX__Texture__) */
