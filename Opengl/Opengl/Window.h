#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window
{
public:
	GLFWwindow* window;


	Window(int width, int height, std::string title); // Start values
	~Window();

	private:bool init();
	static bool destroy();

	struct window_settings
	{
		int width, height;
		std::string title;
	}settings;

};

