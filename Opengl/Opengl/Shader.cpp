#include "Shader.h";


void Shader::set_vec4(const std::string& name, const glm::vec4& value)
{
	GLCall(int location = glGetUniformLocation(program, name.c_str()));
	ASSERT(location != -1);
	GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
}

void Shader::set_mat4(const std::string& name, const glm::mat4& value)
{
	GLCall(int location = glGetUniformLocation(program, name.c_str()));
	ASSERT(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

Shader::Shader(std::string vert, std::string frag)
{
	link_shaders(vert, frag);
}


Shader::~Shader()
{
	delete [] shader_source;
}

void Shader::link_shaders(const std::string& vert, const std::string& frag)
{
	vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertex_shader_, 1, &get_file(vert), NULL));
	GLCall(glCompileShader(vertex_shader_));

	fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
	
	GLCall(glShaderSource(fragment_shader_, 1, &get_file(frag), NULL));
	GLCall(glCompileShader(fragment_shader_));

	int suc;
	GLCall(glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &suc));
	GLCall(glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &suc));
	program = glCreateProgram();
	GLCall(glAttachShader(program, vertex_shader_));
	GLCall(glAttachShader(program, fragment_shader_));
	GLCall(glLinkProgram(program));

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &suc));

	GLCall(glDeleteShader(vertex_shader_));
	GLCall(glDeleteShader(fragment_shader_));

}

const char*& Shader::get_file(const std::string& path)
{
	std::fstream f;
	shader_source = new std::string;
	const char* content;
	*shader_source = "";

	f.open(path, std::fstream::in | std::ios_base::binary);
	if (!f.is_open())
	{
		std::cout << "File not found, returning empty string\n";
		content = shader_source->c_str();
		return *&content;
	}

	getline(f, *shader_source, '\0');
	f.close();
	content = shader_source->c_str();
	return *&content; // Some crazy ass shit i dont quit understand but it works. Should mean reference to a pointer. So the adress of the pointer
}