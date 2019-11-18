#pragma once
#include <vector>
#include <GL/glew.h>
#include "../math/math.h"
#include "../math/matrix4.h"
#include "../utils/file_utils.h"

namespace letc {namespace graphics {
	class Shader {
	private:
		GLuint m_shaderID;
		const char* m_vertPath;
		const char* m_fragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();


		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name,  float* value, int count);
		void setUniform1iv(const GLchar* name,  int* value, int count);
		void setUniform1i(const GLchar* name, int value);
		
		void setUniform2f(const GLchar* name, const math::Vector2& vector);
		void setUniform3f(const GLchar* name, const math::Vector3& vector);
		void setUniform4f(const GLchar* name, const math::Vector4& vector);
		
		void setUniformMat4(const GLchar* name, const math::Matrix4& matrix);


		void enable() const;
		void disable() const;
	private:
		GLint getUniformLocation(const GLchar* name);
		GLuint load();

	};

}}
