//
//  Material.cpp
//  SEngineX
//
//  Created by Simon McMahon on 12/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Material.h"

void SEngineX::Material::Draw(Mesh &mesh) {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    int i = 0;
    
    shader->Use();
    shader->SetUniform2f("_tiling", this->tiling.x, this->tiling.y);
    for(auto iter = textures.begin(); iter != textures.end(); ++iter)
    {
        shader->SetUniformTexture("material." + iter->first, i);
        iter->second->Bind(i);
        
        i++;
    }
    
    mesh.Draw();
}