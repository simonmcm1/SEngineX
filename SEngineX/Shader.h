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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        Shader();
        Shader(const std::string shaderName, std::vector<ShaderAttribute> attributes, std::vector<ShaderAttribute> uniforms);
        void Use();
        void EnableAttributes();
        void SetUniform3f(std::string name, float x, float y, float z);
        void SetUniformFloat(std::string name, float val);
        void SetUniformMatrix(std::string name, glm::mat4 &matrix);
        void SetUniformTexture(std::string name, GLint textureUnit);
        
    };
}


#endif /* defined(__SEngineX__Shader__) */
