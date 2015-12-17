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
#include <map>
#include "Engine.h"
#include "util.h"
#include "Resources.h"
#include "Serializer.h"

// display info for all active uniforms in a program
void PrintUniformsInfo(unsigned int program) {
    
    
    
	int activeUnif, actualLen, index, uniType,
    uniSize, uniMatStride, uniArrayStride, uniOffset;
	char name[256];
    
	// Get uniforms info (not in named blocks)
	printf("Uniforms Info for program: %d", program);
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUnif);
    
	for (unsigned int i = 0; i < (unsigned int)activeUnif; ++i) {
		glGetActiveUniformsiv(program, 1, &i, GL_UNIFORM_BLOCK_INDEX, &index);
		if (index == -1) {
			glGetActiveUniformName(program, i, 256, &actualLen, name);
			glGetActiveUniformsiv(program, 1, &i, GL_UNIFORM_TYPE, &uniType);
			printf("%s", name);
//			printf("    %s", spGLSLType[uniType].c_str());
			printf("    location: %d", i);
            
			glGetActiveUniformsiv(program, 1, &i, GL_UNIFORM_SIZE, &uniSize);
			glGetActiveUniformsiv(program, 1, &i, GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
            
			int auxSize;
			if (uniArrayStride > 0)
				auxSize = uniArrayStride * uniSize;
//			else
//				auxSize = spGLSLTypeSize[uniType];
            
			printf("    size: %d", auxSize);
			if (uniArrayStride > 0)
				printf("    stride: %d", uniArrayStride);
		}
	}
	// Get named blocks info
	int count, dataSize, info;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_BLOCKS, &count);
    
	for (int i = 0; i < count; ++i) {
		// Get blocks name
		glGetActiveUniformBlockName(program, i, 256, NULL, name);
		glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
		printf("%s\n  Size %d", name, dataSize);
        
		glGetActiveUniformBlockiv(program, i,  GL_UNIFORM_BLOCK_BINDING, &index);
		printf("  Block binding point: %d", index);
		glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, index, &info);
		printf("  Buffer bound to binding point: %d {", info);
        
        
		glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUnif);
        
		unsigned int *indices;
		indices = (unsigned int *)malloc(sizeof(unsigned int) * activeUnif);
		glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (int *)indices);
        
		for (int k = 0; k < activeUnif; ++k) {
            
			glGetActiveUniformName(program, indices[k], 256, &actualLen, name);
			glGetActiveUniformsiv(program, 1, &indices[k], GL_UNIFORM_TYPE, &uniType);
			printf("\t%s\n\t    %s", name, "");
            
			glGetActiveUniformsiv(program, 1, &indices[k], GL_UNIFORM_OFFSET, &uniOffset);
			printf("\t    offset: %d", uniOffset);
            
			glGetActiveUniformsiv(program, 1, &indices[k], GL_UNIFORM_SIZE, &uniSize);
            
			glGetActiveUniformsiv(program, 1, &indices[k], GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
            
			glGetActiveUniformsiv(program, 1, &indices[k], GL_UNIFORM_MATRIX_STRIDE, &uniMatStride);
            
			int auxSize;
			if (uniArrayStride > 0)
				auxSize = uniArrayStride * uniSize;
            
			else if (uniMatStride > 0) {
                
				switch(uniType) {
					case GL_FLOAT_MAT2:
					case GL_FLOAT_MAT2x3:
					case GL_FLOAT_MAT2x4:
					case GL_DOUBLE_MAT2:
					case GL_DOUBLE_MAT2x3:
					case GL_DOUBLE_MAT2x4:
						auxSize = 2 * uniMatStride;
						break;
					case GL_FLOAT_MAT3:
					case GL_FLOAT_MAT3x2:
					case GL_FLOAT_MAT3x4:
					case GL_DOUBLE_MAT3:
					case GL_DOUBLE_MAT3x2:
					case GL_DOUBLE_MAT3x4:
						auxSize = 3 * uniMatStride;
						break;
					case GL_FLOAT_MAT4:
					case GL_FLOAT_MAT4x2:
					case GL_FLOAT_MAT4x3:
					case GL_DOUBLE_MAT4:
					case GL_DOUBLE_MAT4x2:
					case GL_DOUBLE_MAT4x3:
						auxSize = 4 * uniMatStride;
						break;
				}
			}
//			else
//				auxSize = spGLSLTypeSize[uniType];
            
//			auxSize = getUniformByteSize(uniSize, uniType, uniArrayStride, uniMatStride);
//			printf("\t    size: %d", auxSize);
			if (uniArrayStride > 0)
				printf("\t    array stride: %d", uniArrayStride);
			if (uniMatStride > 0)
				printf("\t    mat stride: %d", uniMatStride);
		}
		printf("    }");
	}
}


void PrintProgramInfo(unsigned int program) {
    
	
	unsigned int shaders[5];
	int count, info, linked;
	bool geom= false, tess = false;
    
	// Get the shader's name
	printf("    Shaders {");
	glGetProgramiv(program, GL_ATTACHED_SHADERS,&count);
	glGetAttachedShaders(program, count, NULL, shaders);
	for (int i = 0;  i < count; ++i) {
        
		glGetShaderiv(shaders[i], GL_SHADER_TYPE, &info);
		printf("\t%s: %d", "shadertype", shaders[i]);
		if (info == GL_GEOMETRY_SHADER)
			geom = true;
		if (info == GL_TESS_EVALUATION_SHADER || info == GL_TESS_CONTROL_SHADER)
			tess = true;
	}
	printf("    }");
    
	// Get program info
	glGetProgramiv(program, GL_PROGRAM_SEPARABLE, &info);
	printf("    Program Separable: %d", info);
	
	glGetProgramiv(program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, &info);
	printf("    Program Binary Retrievable Hint: %d", info);
    
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	printf("    Link Status: %d", linked);
    
	glGetProgramiv(program, GL_VALIDATE_STATUS, &info);
	printf("    Validate_Status: %d", info);
    
	glGetProgramiv(program, GL_DELETE_STATUS, &info);
	printf("    Delete_Status: %d", info);
    
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &info);
	printf("    Active_Attributes: %d", info);
    
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &info);
	printf("    Active_Uniforms: %d", info);
    
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_BLOCKS, &info);
	printf("    Active_Uniform_Blocks: %d", info);
    
	// check if trans feed is active
//	glGetProgramiv(program, GL_TRANSFORM_FEEDBACK_BUFFER_MODE, &info);
//	printf("    Transform Feedback Buffer Mode: %s", spTransFeedBufferMode[info].c_str());
    
	glGetProgramiv(program, GL_TRANSFORM_FEEDBACK_VARYINGS, &info);
	printf("    Transform Feedback Varyings: %d", info);
    
	// Geometry shader info, if present
	if (geom && linked) {
		glGetProgramiv(program, GL_GEOMETRY_VERTICES_OUT, &info);
		printf("    Geometry Vertices Out: %d", info);
        
//		glGetProgramiv(program, GL_GEOMETRY_INPUT_TYPE, &info);
//		printf("    Geometry Input Type: %s", spGLSLPrimitives[info].c_str());
        
//		glGetProgramiv(program, GL_GEOMETRY_OUTPUT_TYPE, &info);
//		printf("    Geometry Output Type: %s", spGLSLPrimitives[info].c_str());
        
		glGetProgramiv(program, GL_GEOMETRY_SHADER_INVOCATIONS, &info);
		printf("    Geometry Shader Invocations: %d", info);
	}
	// tessellation shaders info, if present
	if (tess && linked) {
		glGetProgramiv(program, GL_TESS_CONTROL_OUTPUT_VERTICES, &info);
		printf("    Tess Control Output Vertices: %d", info);
        
//		glGetProgramiv(program, GL_TESS_GEN_MODE, &info);
//		printf("    Tess Gen Mode: %s", spGLSLPrimitives[info].c_str());
        
//		glGetProgramiv(program, GL_TESS_GEN_SPACING, &info);
//		printf("    Tess Spacing: %s", spTessGenSpacing[info].c_str());
        
//		glGetProgramiv(program, GL_TESS_GEN_VERTEX_ORDER, &info);
//		printf("    Tess Vertex Order: %s", spVertexOrder[info].c_str());
        
		glGetProgramiv(program, GL_TESS_GEN_POINT_MODE, &info);
		printf("    Tess Gen Point Mode: %d", info); 
	}
	printf("");
}

SEngineX::ShaderAttributeType SEngineX::Shader::AttributeTypeFromString(std::string type) {

    if(type == "float")
        return SEngineX::ShaderAttributeType::FLOAT;
    else if(type == "vec2")
        return SEngineX::ShaderAttributeType::FLOAT2;
    else if(type == "vec3")
        return SEngineX::ShaderAttributeType::FLOAT3;
    else if(type == "vec4")
        return SEngineX::ShaderAttributeType::FLOAT4;
    else if(type == "matrix")
        return SEngineX::ShaderAttributeType::MATRIX;
    else if(type == "tex")
        return SEngineX::ShaderAttributeType::TEXTURE2D;
    else if(type == "int")
        return SEngineX::ShaderAttributeType::INT;
    else
        throw 0; //TODO: throw a proper exception here

}

SEngineX::Shader::Shader(const std::string vertexShader, const std::string fragmentShader, std::vector<ShaderAttribute> sattributes, std::vector<ShaderAttribute> suniforms) {
    
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    
    const char* vShaderCode = vertexShader.c_str();
    const char* fShaderCode = fragmentShader.c_str();
    
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexShader << infoLog << std::endl;
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
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentShader << infoLog << std::endl;
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
    
    //handle UBO
    unsigned int ubo_block_index = glGetUniformBlockIndex(this->Program, "InternalData");
    GLuint binding_point_index = 9;
    glUniformBlockBinding(this->Program, ubo_block_index, binding_point_index);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, Engine::Instance().renderer->GetUBO());
    
   // PrintUniformsInfo(this->Program);
    
}

void SEngineX::Shader::EnableAttributes() {
    for(auto& attribute : this->attributes) {
        
        glVertexAttribPointer(attribute.identifier, attribute.numberOfElements, attribute.elementType, GL_FALSE, attribute.stride, (void *)(attribute.offset));
        glEnableVertexAttribArray(attribute.identifier);

    }
}

void SEngineX::Shader::SetUniform2f(std::string name, float x, float y) {
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniform2f(uniform.identifier, x, y);
        }
    }
}

void SEngineX::Shader::SetUniform3f(std::string name, float x, float y, float z) {
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniform3f(uniform.identifier, x, y, z);
        }
    }
}

void SEngineX::Shader::SetUniformFloat(std::string name, float val) {
    for(auto& uniform : this->uniforms) {
        if(uniform.name == name) {
            glUniform1f(uniform.identifier, val);
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

//TODO: switch uniforms list to a map
void SEngineX::Shader::AddUniform(std::string name, ShaderAttributeType type) {
    ShaderAttribute attrib(name, type);
    attrib.identifier = glGetUniformLocation(this->Program, attrib.name.c_str());
    this->uniforms.push_back(attrib);
}

void SEngineX::Shader::Use() {
    glUseProgram(this->Program);
}

std::shared_ptr<SEngineX::Shader> SEngineX::ShaderManager::CreateShader(const std::string shaderName) {
    auto shader = SEngineX::Serializer::LoadShader(shaderName);
	shader->Use();
    AddShader(shaderName, shader);
    
    //add uniform for directional shadow map
    shader->AddUniform("_DirLightDepth", ShaderAttributeType::TEXTURE2D);
    shader->SetUniformTexture("_DirLightDepth", SHADOW_MAP_TEX_UNIT);
	
	shader->AddUniform("_DirLightSpace", ShaderAttributeType::MATRIX);
    return shader;
}


