#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <wtypes.h>

#include <filesystem>
#include <fstream>
#include <Shader.h>
#include <ObjLoader.h>
#include <VertexArrayObject.h>
#include <Camera.h>

using namespace std;

#define LOG_GL_NOTIFICATIONS

/*
	Handles debug messages from OpenGL
	https://www.khronos.org/opengl/wiki/Debug_Output#Message_Components
	@param source    Which part of OpenGL dispatched the message
	@param type      The type of message (ex: error, performance issues, deprecated behavior)
	@param id        The ID of the error or message (to distinguish between different types of errors, like nullref or index out of range)
	@param severity  The severity of the message (from High to Notification)
	@param length    The length of the message
	@param message   The human readable message from OpenGL
	@param userParam The pointer we set with glDebugMessageCallback (should be the game pointer)
*/
void GlDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::string sourceTxt;
	switch (source) {
	case GL_DEBUG_SOURCE_API: sourceTxt = "DEBUG"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceTxt = "WINDOW"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceTxt = "SHADER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: sourceTxt = "THIRD PARTY"; break;
	case GL_DEBUG_SOURCE_APPLICATION: sourceTxt = "APP"; break;
	case GL_DEBUG_SOURCE_OTHER: default: sourceTxt = "OTHER"; break;
	}
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:          LOG_INFO("[{}] {}", sourceTxt, message); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       LOG_WARN("[{}] {}", sourceTxt, message); break;
	case GL_DEBUG_SEVERITY_HIGH:         LOG_ERROR("[{}] {}", sourceTxt, message); break;
		#ifdef LOG_GL_NOTIFICATIONS
	case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_INFO("[{}] {}", sourceTxt, message); break;
		#endif
	default: break;
	}
}

GLFWwindow* window;
Camera::sptr camera = nullptr;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool initGLFW() {

	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to Initialize GLFW" << std::endl;
		return false;
	}

	int horiz, vert;
	GetDesktopResolution(horiz, vert);
	//Create a new GLFW window
	window = glfwCreateWindow(horiz, vert, "Project Poultry Game", nullptr, nullptr);
	
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, GlfwWindowResizedCallback);

	return true;
}

bool initGLAD() {
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		std::cout << "Failed to initialize Glad" << std::endl;
		return false;
	}
}

GLuint shader_program;

int main()
{
	Logger::Init();

	//Initialize GLFW
	if (!initGLFW())
		return 1;

	//Initialize GLAD
	if (!initGLAD())
		return 1;


	LOG_INFO(glGetString(GL_RENDERER));
	LOG_INFO(glGetString(GL_VERSION));

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GlDebugMessage, nullptr);


	//Vectors for the verticies, uvs, and normals to render (start off empty)
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;


	//Loads the Obj file into an object
	bool load = ObjLoader::LoadFromFile("Models/Monkey.obj", vertices, uvs, normals);


	//Creating the VAO and buffers
	VertexArrayObject::sptr	meshVao = VertexArrayObject::Create();

	VertexBuffer::sptr positions = VertexBuffer::Create();
	positions->LoadData(vertices.data(), vertices.size());

	meshVao->AddVertexBuffer(positions, {
		BufferAttribute(0, 3, GL_FLOAT, false, 0, NULL)
		});

	// Load our shaders
	Shader::sptr shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 4.0f;

	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);

	glEnable(GL_DEPTH_TEST);

	//Creating transformation matricies
	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 transform2 = glm::mat4(1.0f);
	glm::mat4 transform3 = glm::mat4(1.0f);
	glm::mat4 transform4 = glm::mat4(1.0f);

	//Sets the inital positions of the 2 objs
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform2 = transform * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));
	transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(230.0f), glm::vec3(1, 0, 0));
	//transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(125.0f), glm::vec3(1, 0, 0));
	//transform3 = glm::translate(transform, glm::vec3(3.0f, 0.0f, 0.0f));


	camera = Camera::Create();
	camera->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camera->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera->SetFovDegrees(90.0f); // Set an initial FOV


	double lastFrame = glfwGetTime();

	//Main Loop//
	while (!glfwWindowShouldClose(window)) {

		//Close the window
		processInput(window);

		glfwPollEvents();

		// Calculate the time since our last frame (dt)
		double thisFrame = glfwGetTime();
		float dt = static_cast<float>(thisFrame - lastFrame);


		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.0001f * dt, 0.0f, 0.0f));
			transform2 = transform * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0));
			transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(0, 0, 1));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(-0.0001f * dt, 0.0f, 0.0f));
			transform2 = transform * glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0, 1, 0));
			transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(240.0f), glm::vec3(0, 0, 1));
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.0f, -0.0001f * dt, 0.0f));
			transform2 = transform * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 1, 0));
			transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(150.0f), glm::vec3(1, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.0f, 0.0001f * dt, 0.0f));
			transform2 = transform * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));
			transform2 = transform2 * glm::rotate(glm::mat4(1.0f), glm::radians(230.0f), glm::vec3(1, 0, 0));
		}

		//transform4 = transform3 * glm::rotate(glm::mat4(1.0f), static_cast<float>(thisFrame), glm::vec3(0, 1, 0));

		glClearColor(0.5f, 0.5f, 0.5f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Bind();
		//Renders the first obj in the correct position with rotation
		shader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform2);
		shader->SetUniformMatrix("u_Model", transform2);
		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform2));
		meshVao->Render();


		glfwSwapBuffers(window);
	}
	Logger::Uninitialize();
	return 0;
}