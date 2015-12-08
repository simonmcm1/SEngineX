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
#define SHADOW_MAP_RESOLUTION 1024

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
        float NumberOfPointLights;
        float NumberOfDirectionalLights;
        float pad[2];
        glm::mat4 DirLightSpace;
    };
    
    class LightProjector : public ViewProjector {
        glm::mat4 view;
        glm::mat4 proj;
        
        public:
        LightProjector(DirectionalLight l) {
            //TODO calculate extents from camera view bounding box
            proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10000.0f);
            glm::vec3 fwd = l.transform->GetForward();
            
            view = glm::lookAt(fwd * -1000.0f, fwd, l.transform->GetUp());
        }
        
        glm::mat4 GetViewMatrix() {
            return view;
        }
        
        glm::mat4 GetProjectionMatrix() {
            return proj;
        }
        
        
        
    };
    
    class Renderer {
    private:
        std::vector<PointLight> pointLights;
        std::vector<DirectionalLight> directionalLights;
        std::vector<std::shared_ptr<RenderInstruction>> renderInstructions;
        int numberOfPointLights = 0;
        int numberOfDirectionalLights = 0;
        bool lightsDirty = false;
        InternalShaderData internalShaderData;
        GLuint uniformBufferObject = 0;
        
        void UpdateLights();
        
        GLuint shadowsFBO;
        GLuint shadowsDepthMap;
		GLuint hdrFBO;
		GLuint hdrColorBuffer;
        
    public:
        Renderer(int width, int height);
        void UpdateUniformBuffer();
        void AddLight(PointLight &light);
        void AddLight(DirectionalLight &light);
        void Render(int screenWidth, int screenHeight);
		void RenderFullScreenQuad();
        GLuint GetUBO() {
            return this->uniformBufferObject;
        }
        glm::vec3 Ambient;
        std::shared_ptr<Camera> camera;
        
        void AddRenderInstruction(std::shared_ptr<RenderInstruction> renderInstruction) {
            renderInstructions.push_back(renderInstruction);
        }
        


    };
    
    
}

#endif /* defined(__SEngineX__Renderer__) */
