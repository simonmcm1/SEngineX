//
//  Renderer.cpp
//  SEngineX
//
//  Created by Simon McMahon on 7/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "Renderer.h"
SEngineX::Renderer::Renderer(int width, int height) {
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

	
	//HDR FBO setup
	glGenFramebuffers(1, &this->hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	
	glGenTextures(1, &this->hdrColorBuffer);
	glBindTexture(GL_TEXTURE_2D, this->hdrColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	GLuint hdrDepthBuffer;
	glGenRenderbuffers(1, &hdrDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, hdrDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->hdrColorBuffer, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, hdrDepthBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
    
	//Post-effects setup
	glGenFramebuffers(1, &this->postEffectsFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->postEffectsFBO);

	glGenTextures(2, this->postEffectsColorBuffers);
	for (int i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, this->postEffectsColorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, this->postEffectsColorBuffers[i], 0);
	}

	//ping-ping fbos for gaussian blur

	glGenFramebuffers(2, this->pingpongFBO);
	glGenTextures(2, this->pingpongBuffer);
	for (GLuint i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, this->pingpongBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->pingpongBuffer[i], 0
			);
	}

	//G-Buffer
	glGenFramebuffers(1, &this->gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->gBuffer);

	//albedo
	glGenTextures(1, &this->gAlbedo);
	glBindTexture(GL_TEXTURE_2D, this->gAlbedo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->gAlbedo, 0);

	//position
	glGenTextures(1, &this->gPosition);
	glBindTexture(GL_TEXTURE_2D, this->gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->gPosition, 0);

	//normals
	glGenTextures(1, &this->gNormal);
	glBindTexture(GL_TEXTURE_2D, this->gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->gNormal, 0);

	//spec
	glGenTextures(1, &this->gSpecular);
	glBindTexture(GL_TEXTURE_2D, this->gSpecular);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, this->gSpecular, 0);



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

	if (this->lightsDirty) {
		this->UpdateLights();
		uboDirty = true;
		this->lightsDirty = false;
	}

	//check camera view pos
	if (camera->transform->position.x != this->internalShaderData.ViewPos[0] ||
		camera->transform->position.y != this->internalShaderData.ViewPos[1] ||
		camera->transform->position.z != this->internalShaderData.ViewPos[2]) {

		this->internalShaderData.ViewPos[0] = camera->transform->position.x;
		this->internalShaderData.ViewPos[1] = camera->transform->position.y;
		this->internalShaderData.ViewPos[2] = camera->transform->position.z;

		uboDirty = true;
	}

	if (uboDirty) {
		this->UpdateUniformBuffer();
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(camera->clearColor.r, camera->clearColor.g, camera->clearColor.b, camera->clearColor.a);

	//render directional shadows into shadows depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowsFBO);
	this->DirectionalShadowsPass();

	//render the scene to HDR floating point buffer
	//glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	//this->ForwardPass(screenWidth, screenHeight);
	
	glBindFramebuffer(GL_FRAMEBUFFER, this->gBuffer);
	this->DeferredPass(screenWidth, screenHeight);

	//Render the HDR floating point buffer to post-effects buffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->postEffectsFBO);
	this->PostEffectsPass();
	
	//draw the final buffer tto screen	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->DrawFrameToScreen(this->hdrColorBuffer);
	//this->DrawFrameToScreen(this->gSpecular);
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

GLuint quadVAO = 0;
GLuint quadVBO;
void SEngineX::Renderer::RenderFullScreenQuad()
{
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void SEngineX::Renderer::DirectionalShadowsPass() {
	//render to depth map
	glCullFace(GL_FRONT);
	glViewport(0, 0, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION);
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);

	//TODO: handle all lights
	LightProjector lp(this->directionalLights[0]);

	auto depthShader = ShaderManager::Instance().GetShader("LIGHTING_DepthOnly");

	//Do the drawing!
	for (auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
		(*iter)->DrawWithShader(lp, *depthShader);
	}
}

void SEngineX::Renderer::ForwardPass(int screenWidth, int screenHeight) {

	//render main camera view
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0 + SHADOW_MAP_TEX_UNIT);
	glBindTexture(GL_TEXTURE_2D, this->shadowsDepthMap);

	LightProjector lp(this->directionalLights[0]);
	glm::mat4 dirspace = lp.GetProjectionMatrix() * lp.GetViewMatrix();

	//draw!
	for (auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
		//todo: put this somewhere more appropriate -i.e uniform block?		
		(*iter)->material->GetShader()->SetUniformMatrix("_DirLightSpace", dirspace);
		(*iter)->Draw(*camera);
	}
}

void SEngineX::Renderer::DeferredPass(int screenWidth, int screenHeight) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//render main camera view
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0 + SHADOW_MAP_TEX_UNIT);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, this->shadowsDepthMap);

	LightProjector lp(this->directionalLights[0]);
	glm::mat4 dirspace = lp.GetProjectionMatrix() * lp.GetViewMatrix();

	GLuint attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);

	//draw!
	for (auto iter = renderInstructions.begin(); iter != renderInstructions.end(); iter++) {
		(*iter)->Draw(*camera);
	}

	//now render the lit scene into the hdr buffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto lightingShader = ShaderManager::Instance().GetShader("LIGHTING_deferred");
	lightingShader->Use();
	lightingShader->SetUniformTexture("gPosition", 0);
	lightingShader->SetUniformTexture("gNormal", 1);
	lightingShader->SetUniformTexture("gAlbedo", 2);
	lightingShader->SetUniformTexture("gSpecular", 3);
	//todo: put this somewhere more appropriate -i.e uniform block?		
	lightingShader->SetUniformMatrix("_DirLightSpace", dirspace);	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->gAlbedo);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->gSpecular);
	glActiveTexture(GL_TEXTURE0 + SHADOW_MAP_TEX_UNIT);
	glBindTexture(GL_TEXTURE_2D, this->shadowsDepthMap);

	this->RenderFullScreenQuad();

}

void SEngineX::Renderer::PostEffectsPass() {
	//render brightness out first
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);

	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	auto hdrShader = ShaderManager::Instance().GetShader("bloom_brightness");
	hdrShader->Use();
	hdrShader->SetUniformTexture("hdrBuffer", 0);
	hdrShader->SetUniformFloat("brightnessThreshold", 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->hdrColorBuffer);

	this->RenderFullScreenQuad();

	//gaussian blur the brightness texture
	GLboolean horizontal = true, first_iteration = true;
	GLuint amount = 10;

	auto blurShader = ShaderManager::Instance().GetShader("bloom_blur");
	blurShader->Use();
	blurShader->SetUniformTexture("image", 0);
	for (GLuint i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		blurShader->SetUniformFloat("horizontal", horizontal ? 1.0f : 0.0f);
		glBindTexture(
			GL_TEXTURE_2D, first_iteration ? this->postEffectsColorBuffers[1] : this->pingpongBuffer[!horizontal]
			);

		this->RenderFullScreenQuad();
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	
	//Add the blurred brightness back into the HDR buffer
	auto addShader = ShaderManager::Instance().GetShader("bloom_add");
	addShader->Use();
	addShader->SetUniformTexture("hdrBuffer", 0);
	addShader->SetUniformTexture("brightnessBuffer", 1);

	glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	glDrawBuffers(1, attachments);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->hdrColorBuffer);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->pingpongBuffer[1]);
	this->RenderFullScreenQuad();

}

void SEngineX::Renderer::DrawFrameToScreen(GLuint texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	auto hdrShader = ShaderManager::Instance().GetShader("hdr_render");
	hdrShader->Use();
	hdrShader->SetUniformFloat("exposure", 1.0f);
	hdrShader->SetUniformTexture("hdrBuffer", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	this->RenderFullScreenQuad();
}