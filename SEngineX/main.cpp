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

using namespace std;

int main()
{
    SEngineX::Engine &engine = SEngineX::Engine::Instance();
    engine.Init("SEngineX", 800, 600);

    GLfloat vertices[] = {
        // Positions           // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
    
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    
    // Positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    
    
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                 GL_STATIC_DRAW);

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


    
    
    SEngineX::Shader basicShader("basic", attributes, uniforms);
    basicShader.Use();
    basicShader.EnableAttributes();
    
    SEngineX::Texture2D texture("container2.png");
    
    SEngineX::Texture2D faceTex("awesomeface.png");

    basicShader.SetUniformTexture("material.MainTex", 0);
    basicShader.SetUniformTexture("material.AltTex", 1);

    basicShader.SetUniform3f("material.Specular", 0.5f, 0.5f, 0.5f);
    basicShader.SetUniformFloat("material.Shininess", 32.0f);
    
    SEngineX::DirectionalLight dirLight(glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(90.0f, 0.0f, 0.0f));
    SEngineX::PointLight pLight0(pointLightPositions[0], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight1(pointLightPositions[1], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight2(pointLightPositions[2], glm::vec3(0.8f, 0.8f, 0.8f));
    SEngineX::PointLight pLight3(pointLightPositions[3], glm::vec3(0.8f, 0.9f, 0.8f));
    
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
    
    vector<SEngineX::Transform> boxes;
    
    for(int i = 0; i < 10; i++) {
        SEngineX::Transform box;
        box.position = cubePositions[i];
        boxes.push_back(box);
    }
    
    glm::mat4 view;
    glm::mat4 projection;
    
    glEnable(GL_DEPTH_TEST);
    
    SEngineX::Camera camera(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    projection = camera.GetProjectionMatrix();
    
    camera.transform->eulerRotation = glm::vec3(0.0f, 180.0f, 0.0f);
    camera.transform->position = glm::vec3(0.0f, 0.0f, 3.0f);
    auto t_start = std::chrono::high_resolution_clock::now();
    
    engine.renderer->Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    
    while(!glfwWindowShouldClose(engine.window))
    {
        engine.renderer->Render(camera);
        
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = camera.GetViewMatrix();
        
        texture.Bind(0);
        faceTex.Bind(1);
        glBindVertexArray(vao);
        int i = 0;
        for(auto& box : boxes) {
            i++;
            box.eulerRotation = glm::vec3(-55.0f, (GLfloat)glfwGetTime() * 7.0f * i, 0.0f);
            auto m = box.GetMatrix();
            glm::mat4 mvp = projection * view * *m;
            glm::mat4 vp = projection * view;
            basicShader.SetUniformMatrix("_MVP", mvp);
            basicShader.SetUniformMatrix("_VP", vp);
            basicShader.SetUniformMatrix("_M", *m);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        
        glBindVertexArray(0);
        // Swap buffers and poll window events
        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return 0;

}
