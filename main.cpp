#include <cmath>


#include "SEngineX/Engine.h"

#include "SEngineX/Shader.h"
#include "SEngineX/Texture.h"
#include "SEngineX/Transform.h"
#include "SEngineX/Camera.h"
#include "SEngineX/PointLight.h"
#include "SEngineX/DirectionalLight.h"
#include "SEngineX/Mesh.h"
#include "SEngineX/Material.h"
#include "SEngineX/RenderInstruction.h"
#include "SEngineX/Object.h"
#include "SEngineX/util.h"
#include "SEngineX/Serializer.h"
#include "SEngineX/Model.h"
#include "SEngineX/Input.h"

using namespace std;

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
    glm::vec3( 4.2f,  2.0f,  1.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};


enum class InputKey { FORWARD, BACK, LEFT, RIGHT };

class Box : public SEngineX::GameObject {
public:
    shared_ptr<SEngineX::Transform> transform;
    shared_ptr<SEngineX::Mesh> mesh;
    shared_ptr<SEngineX::Material> material;
    
    static int counter;
    int count;
    
    Box() {
        transform = make_shared<SEngineX::Transform>();
        count = counter++;
    }
    
    virtual void  Update() {
        transform->eulerRotation = glm::vec3(0.0f, -(GLfloat)glfwGetTime() * 7.0f * count, 0.0f);
    }
};

int Box::counter = 1;

class FirstPersonController : public SEngineX::GameObject {

public:
	shared_ptr<SEngineX::Camera> cam;

	FirstPersonController() {

	}

	virtual void Update() {
		//rotation
		glm::vec2 rotSpeed = SEngineX::Input::GetMouseDelta() * 10.0f * SEngineX::Time::deltaTime;
		cam->transform->eulerRotation.y -= rotSpeed.x;
		cam->transform->eulerRotation.x -= rotSpeed.y;

		float speed = 3.0f;
		glm::vec3 dir;
		SEngineX::InputManager<InputKey> &inputManager = SEngineX::InputManager<InputKey>::Instance();

		//forward/back
		if (inputManager.IsKeyDown(InputKey::FORWARD)) {
			dir.z -= 1;
		}
		else if (inputManager.IsKeyDown(InputKey::BACK)) {
			dir.z += 1;
		}
		
		//left/right
		if (inputManager.IsKeyDown(InputKey::LEFT)) {
			dir.x -= 1;
		}
		else if (inputManager.IsKeyDown(InputKey::RIGHT)) {
			dir.x += 1;
		}

		glm::vec3 movementVector = cam->transform->TransformDirection(dir) * speed * SEngineX::Time::deltaTime;
		cam->transform->position += movementVector;
	}
};



int main()
{
    SEngineX::Engine &engine = SEngineX::Engine::Instance();
    engine.Init("SEngineX", 800, 600);

	SEngineX::Input::SetCursorMode(SEngineX::CursorMode::DISABLED);
     
	SEngineX::InputManager<InputKey> &inputManager = SEngineX::InputManager<InputKey>::Instance();
	inputManager.AddMapping(InputKey::FORWARD, SEngineX::Key::W);
	inputManager.AddMapping(InputKey::FORWARD, SEngineX::Key::UP);
	inputManager.AddMapping(InputKey::BACK, SEngineX::Key::S);
	inputManager.AddMapping(InputKey::BACK, SEngineX::Key::DOWN);
	inputManager.AddMapping(InputKey::LEFT, SEngineX::Key::A);
	inputManager.AddMapping(InputKey::LEFT, SEngineX::Key::LEFT);
	inputManager.AddMapping(InputKey::RIGHT, SEngineX::Key::RIGHT);
	inputManager.AddMapping(InputKey::RIGHT, SEngineX::Key::D);

    auto mat = SEngineX::Serializer::LoadMaterial("woodfloor");
    auto cubemat = SEngineX::Serializer::LoadMaterial("cubemat");
	auto lightmat = SEngineX::Serializer::LoadMaterial("light");
    
    auto cube = GetCube();
    auto plane = GetPlane();
    
    auto camera = make_shared<SEngineX::Camera>(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    engine.renderer->camera = camera;
    
    camera->transform->eulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    camera->transform->position = glm::vec3(3.0f, 0.5f, 5.0f);
    
    engine.renderer->Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    camera->clearColor = glm::vec4(0.0f, 0.3f, 0.4f, 1.0f);
    
    SEngineX::DirectionalLight dirLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 90.0f, 45.0f));
    SEngineX::PointLight pLight0(pointLightPositions[0], glm::vec3(10.2f, 10.2f, 10.2f));
    //SEngineX::PointLight pLight1(pointLightPositions[1], glm::vec3(0.8f, 0.8f, 0.8f));
    //SEngineX::PointLight pLight2(pointLightPositions[2], glm::vec3(0.8f, 0.8f, 0.8f));
    //SEngineX::PointLight pLight3(pointLightPositions[3], glm::vec3(0.8f, 0.9f, 0.8f));
    
    //SEngineX::PointLight pLight(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f));
    
    vector<SEngineX::RenderInstruction> renderInstructions;

    shared_ptr<Box> box = SEngineX::GameObjectFactory::Create<Box>();
	shared_ptr<FirstPersonController> controller = SEngineX::GameObjectFactory::Create<FirstPersonController>();
	controller->cam = camera;
    
    auto tf = std::make_shared<SEngineX::Transform>();
	//tf->position = glm::vec3(4.0f, 0.0f, 0.0f);
    auto ri = SEngineX::RenderInstruction::Create(plane, mat, tf);
	auto cub = SEngineX::RenderInstruction::Create(cube, cubemat, box->transform);

	lightmat->SetUniform3f("material.color", pLight0.color.r, pLight0.color.g, pLight0.color.b);
	auto light = SEngineX::RenderInstruction::Create(cube, lightmat, pLight0.transform);
	box->transform->position = glm::vec3(4.0f, 0.0f, 0.0f);
    
    //SEngineX::Model model(resourcePath() + "only_quad_sphere.obj");
    //model.meshes[0]->material = mat;
    //model.meshes[1]->material = mat;
   // for(int i = 0; i < 10; i++) {
   //     shared_ptr<Box> box = SEngineX::GameObjectFactory::Create<Box>();
   //     box->transform->position = cubePositions[i];
   //     renderInstructions.push_back(SEngineX::RenderInstruction(mesh, mat, box->transform));
   // }
    
    engine.StartGameLoop();
    
    return 0;
    
}




