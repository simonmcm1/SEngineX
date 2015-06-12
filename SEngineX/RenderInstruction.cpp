//
//  RenderInstruction.cpp
//  SEngineX
//
//  Created by Simon McMahon on 12/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "RenderInstruction.h"
#include "Engine.h"

SEngineX::RenderInstruction::RenderInstruction(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
    this->mesh = mesh;
    this->material = material;
    
    Engine::Instance().renderer->AddRenderInstruction(*this);
}