#include "texture.h"
#include "../utils/file_utils.h"

namespace letc {namespace graphics {
	std::vector<const Texture*> Texture::allTextures;


	std::vector<const Texture*> Texture::getAllTextures()
	{
		return std::vector<const Texture*>();
	}

	void Texture::clean()
	{
		for (size_t i = 0; i < allTextures.size(); i++){
			delete allTextures[i];
		}
	}


	Texture::Texture(const std::string& filename) {
		m_filename = filename;
		m_TID = load();
		addGlobalTexture(this);
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
		glBindTexture(GL_TEXTURE_2D, NULL);
		addGlobalTexture(this);
	}

	Texture* Texture::regenerate(unsigned int id, unsigned int width, unsigned int height, const void* data){
		m_width = width;
		m_height = height;
		// remake GL texture
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_width, m_height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, NULL);
		addGlobalTexture(this);

		return this;

	}
	

	void Texture::bind() const{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::unbind() const{
		glBindTexture(GL_TEXTURE_2D, NULL);

	}



	GLuint Texture::load(){
		BYTE* pixels = load_image(m_filename.c_str(), &m_width, &m_height);

		if (pixels == nullptr) {
			std::cout << "Error loading texture: " << m_filename << std::endl;
			return 0;
		}

		GLuint output;
		glGenTextures(1, &output); // generate unique glTID
		glBindTexture(GL_TEXTURE_2D, output);
		
		//TODO this should be a setting
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		//TODO delete pixels
		delete[] pixels;
		return output;
	}

	void Texture::addGlobalTexture(Texture* texture){
		bool found = false;
		for (size_t i = 0; i < allTextures.size(); i++)
		{
			if (allTextures[i]->getID() == texture->getID()) {
				found = true;
				allTextures[i] = texture;
			}
		}
		if (!found) {
			allTextures.push_back(texture);
		}
	}



}}