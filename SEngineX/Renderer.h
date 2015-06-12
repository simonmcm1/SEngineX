//
//  Renderer.h
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Renderer__
#define __SEngineX__Renderer__

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "RenderInstruction.h"

#define MAX_POINT_LIGHTS 4
#define MAX_DIRECTIONAL_LIGHTS 2

namespace SEngineX {
    
    struct directional_light {
        float color[4];
        float direction[4];
    };
    
    struct point_light {
        float position[4];
        float color[4];
        float constant;
        float linear;
        float quadratic;
        float pad;
    };
    
    struct InternalShaderData {
        float Ambient[4];
        float ViewPos[4];
        point_light pointLights[MAX_POINT_LIGHTS];
        directional_light directionalLights[MAX_DIRECTIONAL_LIGHTS];
    };
    
    class Renderer {
    private:
        std::vector<PointLight> pointLights;
        std::vector<DirectionalLight> directionalLights;
        std::vector<RenderInstruction> renderInstructions;
        int numberOfPointLights = 0;
        int numberOfDirectionalLights = 0;
        bool lightsDirty = false;
        InternalShaderData internalShaderData;
        GLuint uniformBufferObject = 0;
        
        void UpdateLights();
        
    public:
        Renderer();
        void UpdateUniformBuffer();
        void AddLight(PointLight &light);
        void AddLight(DirectionalLight &light);
        void Render(Camera& camera);
        GLuint GetUBO() {
            return this->uniformBufferObject;
        }
        glm::vec3 Ambient;
        
        void AddRenderInstruction(RenderInstruction &renderInstruction) {
            renderInstructions.push_back(renderInstruction);
        }
        


    };
    
    
}

#endif /* defined(__SEngineX__Renderer__) */
