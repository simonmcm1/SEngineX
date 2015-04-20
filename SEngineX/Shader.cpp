//
//  Shader.cpp
//  SEngineX
//
//  Created by Simon McMahon on 15/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "util.h"
#include "ResourcePath.hpp"

SEngineX::Shader::Shader(const std::string shaderName, std::vector<ShaderAttribute> sattributes, std::vector<ShaderAttribute> suniforms) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        //const char* vertexPath = (resourcePath() + "basic.vs").c_str();
        vertexCode = get_file_contents((resourcePath() + "basic.vs").c_str());
        fragmentCode = get_file_contents((resourcePath() + "basic.fs").c_str());
        //const char* vsSrc = vs.c_str();
        //const char* fragmentPath = (resourcePath() + "basic.fs").c_str();
        // Convert stream into GLchar array
       // vertexCode = get_file_contents(vertexPath);
       // fragmentCode = get_file_contents(fragmentPath);
    }
    catch(std::exception e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glBindFragDataLocation(this->Program, 0, "outColor");
    glLinkProgram(this->Program);
    
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    
    //register attributes
    GLsizei offset = 0;
    for(auto& attrib : sattributes) {
        attrib.identifier = glGetAttribLocation(this->Program, attrib.name.c_str());
       
        switch (attrib.type) {
            case ShaderAttributeType::FLOAT:
                attrib.stride = 1 * sizeof(float);
                attrib.numberOfElements = 1;
                attrib.elementType = GL_FLOAT;
                break;
            case ShaderAttributeType::FLOAT2:
                attrib.stride = 2 * sizeof(float);
                attrib.numberOfElements = 2;
                attrib.elementType = GL_FLOAT;
                break;
            case ShaderAttributeType::FLOAT3:
                attrib.stride = 3 * sizeof(float);
                attrib.numberOfElements = 3;
                attrib.elementType = GL_FLOAT;
                break;
            default:
                break;
        }
        attrib.offset = offset;
        offset += attrib.stride;
        this->attributes.push_back(attrib);
    }
    
    //stride is actually stride of every attribute together
    for(auto& attribute : this->attributes) {
        attribute.stride = offset;
    }
    
    //register uniforms
    for(auto& attrib : suniforms) {
        attrib.identifier = glGetUniformLocation(this->Program, attrib.name.c_str());
        this->uniforms.push_back(attrib);
    }
}

void SEngineX::Shader::EnableAttributes() {
    for(auto& attribute : this->attributes) {
        
        glVertexAttribPointer(attribute.identifier, attribute.numberOfElements, attribute.elementType, GL_FALSE, attribute.stride, (void *)(attribute.offset));
        glEnableVertexAttribArray(attribute.identifier);

    }
}

void SEngineX::Shader::SetUniform3f(std::string name, float x, float y, float z) {
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniform3f(uniform.identifier, x, y, z);
        }
    }
}

void SEngineX::Shader::SetUniformMatrix(std::string name, glm::mat4 &matrix)
{
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniformMatrix4fv(uniform.identifier, 1, GL_FALSE, glm::value_ptr(matrix));
        }
    }
}

void SEngineX::Shader::SetUniformTexture(std::string name, GLint textureUnit) {
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniform1i(uniform.identifier, textureUnit);
        }
    }
}

void SEngineX::Shader::Use() {
    glUseProgram(this->Program);
}


