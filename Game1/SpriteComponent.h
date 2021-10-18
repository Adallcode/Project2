#pragma once
#include "Component.h"


class SpriteComponent :
	public Component
{
public:
	SpriteComponent(class Actor * owner, int updateOrder = 100);
	~SpriteComponent();

	void SetTexture(class Texture * texture);

	void Draw(class Shader * shader);


private:
	class Texture * mTexture;

	int mWidth, mHeight;

};

