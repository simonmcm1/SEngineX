#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <FreeImage.h>

#include <cmath>

#include "Engine.h"
#include "util.h"
#include "ResourcePath.hpp"
#include "Shader.h"
#include "Texture.h"

using namespace std;

int main()
{
    auto engine = SEngineX::Engine::Init("SEngineX", 800, 600);



    
    // load resources, initialize the OpenGL states, ...
    float vertices[] = {
        // Position Color Texcoords
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Bottom-left
    };
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
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
        SEngineX::ShaderAttribute("position", SEngineX::ShaderAttributeType::FLOAT2),
        SEngineX::ShaderAttribute("color", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("texCoord", SEngineX::ShaderAttributeType::FLOAT2)
    };
    
    vector<SEngineX::ShaderAttribute> uniforms {
        SEngineX::ShaderAttribute("_Color", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("_MainTex", SEngineX::ShaderAttributeType::TEXTURE2D),
        SEngineX::ShaderAttribute("_AltTex", SEngineX::ShaderAttributeType::TEXTURE2D)
    };
    
    SEngineX::Shader basicShader("basic", attributes, uniforms);
    basicShader.Use();
    basicShader.EnableAttributes();
    
    SEngineX::Texture2D texture("container.jpg");
    
    SEngineX::Texture2D faceTex("awesomeface.png");

    basicShader.SetUniformTexture("_MainTex", 0);
    basicShader.SetUniformTexture("_AltTex", 1);
    

    
    
    auto t_start = std::chrono::high_resolution_clock::now();
    
    while(!glfwWindowShouldClose(engine->window))
    {
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        
//        basicShader.SetUniform3f("_Color", (std::sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
        
        texture.Bind(0);
        faceTex.Bind(1);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // Swap buffers and poll window events
        glfwSwapBuffers(engine->window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return 0;

}
