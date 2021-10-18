#pragma once

#include <unordered_map>
#include <string>

#include "SDL_ttf.h"
#include "Math.h"

class Font
{
public:
	Font();
	~Font();

	bool Load(const char * fileName);

	class Texture * RenderTextBlended(const std::string& text, const Vector3& color = Color::White, int size = 30);

private:
	std::unordered_map<int, TTF_Font *> mFont;


};

