#include <graphics/texture.h>

namespace letc {namespace graphics {

	Texture::Texture(const std::string& filename) {
		m_filename = filename;
		m_TID = load();
	}

	// font textures
	Texture::Texture(std::string fileName, unsigned int id, unsigned int width, unsigned int height, const void* data){
		m_filename = std::string("{Font Texture} " + fileName);
		m_TID = id;
		m_width = width;
		m_height = height;
		// make GL texture
		glGenTextures(1, &m_TID);
		glBindTexture(GL_TEXTURE_2D, m_TID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_width, m_height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);

	}

	Texture::~Texture()
	{
	}

	Texture* Texture::regenerate( unsigned int width, unsigned int height, const void* data){
		return nullptr; // TODO we are not using this function right now
		m_width = width;
		m_height = height;

		// remake GL texture
		//glActiveTexture(GL_TEXTURE0 + m_TID);

		glBindTexture(GL_TEXTURE_2D, m_TID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_width, m_height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, m_TID);
	
		return this;

	}
	

	void Texture::bind() const{
		glBindTexture(GL_TEXTURE_2D, m_TID);

	}

	void Texture::unbind() const{
		glBindTexture(GL_TEXTURE_2D, NULL);

	}

	void Texture::bind(unsigned int glActiveTID) const{

		glBindTexture(GL_TEXTURE_2D, m_TID);
	
	}

	void Texture::unbind(unsigned int glActiveTID) const {


		glBindTexture(GL_TEXTURE_2D, NULL);

	}

	GLuint Texture::load(){
		uint8_t* data = load_image(m_filename.c_str(), &m_width, &m_height);

		if (data == nullptr) {
			std::cout << "Error loading texture: " << m_filename << std::endl;
			return 0;
		}

		GLuint output;
		glGenTextures(1, &output); // generate unique glTID
		glBindTexture(GL_TEXTURE_2D, output);
		
		//TODO this should be a setting
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		// NEW
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		delete[] data;
		return output;
	}




}}