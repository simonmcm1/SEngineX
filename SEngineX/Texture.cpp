//
//  Texture.cpp
//  SEngineX
//
//  Created by Simon McMahon on 16/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//


#include "Texture.h"

#include "ResourcePath.hpp"
#include "util.h"

using namespace std;

void SEngineX::Texture2D::Bind(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->glTex);
}

SEngineX::Texture2D::Texture2D(std::string filepath)
{
    glGenTextures(1, &this->glTex);
    glBindTexture(GL_TEXTURE_2D, this->glTex);
    
    string extension = GetFileExtension(filepath);
    if(extension == "jpg" || extension == "jpeg") {
        this->bitmap = FreeImage_Load(FIF_JPEG, (resourcePath() + filepath).c_str(), BMP_DEFAULT);
        this->height = FreeImage_GetHeight(this->bitmap);
        this->width = FreeImage_GetWidth(this->bitmap);
        this->depth = FreeImage_GetBPP(this->bitmap);
        
        FreeImage_FlipVertical(this->bitmap);
        
        unsigned char *img = FreeImage_GetBits(this->bitmap);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, img);
    } else if(extension == "png") {
        this->bitmap = FreeImage_Load(FIF_PNG, (resourcePath() + filepath).c_str(), BMP_DEFAULT);
        this->height = FreeImage_GetHeight(this->bitmap);
        this->width = FreeImage_GetWidth(this->bitmap);
        this->depth = FreeImage_GetBPP(this->bitmap);
        
        FreeImage_FlipVertical(this->bitmap);
        
        unsigned char *img = FreeImage_GetBits(this->bitmap);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, img);
    } else {
        //unsupported
        cout << "Unsupported image extension: " + filepath << endl;
        return;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    
    FreeImage_Unload(this->bitmap);
    glBindTexture(GL_TEXTURE_2D, 0);
}

SEngineX::Texture2D::~Texture2D() {
    glDeleteTextures(1, &this->glTex);
}