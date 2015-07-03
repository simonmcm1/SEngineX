//
//  Model.cpp
//  SEngineX
//
//  Created by Simon McMahon on 17/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Model.h"
#include "Util.h"
#include "Material.h"
#include "Transform.h"
#include "Serializer.h"

void SEngineX::Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    
    this->processNode(scene->mRootNode, scene);
}

void SEngineX::Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for(int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }
    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<SEngineX::RenderInstruction> SEngineX::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture2D> textures;
    
    
    // Process vertex positions, normals and texture coordinates
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        
        
        vertices.push_back(vertex);
    }
    // Process indices
    
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    std::shared_ptr<SEngineX::Material> mat = SEngineX::Serializer::LoadMaterial("diffuse");
    
    // Process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        
        
        aiString diffuseStr;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseStr);
        if(std::string(diffuseStr.C_Str()) != "") {
            auto diffuse = TextureManager::Instance().GetTexture(this->directory, std::string(diffuseStr.C_Str()));
            mat->AddTexture("MainTex", diffuse);
        }
        
        aiString specStr;
        if(std::string(specStr.C_Str()) != "") {
            material->GetTexture(aiTextureType_SPECULAR, 0, &specStr);
            auto specular = TextureManager::Instance().GetTexture(this->directory, std::string(specStr.C_Str()));
            mat->AddTexture("SpecularMap", specular);
        }
    }
    
    auto m = std::make_shared<Mesh>(vertices, indices);
    
    auto instruction = RenderInstruction::Create(m, mat, std::make_shared<Transform>());
    
    return instruction;
}


