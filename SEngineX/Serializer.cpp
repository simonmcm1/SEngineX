//
//  Serializer.cpp
//  SEngineX
//
//  Created by Simon McMahon on 16/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Serializer.h"
#include "Texture.h"

//TODO: throw sane errors on misformated definitions

std::shared_ptr<SEngineX::Shader> SEngineX::Serializer::LoadShader(std::string shaderName) {
    std::string definition = get_file_contents((resourcePath() + shaderName + ".shader").c_str());
    rapidjson::Document d;
    
    d.Parse(definition.c_str());
    
    std::string vertex = get_file_contents((resourcePath() + d["vertex"].GetString()).c_str());
    std::string frag = get_file_contents((resourcePath() + d["fragment"].GetString()).c_str());
    const rapidjson::Value& attrs = d["attributes"];
    const rapidjson::Value& unis = d["uniforms"];
    std::vector<SEngineX::ShaderAttribute> attributes;
    std::vector<SEngineX::ShaderAttribute> uniforms;
    for (rapidjson::SizeType i = 0; i < attrs.Size(); i++) {
        attributes.push_back(SEngineX::ShaderAttribute(attrs[i]["name"].GetString(), SEngineX::Shader::AttributeTypeFromString(attrs[i]["type"].GetString())));
    }
    
    for (rapidjson::SizeType i = 0; i < unis.Size(); i++) {
        uniforms.push_back(SEngineX::ShaderAttribute(unis[i]["name"].GetString(), SEngineX::Shader::AttributeTypeFromString(unis[i]["type"].GetString())));
    }
    
                           
    return std::make_shared<SEngineX::Shader>(vertex, frag, attributes, uniforms);
}

std::shared_ptr<SEngineX::Material> SEngineX::Serializer::LoadMaterial(std::string materialName) {
    std::string definition = get_file_contents((resourcePath() + materialName+ ".material").c_str());
    rapidjson::Document d;
    
    d.Parse(definition.c_str());
    auto shader = ShaderManager::Instance().CreateShader(d["shader"].GetString());
    auto mat = std::make_shared<Material>(d["shader"].GetString());
    mat->GetShader()->Use();
    
    for ( rapidjson::Value::ConstMemberIterator itr = d["uniforms"].MemberBegin(); itr != d["uniforms"].MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        for(auto iter = mat->GetShader()->uniforms.begin(); iter != mat->GetShader()->uniforms.end(); iter++) {
            if(iter->name == "material." + name) {
                if(iter->type == SEngineX::ShaderAttributeType::FLOAT) {
                    mat->GetShader()->SetUniformFloat("material." + name, itr->value.GetDouble());
                } else if(iter->type == SEngineX::ShaderAttributeType::FLOAT2) {
                    mat->GetShader()->SetUniform2f("material." + name, itr->value[0].GetDouble(), itr->value[1].GetDouble());
                }
                else if(iter->type == SEngineX::ShaderAttributeType::FLOAT3) {
                    mat->GetShader()->SetUniform3f("material." + name,
                            itr->value[0].GetDouble(),
                            itr->value[1].GetDouble(),
                            itr->value[2].GetDouble()
                    );
                }
                else if(iter->type== SEngineX::ShaderAttributeType::TEXTURE2D) {
                    auto tex = SEngineX::TextureManager::Instance().GetTexture(itr->value.GetString());
                    mat->AddTexture(name, tex);
                }
                
                //TODO: matrix and other types
            }
        }
    
        
    }
    
    return mat;
}