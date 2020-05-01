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
		std::cout << "gen texture " << m_TID << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		std::cout << "wrap t" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		std::cout << "wrap s" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		std::cout << "mag" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		std::cout << "min" << std::endl;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_width, m_height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);

		std::cout << "..texture generated" << std::endl;

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

		std::cout << "Loading Texture: " << m_filename << std::endl;
		GLuint output;

		glGenTextures(1, &output); // generate unique glTID
		glBindTexture(GL_TEXTURE_2D, output);
		
		//TODO this should be a setting
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		if (isPowerOfTwo(m_width) && isPowerOfTwo(m_height)) {
			// Yes, it's a power of 2. Generate mips.
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		std::cout << "Loaded Texture: " << m_filename <<" With ID:" << output << std::endl;
		delete[] data;
		return output;
	}

	bool Texture::isPowerOfTwo(int value)
	{
		return (value & (value - 1)) == 0;
	}


}}