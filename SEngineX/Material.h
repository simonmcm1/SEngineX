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
        Shader shader;
        map<string, Texture2D> textures;
        
        public:
        Material(string shaderName) {
            shader = ShaderManager::Instance().GetShader(shaderName);
        }
        
        void AddTexture(string name, Texture2D &texture) {
            textures.insert({name, texture});
        }
        
        void Draw(Mesh &mesh);
        
    };
    
}

#endif /* defined(__SEngineX__Material__) */
