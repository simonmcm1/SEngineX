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
    
    //TODO add switch for depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //TODO: specify face culling in shader?
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glFrontFace(GL_CCW);
    
    
    //FrameBuffer for shadow pass
    glGenFramebuffers(1, &this->shadowsFBO);
    
    //depth texture for shadows;
    glGenTextures(1, &shadowsDepthMap);
    glBindTexture(GL_TEXTURE_2D, shadowsDepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //shadow FBO set up for depth only with our depth texture
    glBindFramebuffer(GL_FRAMEBUFFER, this->shadowsFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowsDepthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
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

void SEngineX::Renderer::Render(int screenWidth, int screenHeight) {
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
    glClearColor(camera->clearColor.r, camera->clearColor.g, camera->clearColor.b, camera->clearColor.a);
    
    //render to depth map
    glViewport(0, 0, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION);
    glBindFramebuffer(GL_FRAMEBUFFER, this->shadowsFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //TODO: handle all lights
    LightProjector lp(this->directionalLights[0]);
    
   auto depthShader = ShaderManager::Instance().GetShader("LIGHTING_DepthOnly");
 
    //Do the drawing!
    for(auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
        (*iter)->DrawWithShader(lp, *depthShader);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //render main camera view
    glViewport(0, 0,  screenWidth, screenHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0 + SHADOW_MAP_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, shadowsDepthMap);
    
    //Do the drawing!
    for(auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
        (*iter)->Draw(*camera);
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
    this->internalShaderData.NumberOfPointLights = p;
    
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
    
    this->internalShaderData.NumberOfDirectionalLights = p;
    
    if(this->internalShaderData.NumberOfDirectionalLights >= 1) {
        LightProjector lp(this->directionalLights[0]);
        glm::mat4 dirspace = lp.GetProjectionMatrix() * lp.GetViewMatrix();
        this->internalShaderData.DirLightSpace = dirspace;
    }
    
    this->internalShaderData.Ambient[0] = this->Ambient.x;
    this->internalShaderData.Ambient[1] = this->Ambient.y;
    this->internalShaderData.Ambient[2] = this->Ambient.z;
    
}