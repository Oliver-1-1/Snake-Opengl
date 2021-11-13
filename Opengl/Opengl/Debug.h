#pragma once
#include <GLFW/glfw3.h>
#include <iostream>


#define ASSERT(x) if (!(x)) __debugbreak(); // Error logic by Cherno. Looked at it and thought it was a pretty soild method. I did some improvments
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* func, const char* file, unsigned int line);

