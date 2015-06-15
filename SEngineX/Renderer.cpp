//
//  Renderer.cpp
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Renderer.h"

SEngineX::Renderer::Renderer() {
    
    //Some default values
    this->Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    
    //set up uniform buffer for internal shader values
    glGenBuffers(1, &this->uniformBufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, this->uniformBufferObject);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(this->internalShaderData), &this->internalShaderData, GL_DYNAMIC_DRAW);
    //glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
}

void SEngineX::Renderer::UpdateUniformBuffer() {
    glBindBuffer(GL_UNIFORM_BUFFER, this->uniformBufferObject);
    GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &this->internalShaderData, sizeof(this->internalShaderData));
    glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void SEngineX::Renderer::AddLight(PointLight &light) {
    this->pointLights.push_back(light);
    this->lightsDirty = true;
    this->numberOfPointLights++;
}

void SEngineX::Renderer::AddLight(DirectionalLight &light) {
    this->directionalLights.push_back(light);
    this->lightsDirty = true;
    this->numberOfDirectionalLights++;
}

void SEngineX::Renderer::Render() {
    bool uboDirty = false;
    
    if(this->lightsDirty) {
        this->UpdateLights();
        uboDirty = true;
        this->lightsDirty = false;
    }
    
    //check camera view pos
    if(camera->transform->position.x != this->internalShaderData.ViewPos[0] ||
       camera->transform->position.y != this->internalShaderData.ViewPos[1] ||
       camera->transform->position.z != this->internalShaderData.ViewPos[2]) {
        
        this->internalShaderData.ViewPos[0] = camera->transform->position.x;
        this->internalShaderData.ViewPos[1] = camera->transform->position.y;
        this->internalShaderData.ViewPos[2] = camera->transform->position.z;
        
        uboDirty = true;
    }
    
    if(uboDirty) {
        this->UpdateUniformBuffer();
    }
    
    
    //clear screen
    // Clear the screen to black
    glClearColor(camera->clearColor.r, camera->clearColor.g, camera->clearColor.b, camera->clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Do the drawing!
    for(auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
        iter->Draw(*camera);
    }
    
    
    
}

void SEngineX::Renderer::UpdateLights() {
    int p = 0;
    for(auto& light : this->pointLights) {
        point_light pLight = {
            light.transform->position.x,
            light.transform->position.y,
            light.transform->position.z,
            0.0f,
            light.color.r,
            light.color.g,
            light.color.b,
            0.0f,
            light.constant,
            light.linear,
            light.quadratic,
            0.0f
        };
        this->internalShaderData.pointLights[p++] = pLight;
    }
    
    p = 0;
    for(auto& light : this->directionalLights) {
        glm::vec3 fwd = light.transform->GetForward();
        directional_light dLight = {
            light.color.r,
            light.color.g,
            light.color.b,
            0.0f,
            fwd.x,
            fwd.y,
            fwd.z,
            0.0f
        };
        this->internalShaderData.directionalLights[p++] = dLight;
    }
    
    this->internalShaderData.Ambient[0] = this->Ambient.x;
    this->internalShaderData.Ambient[1] = this->Ambient.y;
    this->internalShaderData.Ambient[2] = this->Ambient.z;
    
}