#include "Debug.h"
void GLClearError() { while (glGetError() != GLFW_NO_ERROR); }

bool GLLogCall(const char* func, const char* file, unsigned int line)
{
	while(GLenum error_code = glGetError())
	{
		std::cout << "[OpenGL Error] (" << std::hex << error_code << std::dec << ") Function: " << func << " File: " << file << " Line: " << line << std::endl;
		return false;
	}
	return true;
}
