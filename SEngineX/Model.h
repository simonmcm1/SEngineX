//
//  Model.h
//  SEngineX
//
//  Created by Simon McMahon on 17/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Model__
#define __SEngineX__Model__

#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Object.h"
#include "Mesh.h"
#include "RenderInstruction.h"
#include "Texture.h"

namespace SEngineX {
    class Model : public Object {
    public:
        Model(std::string path)
        {
            this->loadModel(path);
        }
        void Draw();
        std::vector<std::shared_ptr<RenderInstruction>> meshes;
    private:
        
        std::string directory;
        
        void loadModel(std::string path);
        
        void processNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<RenderInstruction> processMesh(aiMesh* mesh, const aiScene* scene);
        
    };
}

#endif /* defined(__SEngineX__Model__) */
