#include <graphics/texture.h>

namespace letc {namespace graphics {

	Texture::Texture(const std::string& filename) {
		m_filename = filename;
#ifdef WATTY_EMSCRIPTEN
		uint8_t* dataToLoad = load_image_from_disk(m_filename.c_str(), &m_width, &m_height);
#else

		Resource* res = Resources::Load(filename.c_str());
		if (res == nullptr) {
			std::cout << "Could not find file: " << filename << std::endl;
			exit(0);
		}

		uint8_t* dataToLoad = load_image(res->data, res->size, &m_width, &m_height);
#endif
		m_TID = load(dataToLoad);
	}

	Texture::Texture()
	{
		m_TID = 0;
	}

	
	// font textures
	Texture::Texture(std::string fileName, unsigned int* atlasID, unsigned int width, unsigned int height, unsigned int depth, const void* data){
		m_filename = std::string("{Font Texture} " + fileName);
		m_width = width;
		m_height = height;
		m_TID = *atlasID;
		
		//// make GL font atlas texture
		glGenTextures(1, atlasID);
		m_TID = *atlasID;
		glBindTexture(GL_TEXTURE_2D, m_TID);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // were linear
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		for (size_t i = 0; i < 512 * 512 * 2 * sizeof(unsigned char); i++)
		{
			//printf("%02x", data[i]);

		}

		switch (depth) {
			case(1):
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, data); //1
				break;
			case(3):
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				break;
			case(4):
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			default:
				//TODO log error
				std::cout << "Bad font Texture Depth: " << depth << std::endl;
				return;
		}
		
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_width, m_height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data); // 2
		
		glBindTexture(GL_TEXTURE_2D, NULL);

	}

	Texture::~Texture()
	{
	}

	Texture* Texture::regenerate( unsigned int width, unsigned int height, const void* data){
		return nullptr; // TODO we are not using this function right now
		m_width = width;
		m_height = height;

		load((uint8_t*)data);

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

	GLuint Texture::load(uint8_t* data){

		if (data == nullptr) {
			std::cout << "Error loading texture: " << m_filename <<" (no data)" << std::endl;
			return 0;
		}

		GLuint output;

		glGenTextures(1, &output); // generate unique glTID
		glBindTexture(GL_TEXTURE_2D, output);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
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


		delete[] data;
		return output;
	}

	bool Texture::isPowerOfTwo(int value)
	{
		return (value & (value - 1)) == 0;
	}


}}