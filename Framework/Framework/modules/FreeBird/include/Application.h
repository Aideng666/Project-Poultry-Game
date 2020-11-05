#pragma once
#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <wtypes.h>

#include <filesystem>
#include <fstream>

//Referenced in conjunction with NOU and Shawn's setup of a window from the CG Tutorials//

namespace freebird
{
	class Application
	{
	public:
		//Inits a window
		//static void Init(const std::string name, int w, int h);
		static GLFWwindow* Init(std::string name, int w, int h);

		//Sets the clear color of the window
		static void SetClearColor(const glm::vec4& color);

		static void Update();
		static void SwapBuffers();

	private:
		static GLFWwindow* m_window;
	};
}