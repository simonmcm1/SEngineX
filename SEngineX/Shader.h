//
//  Shader.h
//  SEngineX
//
//  Created by Simon McMahon on 15/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Shader__
#define __SEngineX__Shader__

#include <iostream>
#include <vector>
#include "Object.h"
#include "Texture.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace SEngineX {
    
    enum class ShaderAttributeType {FLOAT, INT, FLOAT2, FLOAT3, TEXTURE2D, MATRIX};
    
    class ShaderAttribute {
        public:
        ShaderAttributeType type;
        std::string name;
        GLint identifier;
        GLsizei offset;
        GLsizei stride;
        GLint numberOfElements;
        GLenum elementType;
        ShaderAttribute(const std::string name, const ShaderAttributeType type) {
            this->name = name;
            this->type = type;
        }
    };
    
    class Shader : public Object {
    public:
        GLuint Program;
        std::vector<ShaderAttribute> attributes;
        std::vector<ShaderAttribute> uniforms;
        Shader() {
            
        }
        Shader(const std::string shaderName, std::vector<ShaderAttribute> attributes, std::vector<ShaderAttribute> uniforms);
        void Use();
        void EnableAttributes();
        void SetUniform3f(std::string name, float x, float y, float z);
        void SetUniformFloat(std::string name, float val);
        void SetUniformMatrix(std::string name, glm::mat4 &matrix);
        void SetUniformTexture(std::string name, GLint textureUnit);
        
    };
    
    class ShaderManager {
        map<string, std::shared_ptr<Shader>> shaders;
        
        ShaderManager() {}
        
        //delete these to enforce singleton
        ShaderManager(ShaderManager const&)          = delete;
        void operator=(ShaderManager const&)  = delete;
        
        public:
        static ShaderManager& Instance() {
            static ShaderManager instance;
            return instance;
        }
        
        std::shared_ptr<Shader> CreateShader(const std::string shaderName, std::vector<ShaderAttribute> attributes, std::vector<ShaderAttribute> uniforms) {
            auto shader = std::make_shared<Shader>(shaderName, attributes, uniforms);
            AddShader(shaderName, shader);
            
            return shader;
        }
        
        void AddShader(string name, std::shared_ptr<Shader> shader) {
            shaders.insert({name, shader});
        }
        
        shared_ptr<Shader> GetShader(string name) {
            return shaders[name];
        }
        
    };
}


#endif /* defined(__SEngineX__Shader__) */
