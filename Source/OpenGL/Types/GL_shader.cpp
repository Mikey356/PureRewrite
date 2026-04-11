#include "GL_shader.h"
#include "Types/enums.h"
#include <iostream>



bool ParseShaderSource(const std::string& filepath, std::string& output);
PureResult CheckCompilationErrors(GLuint shader, const std::string& type);

void Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;

	if (!ParseShaderSource(vertexPath, vertexSource)) return;
	if (!ParseShaderSource(fragmentPath, fragmentSource)) return;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();

	// Compile shaders
	unsigned int vert, frag;

	// vertex shader
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vShaderCode, NULL);
	glCompileShader(vert);
	CheckCompilationErrors(vert, "VERTEX");

	// fragment shader
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fShaderCode, NULL);
	glCompileShader(frag);
	CheckCompilationErrors(frag, "FRAGMENT");

	// Shader Program
	m_handle = glCreateProgram();
	glAttachShader(m_handle, vert);
	glAttachShader(m_handle, frag);
	glLinkProgram(m_handle);
	CheckCompilationErrors(m_handle, "PROGRAM");
						
	// Cleanup
	glDeleteShader(vert);
	glDeleteShader(frag);
	
	// Store paths for hotloading
	m_vertexPath = vertexPath;
	m_fragmentPath = fragmentPath;
}

void Shader::Hotload()
{
	std::string vertexSource;
	std::string fragmentSource;

	if (!ParseShaderSource(m_vertexPath, vertexSource)) return;
	if (!ParseShaderSource(m_fragmentPath, fragmentSource)) return;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();

	// Compile shaders
	unsigned int vert, frag;

	// vertex shader
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vShaderCode, NULL);
	glCompileShader(vert);
	CheckCompilationErrors(vert, "VERTEX");

	// fragment shader
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fShaderCode, NULL);
	glCompileShader(frag);
	CheckCompilationErrors(frag, "FRAGMENT");

	// Shader Program
	int tempHandle = glCreateProgram();
	glAttachShader(tempHandle, vert);
	glAttachShader(tempHandle, frag);

	glLinkProgram(tempHandle);

	// Only update the handle if the hotload was successful
	if (CheckCompilationErrors(tempHandle, "PROGRAM") == PureResult::SUCCESS) m_handle = tempHandle;

	// Cleanup
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::Bind() const {
	glUseProgram(m_handle);
}


void Shader::SetBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_handle, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_handle, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_handle, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(m_handle, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(m_handle, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(m_handle, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(m_handle, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(m_handle, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(m_handle, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_handle, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_handle, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_handle, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

PureResult CheckCompilationErrors(GLuint shader, const std::string& type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			return PureResult::FAILURE;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			return PureResult::FAILURE;
		}
	}

	return PureResult::SUCCESS;
}

bool ParseShaderSource(const std::string& filepath, std::string& output)
{
	std::ifstream file;

	// Open file
	file.open(filepath);
	if (!file.is_open())
	{
		std::cout << "Failed to open " << filepath << std::endl;
		return false;
	}


	// Cead file's content into a stringstream
	std::stringstream stringstream;
	stringstream << file.rdbuf();

	// Close file
	file.close();

	// convert streamstring into string
	output = stringstream.str();
	return true;
}
