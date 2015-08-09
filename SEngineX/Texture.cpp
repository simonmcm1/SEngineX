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

SEngineX::Texture2D::Texture2D(std::string folder, std::string filepath)
{
    glGenTextures(1, &this->glTex);
    glBindTexture(GL_TEXTURE_2D, this->glTex);
    
    string extension = GetFileExtension(filepath);
    if(extension == "jpg" || extension == "jpeg") {
        this->bitmap = FreeImage_Load(FIF_JPEG, (folder + filepath).c_str(), BMP_DEFAULT);
    } else if(extension == "png") {
        this->bitmap = FreeImage_Load(FIF_PNG, (folder + filepath).c_str(), BMP_DEFAULT);
    } else {
        //unsupported
        cout << "Unsupported image extension: " + folder + filepath << endl;
        return;
    }
    
    this->height = FreeImage_GetHeight(this->bitmap);
    this->width = FreeImage_GetWidth(this->bitmap);
    this->depth = FreeImage_GetBPP(this->bitmap);
    
    FreeImage_FlipVertical(this->bitmap);

    unsigned char *img = FreeImage_GetBits(this->bitmap);
    
    //TODO: support for grayscale textures?
    if(FreeImage_GetColorType(this->bitmap) == FIC_RGBALPHA){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, img);
    } else if(FreeImage_GetColorType(this->bitmap) == FIC_RGB){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, img);
    } else {
        FreeImage_Unload(this->bitmap);
        cout << "Unsupported image color type: " + folder + filepath << endl;
        return;
    }
    
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    FreeImage_Unload(this->bitmap);
}

//REPEAT is default
void SEngineX::Texture2D::SetWrapMode(TextureWrapMode x, TextureWrapMode y) {
    
    GLenum xWrapMode = GL_REPEAT;
    switch (x) {
        case TextureWrapMode::CLAMP:
            xWrapMode = GL_CLAMP;
            break;
        case TextureWrapMode::REPEAT:
            xWrapMode = GL_REPEAT;
            break;
        default:
            xWrapMode = GL_REPEAT;
    }
    
    GLenum yWrapMode = GL_REPEAT;
    switch (y) {
        case TextureWrapMode::CLAMP:
            yWrapMode = GL_CLAMP;
            break;
        case TextureWrapMode::REPEAT:
            yWrapMode = GL_REPEAT;
            break;
        default:
            xWrapMode = GL_REPEAT;
    }
    
    
    this->Bind(0);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xWrapMode);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yWrapMode);
}

SEngineX::TextureWrapMode SEngineX::Texture2D::WrapModeFromString(std::string string) {
    if(string == "repeat") {
        return TextureWrapMode::REPEAT;
    } else if(string == "clamp") {
        return TextureWrapMode::CLAMP;
    }
    return TextureWrapMode::DEFAULT;
}

SEngineX::Texture2D::~Texture2D() {
    glDeleteTextures(1, &this->glTex);
}

std::shared_ptr<SEngineX::Texture2D>  SEngineX::TextureManager::GetTexture(const std::string folder, const std::string texture) {
    auto iter = textures.find(texture);
    if(iter == textures.end()) {
        auto tex = std::make_shared<Texture2D>(folder, texture);
        textures.insert({texture, tex});
        return tex;
    }
    else return iter->second;
}

std::shared_ptr<SEngineX::Texture2D>  SEngineX::TextureManager::GetTexture(const std::string texture) {
    return this->GetTexture(resourcePath(), texture);
}

