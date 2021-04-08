#include "Application.h"
#include <Framebuffer.h>
#include <AudioEngine.h>

namespace freebird
{
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

	GLFWwindow* Application::m_window = nullptr;
	float Application::m_thisFrame = 0.0f;
	float Application::m_dt = 0.0f;
	std::vector<std::function<void()>> Application::imGuiCallbacks;

	void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) 
	{
		glViewport(0, 0, width, height);
	}

	//Initializes a window
	GLFWwindow* Application::Init(std::string name, int w, int h)
	{
		Logger::Init();

		//Checks for initialization of GLFW
		if (glfwInit() == GLFW_FALSE) 
		{
			std::cout << "Failed to Initialize GLFW" << std::endl;	
			throw std::runtime_error("GLFW init failed");			
		}

		glfwWindowHint(GLFW_RESIZABLE, false);

		m_window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		glfwSetWindowSizeCallback(m_window, GlfwWindowResizedCallback);

		//Checks for initialization of GLAD
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) 
		{
			std::cout << "Failed to initialize Glad" << std::endl;
			throw std::runtime_error("GLAD init failed");
		}

		LOG_INFO(glGetString(GL_RENDERER));
		LOG_INFO(glGetString(GL_VERSION));

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GlDebugMessage, nullptr);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);

		//Default clear color to white
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		Framebuffer::InitFullscreenQuad();

		return m_window;
	}

	//Sets the clear color of the window
	void Application::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	//Polls events and updates timer
	void Application::Update()
	{		
		Tick();

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	//Allows use of ESC key to close screen
	void Application::ProcessInput(GLFWwindow* window)
	{
		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			//glfwSetWindowShouldClose(window, true);
	}

	void Application::Cleanup()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	float Application::GetDT()
	{
		return m_dt;
	}

	void Application::Tick()
	{
		float lastFrame = glfwGetTime();
		m_dt = lastFrame - m_thisFrame;
		m_thisFrame = lastFrame;
	}

	bool Application::IsClosing()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Application::InitImGui()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_TransparentBackbuffers;
		
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		
		ImGui::StyleColorsDark();
		
		ImGuiStyle& style = ImGui::GetStyle();
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 0.8f;
		}
	}

	void Application::ShutdownImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Application::RenderImGui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff
			for (auto& func : imGuiCallbacks) {
				func();
			}
		}
		ImGui::End();

		// Make sure ImGui knows how big our window is
		ImGuiIO& io = ImGui::GetIO();
		int width{ 0 }, height{ 0 };
		glfwGetWindowSize(m_window, &width, &height);
		io.DisplaySize = ImVec2((float)width, (float)height);

		// Render all of our ImGui elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// If we have multiple viewports enabled (can drag into a new window)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			// Update the windows that ImGui is using
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			// Restore our gl context
			glfwMakeContextCurrent(m_window);
		}
	}

	void Application::LoadAudio()
	{
		AudioEngine& audioEngine = AudioEngine::Instance();

		audioEngine.Init();
		//Loads the bank
		audioEngine.LoadBank("Sounds/Master");

		//Loads the bus
		AudioEngine::Instance().LoadBus("MusicBus", "{aa712c3f-3f70-472f-8ddd-d7ee091ff0fe}");
		AudioEngine::Instance().LoadBus("SoundBus", "{19d186f5-e8be-40df-b1d2-ce3cf6c59f92}");

		AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.2f);
		AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.5f);

		//Creates the sound events
		AudioEvent& BG = AudioEngine::Instance().CreateSoundEvent("BG", "{beba64b3-3176-4f20-9f00-7f32807325b6}"); //Background music
		AudioEvent& walk = AudioEngine::Instance().CreateSoundEvent("Walk", "{858d6f38-82a8-4477-8e80-5a6b52fd1313}"); //Walk SFX
		AudioEvent& door = AudioEngine::Instance().CreateSoundEvent("Door", "{24678d0f-f199-4d73-95dc-10657db09e8a}"); //Door SFX
		AudioEvent& levelComplete = AudioEngine::Instance().CreateSoundEvent("Level Complete", "{03daedd8-d89f-4d92-917f-43d3b74e73ef}"); //Level Complete SFX

		
	}
}