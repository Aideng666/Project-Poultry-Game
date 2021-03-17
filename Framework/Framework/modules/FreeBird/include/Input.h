#pragma once

#include <functional>
#include <Entity.h>
#include <Transform.h>
#include <Camera.h>
#include <MorphAnimation.h>

struct GLFWwindow;

namespace freebird
{
	struct KeyPressWatcher final
	{
	public:
		KeyPressWatcher(int keyCode, const std::function<void()>& onPressed);
		~KeyPressWatcher() = default;

		bool Poll(GLFWwindow* window) const;

	protected:
		int _keyCode;
		mutable bool _isPressed;
		std::function<void()> _onPressed;
	};


	class Input
	{
	public:

		static void MovePlayer(GLFWwindow* window, Entity player, Entity camEnt, float dt, bool camFar, bool camClose, bool camLeft, bool camRight);
		static void MoveCamera(GLFWwindow* window, Entity camEnt, float dt);
		static int ChangeLighting(GLFWwindow* window, int lightNum);
	};
}