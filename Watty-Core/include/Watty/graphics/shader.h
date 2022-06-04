#pragma once
#include <vector>

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#include <GLES3/gl32.h>

#else
#include <glad/glad.h>
#endif

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "../utils/file_utils.h"
//
#define DEFAULT_SHADER_VERT_PATH "shaders/default.vert"
#define DEFAULT_SHADER_FRAG_PATH "shaders/default.frag"

namespace watty {namespace graphics {
	class Shader {
	private:
		unsigned int m_shaderID = (uint32_t)-1;
		const char* m_vertPath = "";
		const char* m_fragPath = "";
		static const char* m_defaultVertPath;
		static const char* m_defaultFragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		Shader();
		Shader(bool ECS);
		~Shader();


		void setUniform1f(const char* name, float value);
		void setUniform1fv(const char* name,  float* value, int count);
		void setUniform1iv(const char* name,  int* value, int count);
		void setUniform1i(const char* name, int value);
		
		void setUniform2f(const char* name, const glm::vec2& vector);
		void setUniform3f(const char* name, const glm::vec3& vector);
		void setUniform4f(const char* name, const glm::vec4& vector);
		
		void setUniformMat4(const char* name, const glm::mat4& matrix);
		inline int getID() { return m_shaderID; }

		void enable() const;
		void disable() const;
		int getUniformLocation(const char* name);
		void init();
		inline std::string getFragPath(){return m_fragPath;}
		inline std::string getVertPath(){return m_vertPath;}

	private:
		unsigned int load();

	};

}}
