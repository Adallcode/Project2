#pragma once

#include "SDL.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const char *file);

	void Active();


	//Get/Set
	void SetTexWidth(int width) { mTexWidth = width; }
	void SetTexHeight(int height) { mTexHeight = height; }

	int TexWidth()const { return mTexWidth; }
	int TexHeight()const { return mTexHeight; }

	//Convert a surface to texture
	void ConvertFromSurface(SDL_Surface * surface);


private:
	unsigned int mTextureId;

	int mTexWidth;
	int mTexHeight;

};

