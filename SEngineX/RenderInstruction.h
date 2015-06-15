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
#include "Transform.h"
#include "Camera.h"

namespace SEngineX {
    class RenderInstruction {
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
        std::shared_ptr<Transform> transform;
    public:
        RenderInstruction(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform);
        
        void Draw(Camera &camera);
    };
}

#endif /* defined(__SEngineX__RenderInstruction__) */
