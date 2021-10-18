#include "SpriteComponent.h"

#include "glew.h"

#include "Texture.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"
#include "Shader.h"
#include <algorithm>


SpriteComponent::SpriteComponent(Actor * owner, int updateOrder)
	:Component(owner, updateOrder)
{
	owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	
	Owner()->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(Texture * texture)
{
	mTexture = texture;

	mWidth = mTexture->TexWidth();
	mHeight = mTexture->TexHeight();
}

void SpriteComponent::Draw(Shader * shader)
{
	if (mTexture)
	{
		Matrix4 temp = Owner()->WorldTransform();
		
		temp *= Matrix4::Scale((float)mWidth, (float)mHeight);

		shader->SetMatrixUniform("mTransformation", temp);

		mTexture->Active();
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
