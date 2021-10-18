#include "Font.h"

#include <vector>
#include "Texture.h"


Font::Font()
{
}

Font::~Font()
{
	for (auto f : mFont)
	{
		TTF_CloseFont(f.second);
	}
	mFont.clear();

}

bool Font::Load(const char * fileName)
{
	std::vector<int> size =
	{
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& s : size)
	{
		TTF_Font * font = TTF_OpenFont(fileName, s);

		if (!font)
		{
			SDL_Log("It could not open Font %s from size %d", fileName, s);

			return false;
		}

		mFont.emplace(s, font);
	}


	return true;
}

Texture * Font::RenderTextBlended(const std::string & text, const Vector3 & color, int size)
{
	Texture * t = nullptr;

	auto it = mFont.find(size);

	if (it != mFont.end())
	{
		SDL_Color sdlColor;

		sdlColor.r = static_cast<Uint8>(color.x * 255);
		sdlColor.g = static_cast<Uint8>(color.y * 255);
		sdlColor.b = static_cast<Uint8>(color.z * 255);
		sdlColor.a = 255;

		SDL_Surface * surface = TTF_RenderText_Blended(it->second, text.c_str(), sdlColor);

		if (surface)
		{
			//Convert surface to texture
			t = new Texture();
			t->ConvertFromSurface(surface);

			SDL_FreeSurface(surface);

		}
	}
	else
	{
		SDL_Log("Font of size %d could not be found.", size);
	}

	return t;
}
