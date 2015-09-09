//
//  RenderInstruction.cpp
//  SEngineX
//
//  Created by Simon McMahon on 12/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "RenderInstruction.h"
#include "Engine.h"

SEngineX::RenderInstruction::RenderInstruction(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform) {
    this->mesh = mesh;
    this->material = material;
    this->transform = transform;
    
    
}

void SEngineX::RenderInstruction::Draw(ViewProjector &camera) {
    this->DrawWithShader(camera, *material->GetShader());
}

void SEngineX::RenderInstruction::DrawWithShader(ViewProjector &camera, Shader &shader) {
    
    glm::mat4 view;
    glm::mat4 projection;
    
    view = camera.GetViewMatrix();
    projection = camera.GetProjectionMatrix();
    
    auto m = this->transform->GetMatrix();
    glm::mat4 mvp = projection * view * *m;
    glm::mat4 vp = projection * view;
    
    shader.SetUniformMatrix("_MVP", mvp);
    shader.SetUniformMatrix("_VP", vp);
    shader.SetUniformMatrix("_M", *m);
    
    this->material->Draw(*this->mesh, shader);
}

std::shared_ptr<SEngineX::RenderInstruction> SEngineX::RenderInstruction::Create(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform) {
    
    auto ri = std::shared_ptr<SEngineX::RenderInstruction>(new SEngineX::RenderInstruction(mesh, material, transform));
    Engine::Instance().renderer->AddRenderInstruction(ri);
    
    return ri;
    
}