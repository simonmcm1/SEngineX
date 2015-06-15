//
//  Material.h
//  SEngineX
//
//  Created by Simon McMahon on 12/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Material__
#define __SEngineX__Material__

#include <iostream>
#include <map>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

using namespace std;

namespace SEngineX {
    
    class Material : Object{
        std::shared_ptr<Shader> shader;
        map<string, shared_ptr<Texture2D>> textures;
        
        public:
        Material(string shaderName) {
            shader = ShaderManager::Instance().GetShader(shaderName);
        }
        
        void AddTexture(string name, shared_ptr<Texture2D> texture) {
            textures.insert({name, texture});
        }
        
        void Draw(Mesh &mesh);
        
        std::shared_ptr<Shader> GetShader() {
            return shader;
        }
        
        void SetUniform3f(std::string name, float x, float y, float z) {
            shader->Use();
            shader->SetUniform3f(name, x, y, z);
        }
        void SetUniformFloat(std::string name, float val) {
            shader->Use();
            shader->SetUniformFloat(name, val);
        }
        void SetUniformMatrix(std::string name, glm::mat4 &matrix) {
            shader->Use();
            shader->SetUniformMatrix(name, matrix);
        }
        void SetUniformTexture(std::string name, GLint textureUnit) {
            shader->Use();
            shader->SetUniformTexture(name, textureUnit);
        }
        
    };
    
}

#endif /* defined(__SEngineX__Material__) */
