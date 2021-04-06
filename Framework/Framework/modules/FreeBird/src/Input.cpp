#include "Input.h"
#include <GLFW/glfw3.h>
#include <Lever.h>
#include <iostream>

namespace freebird
{
	KeyPressWatcher::KeyPressWatcher(int keyCode, const std::function<void()>& onPressed)
	{
		_isPressed = false;
		_keyCode = keyCode;
		_onPressed = onPressed;
		
	}

	bool KeyPressWatcher::Poll(GLFWwindow* window) const
	{
		if (glfwGetKey(window, _keyCode) == GLFW_PRESS) {
			if (!_isPressed) {
				_isPressed = true;
				if (_onPressed) {
					_onPressed();
				}
			}
			return false;
		}
		else {
			_isPressed = false;
		}
		return false;
	}

	bool Input::MovePlayer(GLFWwindow* window, Entity player, Entity camEnt, float dt, bool camFar, bool camClose, bool camLeft, bool camRight)
	{
		auto& playerTrans = player.Get<Transform>();
		auto& camera = camEnt.Get<Camera>();

		if (!glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			return false;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(225.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() - 15 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 15 * dt);

			if (camRight)
				camera.SetPosition(glm::vec3(camera.GetPosition().x - 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 15 * dt));

			return true;
		}

		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(315.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() - 15 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 15 * dt);

			if (camRight)
				camera.SetPosition(glm::vec3(camera.GetPosition().x - 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 15 * dt));

			return true;
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(45.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() + 15 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 15 * dt);

			if (camLeft)
				camera.SetPosition(glm::vec3(camera.GetPosition().x + 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 15 * dt));

			return true;
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(135.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() + 15 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 15 * dt);

			if (camLeft)
				camera.SetPosition(glm::vec3(camera.GetPosition().x + 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 15 * dt));

			return true;
		}

		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveLeft())
			{
				playerTrans.SetPositionX(playerTrans.GetPositionX() - 15 * dt);
				playerTrans.SetRotationY(270.0f);
				
				if (camRight)
					camera.SetPosition(glm::vec3(camera.GetPosition().x - 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

				return true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveRight())
			{
				playerTrans.SetPositionX(playerTrans.GetPositionX() + 15 * dt);
				playerTrans.SetRotationY(90.0f);
				
				if (camLeft)
					camera.SetPosition(glm::vec3(camera.GetPosition().x + 15 * dt, camera.GetPosition().y, camera.GetPosition().z));

				return true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveUp())
			{
				playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 15 * dt);
				playerTrans.SetRotationY(180.0f);

				if (camFar)
					camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 15 * dt));

				return true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveDown())
			{
				playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 15 * dt);
				playerTrans.SetRotationY(0.0f);

				if (camClose)
					camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 15 * dt));

				return true;
			}
		}
	}

	void Input::MoveCamera(GLFWwindow* window, Entity camEnt, float dt)
	{
		auto& camera = camEnt.Get<Camera>();

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x - 15 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x + 15 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 15 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 15 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 15 * dt, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 15 * dt, camera.GetPosition().z));
		}
	}

	int Input::ChangeLighting(GLFWwindow* window, int lightNum)
	{
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			return 1;
		}
		else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			return 2;
		}
		else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			return 3;
		}
		else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			return 4;
		}
		else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		{
			return 5;
		}
		else
		{
			return lightNum;
		}
	}
	Camera& Input::ToggleCam(Entity mainPlayer, Entity camEnt, Entity topEnt, bool topView, bool& camChanged, bool& topChanged)
	{
		auto& camera = camEnt.Get<Camera>();

		if (topView)
		{
			camera = topEnt.Get<Camera>();
			if (!topChanged)
			{
				camera.SetPosition(topEnt.Get<Camera>().GetPosition()); // Set initial position
				camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
				camera.LookAt(glm::vec3(0.0f, 0.0f, topEnt.Get<Camera>().GetPosition().z));
				topChanged = true;
				camChanged = false;
			}
		}
		else if (!topView && !camChanged)
		{
			camera = camEnt.Get<Camera>();
			if (!camChanged)
			{
				camera.SetPosition(glm::vec3(mainPlayer.Get<Transform>().GetPositionX(), 12, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position 
				camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
				camera.LookAt(glm::vec3(mainPlayer.Get<Transform>().GetPositionX(), mainPlayer.Get<Transform>().GetPositionY() + 5.0f, mainPlayer.Get<Transform>().GetPositionZ()));
				camChanged = true;
				topChanged = false;
			}
		}

		return camera;
	}
}