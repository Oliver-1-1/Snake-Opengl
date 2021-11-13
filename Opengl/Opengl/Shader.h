#pragma once
#include <GL/glew.h>
#include "Debug.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>

class Shader
{
public:
	int program;
	const char*& get_file(const std::string& path);
	const char* fragmentShaderSource;

	void set_vec4(const std::string& name, const glm::vec4& value);
	void set_mat4(const std::string& name, const glm::mat4& value);

	Shader(std::string vert, std::string frag);
	~Shader();

private:
	unsigned int vertex_shader_;
	unsigned int fragment_shader_;
	std::string* shader_source;
	void link_shaders(const std::string& vert, const std::string& frag);

};

