//
//  RenderInstruction.h
//  SEngineX
//
//  Created by Simon McMahon on 12/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__RenderInstruction__
#define __SEngineX__RenderInstruction__

#include <iostream>

#include "Mesh.h"
#include "Material.h"

namespace SEngineX {
    class RenderInstruction {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
    public:
        RenderInstruction(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
        
        void Draw() {
            this->material->Draw(*this->mesh);
        }
    };
}

#endif /* defined(__SEngineX__RenderInstruction__) */
