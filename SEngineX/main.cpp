#include <cmath>


#include "Engine.h"
#include "util.h"
#include "ResourcePath.hpp"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderInstruction.h"

using namespace std;

SEngineX::Vertex vertices[] = {
    // Positions           // Normals           // Texture Coords
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f),
    
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
    
    glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)
};

GLuint elements[] = {
    0, 1, 2,
    3,4, 5,
    6,7, 8,
    9,10, 11,
    12,13,14,
    15,16,17,
    18,19,20,
    21,22,23,
    24,25,26,
    27,28,29,
    30,31,32,
    33,34,35,
    
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.0f,  0.0f,  1.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};


int main()
{
    SEngineX::Engine &engine = SEngineX::Engine::Instance();
    engine.Init("SEngineX", 800, 600);
 
    vector<SEngineX::ShaderAttribute> attributes {
        SEngineX::ShaderAttribute("position", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("normal", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("texCoord", SEngineX::ShaderAttributeType::FLOAT2)
    };
    
    vector<SEngineX::ShaderAttribute> uniforms {
        SEngineX::ShaderAttribute("_MVP", SEngineX::ShaderAttributeType::MATRIX),
        SEngineX::ShaderAttribute("_M", SEngineX::ShaderAttributeType::MATRIX),
        SEngineX::ShaderAttribute("_VP", SEngineX::ShaderAttributeType::MATRIX),
        SEngineX::ShaderAttribute("material.MainTex", SEngineX::ShaderAttributeType::TEXTURE2D),
        SEngineX::ShaderAttribute("material.AltTex", SEngineX::ShaderAttributeType::TEXTURE2D),
        SEngineX::ShaderAttribute("material.Specular", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("material.Shininess", SEngineX::ShaderAttributeType::FLOAT),
    };
    
    auto basicShader = SEngineX::ShaderManager::Instance().CreateShader("basic", attributes, uniforms);
    
    auto mat = make_shared<SEngineX::Material>("basic");
    
    auto mesh = make_shared<SEngineX::Mesh>(vector<SEngineX::Vertex>(begin(vertices), end(vertices)), vector<GLuint>(begin(elements), end(elements)));
    
    auto texture = make_shared<SEngineX::Texture2D>("container2.png");
    auto faceTex = make_shared<SEngineX::Texture2D>("awesomeface.png");
    
    mat->AddTexture("MainTex", texture);
    mat->AddTexture("AltTex", faceTex);
    mat->SetUniform3f("material.Specular", 0.5f, 0.5f, 0.5f);
    mat->SetUniformFloat("material.Shininess", 32.0f);
    
    SEngineX::Camera camera(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    camera.transform->eulerRotation = glm::vec3(0.0f, 180.0f, 0.0f);
    camera.transform->position = glm::vec3(0.0f, 0.0f, 3.0f);
    
    engine.renderer->Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    
    SEngineX::DirectionalLight dirLight(glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(90.0f, 0.0f, 0.0f));
    SEngineX::PointLight pLight0(pointLightPositions[0], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight1(pointLightPositions[1], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight2(pointLightPositions[2], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight3(pointLightPositions[3], glm::vec3(0.8f, 0.9f, 0.8f));
    
    vector<shared_ptr<SEngineX::Transform>> boxes;
    
    vector<SEngineX::RenderInstruction> renderInstructions;
    
    for(int i = 0; i < 10; i++) {
        auto box = make_shared<SEngineX::Transform>();
        box->position = cubePositions[i];
        boxes.push_back(box);
        
        renderInstructions.push_back(SEngineX::RenderInstruction(mesh, mat, box));
        
    }
    
    
    while(!glfwWindowShouldClose(engine.window))
    {
        
        int i = 0;
        for(auto& box : boxes) {
            i++;
            box->eulerRotation = glm::vec3(-55.0f, (GLfloat)glfwGetTime() * 7.0f * i, 0.0f);
        }
        
        engine.renderer->Render(camera);
        
        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
    
    
    return 0;
    
}




