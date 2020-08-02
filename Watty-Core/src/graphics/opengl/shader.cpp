#include <graphics/shader.h>

namespace letc {namespace graphics {

#ifdef WATTY_EMSCRIPTEN
	const char* Shader::m_defaultVertPath = "shaders/default_es3.vert";
	const char* Shader::m_defaultFragPath = "shaders/default_es3.frag";
#else
	const char* Shader::m_defaultVertPath= "shaders/default.vert";
	const char* Shader::m_defaultFragPath= "shaders/default.frag";
#endif

	Shader::Shader(const char* vertPath, const char* fragPath){
		m_vertPath = vertPath;
		m_fragPath= fragPath;
		init();
	}

	Shader::Shader()
	{
		m_vertPath = m_defaultVertPath;
		m_fragPath = m_defaultFragPath;

		init();

	}

	Shader::~Shader(){
		glDeleteProgram(m_shaderID);
	}

	int Shader::getUniformLocation(const char* name)
	{
		return glGetUniformLocation(m_shaderID, name);
	}

	void Shader::setUniform1f(const char* name, float value){
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const char* name, float* value, int count){
		glUniform1fv(getUniformLocation(name),count, value);
	}
	void Shader::setUniform1iv(const char* name, int* value, int count){
		glUniform1iv(getUniformLocation(name),count, value);
	}

	void Shader::setUniform1i(const char* name, int value){
		glUniform1i(getUniformLocation(name), value);

	}

	void Shader::setUniform2f(const char* name, const glm::vec2& vector){
		glUniform2f(getUniformLocation(name), vector.x, vector.y);

	}

	void Shader::setUniform3f(const char* name, const glm::vec3& vector){
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

	}

	void Shader::setUniform4f(const char* name, const glm::vec4& vector){
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);

	}

	void Shader::setUniformMat4(const char* name, const glm::mat4& matrix){

		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix[0]));

	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertSource = "";
		const char* fragSource = "";
		std::string vertSourceString;
		std::string fragSourceString;

		if (m_vertPath[0] != '\0'){
			// Load Custom Shader:
			std::vector<char> vertChars = read_file(m_vertPath);
			if (vertChars.size() <= 0) {
				std::cout << "Error loading vert shader" << std::endl;
			}
			vertSourceString = std::string(vertChars.begin(), vertChars.end());
			vertSource = vertSourceString.c_str();
		}
		else {
			m_vertPath = m_defaultVertPath;
			std::cout << "No vert shader path provided, using default" << std::endl;
		}

		if (m_fragPath[0] != '\0') {
			// Load Custom Shader:
			std::vector<char> fragChars = read_file(m_fragPath);
			if (fragChars.size() <= 0) {
				std::cout << "Error loading frag shader" << std::endl;
			}
			fragSourceString = std::string(fragChars.begin(), fragChars.end());
			fragSource = fragSourceString.c_str();
		}
		else {
			m_fragPath = m_defaultFragPath;
			// TODO log warning
			std::cout << "No frag shader path provided, using default" << std::endl;
		}
		
		glShaderSource(vertex, 1, &vertSource, NULL);

		glCompileShader(vertex);

		int resultVert;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &resultVert);

		if (resultVert == GL_FALSE) {
			int length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile custom vertex shader :( " << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}
		
		glShaderSource(fragment, 1, &fragSource, NULL);

		glCompileShader(fragment);

		int resultFrag;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &resultFrag);
		if (resultFrag == GL_FALSE) {
			int length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile custom fragment shader :( " <<std::endl<< &error[0] << std::endl;
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
		int texIDs[32];
		for (size_t i = 0; i < 32; i++)
			texIDs[i] = i;

		setUniform1iv("textures", texIDs, 32);
#else

		setUniform1i("textures_0", 0);
		setUniform1i("textures_1", 1);
		setUniform1i("textures_2", 2);
		setUniform1i("textures_3", 3);
		setUniform1i("textures_4", 4);
		setUniform1i("textures_5", 5);
		setUniform1i("textures_6", 6);
		setUniform1i("textures_7", 7);
		setUniform1i("textures_8", 8);
		setUniform1i("textures_9", 9);
		setUniform1i("textures_10", 10);
		setUniform1i("textures_11", 11);
		setUniform1i("textures_12", 12);
		setUniform1i("textures_13", 13);
		setUniform1i("textures_14", 14);
		setUniform1i("textures_15", 15);
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