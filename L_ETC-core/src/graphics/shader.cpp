#include "shader.h"

namespace letc {namespace graphics {
	
	Shader::Shader(const char* vertPath, const char* fragPath){
		m_vertPath = vertPath;
		m_fragPath= fragPath;
		m_shaderID = load();


		GLint texIDs[32];
		for (size_t i = 0; i < 32; i++)
			texIDs[i] = i;
		enable();
		setUniform1iv("textures", texIDs, 32);

	}

	Shader::~Shader(){
		glDeleteProgram(m_shaderID);
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_shaderID, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value){
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, float* value, int count){
		glUniform1fv(getUniformLocation(name),count, value);
	}
	void Shader::setUniform1iv(const GLchar* name, int* value, int count){
		glUniform1iv(getUniformLocation(name),count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value){
		glUniform1i(getUniformLocation(name), value);

	}

	void Shader::setUniform2f(const GLchar* name, const math::Vector2& vector){
		glUniform2f(getUniformLocation(name), vector.x, vector.y);

	}

	void Shader::setUniform3f(const GLchar* name, const math::Vector3& vector){
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

	}

	void Shader::setUniform4f(const GLchar* name, const math::Vector4& vector){
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);

	}

	void Shader::setUniformMat4(const GLchar* name, const math::Matrix4& matrix){
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);

	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		
		std::string vertSourceString = read_file(m_vertPath);
		std::string fragSourceString = read_file(m_fragPath);
			
		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);

		glCompileShader(vertex);

		GLint resultVert;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &resultVert);

		if (resultVert == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader :( " << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}
		
		glShaderSource(fragment, 1, &fragSource, NULL);

		glCompileShader(fragment);

		GLint resultFrag;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &resultFrag);

		if (resultFrag == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader :( " <<std::endl<< &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}
		
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::enable() const{
		glUseProgram(m_shaderID);
	}

	void Shader::disable() const {
		glUseProgram(0);
	}




}
}