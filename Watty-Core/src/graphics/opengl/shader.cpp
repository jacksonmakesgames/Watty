#include <graphics/shader.h>

namespace letc {namespace graphics {
	
	Shader::Shader(const char* vertPath, const char* fragPath){
		m_vertPath = vertPath;
		m_fragPath= fragPath;
		init();
	}

	Shader::Shader()
	{
#ifdef WATTY_EMSCRIPTEN
		m_vertPath = WATTYRESDIR "shaders/default_es3.vert";
		m_fragPath = WATTYRESDIR "shaders/default_es3.frag";
#else
		m_vertPath = WATTYRESDIR "shaders/default.vert";
		m_fragPath = WATTYRESDIR "shaders/default.frag";
#endif // WATTY_EMSCRIPTEN

		init();

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

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector){
		glUniform2f(getUniformLocation(name), vector.x, vector.y);

	}

	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector){
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector){
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);

	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix){

		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix[0]));

	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::vector<char> vertChars = read_file(m_vertPath);
		std::vector<char> fragChars = read_file(m_fragPath);

		std::string vertSourceString(vertChars.begin(), vertChars.end());
		std::string fragSourceString(fragChars.begin(), fragChars.end());
			
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

	void Shader::init()
	{
		m_shaderID = load();
		enable();
#ifndef WATTY_EMSCRIPTEN
		GLint texIDs[32];
		for (size_t i = 0; i < 32; i++)
			texIDs[i] = i;

		setUniform1iv("textures", texIDs, 32);
#else

		setUniform1i("texture_0", 0);
		setUniform1i("texture_1", 1);
		setUniform1i("texture_2", 2);
		setUniform1i("texture_3", 3);
		setUniform1i("texture_4", 4);
		setUniform1i("texture_5", 5);
		setUniform1i("texture_6", 6);
		setUniform1i("texture_7", 7);
		setUniform1i("texture_8", 8);
		setUniform1i("texture_9", 9);
		setUniform1i("texture_10", 10);
		setUniform1i("texture_11", 11);
		setUniform1i("texture_12", 12);
		setUniform1i("texture_13", 13);
		setUniform1i("texture_14", 14);
		setUniform1i("texture_15", 15);
#endif //!WATTY_EMSCRIPTEN
		disable();
	}

	void Shader::enable() const{
		glUseProgram(m_shaderID);
	}

	void Shader::disable() const {
		glUseProgram(0);
	}




}
}