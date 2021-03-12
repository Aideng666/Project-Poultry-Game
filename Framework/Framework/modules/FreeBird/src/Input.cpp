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

	void Input::MovePlayer(GLFWwindow* window, Entity player, Entity camEnt, float dt, bool camFar, bool camClose, bool camLeft, bool camRight)
	{
		auto& playerTrans = player.Get<Transform>();
		auto& camera = camEnt.Get<Camera>();

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(225.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

			if (camRight)
				camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

			player.Get<MorphAnimation>().Update(dt);
		}

		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(315.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

			if (camRight)
				camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

			player.Get<MorphAnimation>().Update(dt);
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(45.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

			if (camLeft)
				camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

			player.Get<MorphAnimation>().Update(dt);
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			playerTrans.SetRotationY(135.0f);

			playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

			if (camLeft)
				camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

			player.Get<MorphAnimation>().Update(dt);
		}

		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveLeft())
			{
				playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
				playerTrans.SetRotationY(270.0f);
				
				if (camRight)
					camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

				player.Get<MorphAnimation>().Update(dt);
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveRight())
			{
				playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
				playerTrans.SetRotationY(90.0f);
				
				if (camLeft)
					camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));

				player.Get<MorphAnimation>().Update(dt);
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveUp())
			{
				playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
				playerTrans.SetRotationY(180.0f);

				if (camFar)
					camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

				player.Get<MorphAnimation>().Update(dt);
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{

			if (playerTrans.GetCanMoveDown())
			{
				playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
				playerTrans.SetRotationY(0.0f);

				if (camClose)
					camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

				player.Get<MorphAnimation>().Update(dt);
			}
		}
	}

	void Input::MoveCamera(GLFWwindow* window, Entity camEnt, float dt)
	{
		auto& camera = camEnt.Get<Camera>();

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 10 * dt, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 10 * dt, camera.GetPosition().z));
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
}