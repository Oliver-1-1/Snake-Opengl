#include "Window.h"

Window::Window(int width, int height, std::string title)
{
	settings.height = height;
	settings.width = width;
	settings.title = title;

	if (!init())
		std::cout << "Init for window failed!\n";

}

Window::~Window()
{
	destroy();
}

bool Window::init()
{

    if (!glfwInit())
        return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
		return false;
    }

    glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glfwSwapInterval(1);

	return true;
}

bool Window::destroy()
{
	glfwTerminate();
	return true;
}
