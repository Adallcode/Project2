#include "Texture.h"

#include "SOIL.h"
#include "SDL.h"
#include "glew.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTextureId);
}

bool Texture::Load(const char * file)
{
	int channel = 0;

	unsigned char * image = SOIL_load_image(file, &mTexWidth, &mTexHeight, &channel, SOIL_LOAD_AUTO);

	if (!image)
	{
		SDL_Log("Image could not be loaded. %s %s", file, SOIL_last_result());
		return false;
	}


	int format = GL_RGB;
	if (channel == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);


	glTexImage2D(GL_TEXTURE_2D, 0, format, mTexWidth, mTexHeight, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);


	// Enable linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return true;
}

void Texture::Active()
{
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void Texture::ConvertFromSurface(SDL_Surface * surface)
{
	mTexWidth = surface->w;
	mTexHeight = surface->h;

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTexWidth, mTexHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, surface->pixels);


	// Enable linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
