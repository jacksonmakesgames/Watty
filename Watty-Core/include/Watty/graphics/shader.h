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

//#include "../math/matrix4.h"
#include "../utils/file_utils.h"

namespace letc {namespace graphics {
	class Shader {
	private:
		unsigned int m_shaderID;
		const char* m_vertPath;
		const char* m_fragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		Shader();
		~Shader();


		void setUniform1f(const char* name, float value);
		void setUniform1fv(const char* name,  float* value, int count);
		void setUniform1iv(const char* name,  int* value, int count);
		void setUniform1i(const char* name, int value);
		
		void setUniform2f(const char* name, const glm::vec2& vector);
		void setUniform3f(const char* name, const glm::vec3& vector);
		void setUniform4f(const char* name, const glm::vec4& vector);
		
		void setUniformMat4(const char* name, const glm::mat4& matrix);


		void enable() const;
		void disable() const;
	private:
		int getUniformLocation(const char* name);
		unsigned int load();
		void init();

	};

}}
