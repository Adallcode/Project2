#include "UIBase.h"

#include "Font.h"
#include "Texture.h"
#include "Game.h"
#include "Shader.h"
#include "Renderer.h"

UIBase::UIBase(Game * game)
	:mGame(game),
	mTitleTex(nullptr),
	mBackgroundTexture(nullptr),
	mPosition(Vector3(0.f, 200.0f, 0.0f)),
	mNextButtonPos(Vector3(0.f, 100.0f, 0.f)),
	mState(EActive)
{
	mFont = game->GetFont("Assets/Carlito-Regular.ttf");

	//Blue color for button on
	mButtonOn = game->GetRenderer()->GetTexture("Assets/ButtonBlue.png");
	//Yellow color for button off
	mButtonOff = game->GetRenderer()->GetTexture("Assets/ButtonYellow.png");

	//Add this ui to game
	mGame->AddUI(this);
}

UIBase::~UIBase()
{
	if (mTitleTex)
	{
		delete mTitleTex;
		mTitleTex = nullptr;
	}

	
	for (auto b : mButton)
	{
		delete b;
	}
	mButton.clear();
}

void UIBase::ProcessInput(const Uint8 * key)
{
	int x, y;

	SDL_GetMouseState(&x, &y);

	//Converted to screen
	x -= mGame->GetRenderer()->WindowW() / 2.0f;
	y = mGame->GetRenderer()->WindowH() / 2.0f - y;

	Vector3 point = Vector3( (float)x, (float)y, 0.0f);

	for (auto b : mButton)
	{
		if (b->ContainsPoint(point))
		{
			b->SetHighlighted(true);
		}
		else
		{
			b->SetHighlighted(false);
		}
	}
}

void UIBase::Update(float delta)
{
}

void UIBase::DrawTexture(Shader * shader, const Vector3 & pos, Texture * texture, float scale )
{
	//Use a 2D Renderer
	Matrix4 Temp = Matrix4::Scale(scale * texture->TexWidth(), scale * texture->TexHeight());

	Temp *= Matrix4::Translate(pos);

	shader->SetMatrixUniform("mTransformation", Temp);

	texture->Active();

	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIBase::HandleKey(int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
		for (auto b : mButton)
		{
			if (b->Highlighted())
			{
				//Call Onclick
				b->Onclick();
			}
		}
		break;

	default:
		break;
	}
}

void UIBase::Draw(Shader * shader)
{
	//This background is for the game over
	if (mBackgroundTexture)
	{
		DrawTexture(shader, Vector3(0.f, 0.f, 0.f), mBackgroundTexture);
	}

	if (mTitleTex)
	{
		
		DrawTexture(shader, mPosition, mTitleTex);
	}

	for (auto b : mButton)
	{
		Texture * tex = (b->Highlighted() ? mButtonOn : mButtonOff);

		DrawTexture(shader, b->Position(), tex);

		//Draw the button name
		DrawTexture(shader, b->Position(), b->Name());
	}


}

void UIBase::SetTitle(const std::string & text, const Vector3& color, int size)
{
	mTitleTex = mFont->RenderTextBlended(text, color, size);
}

void UIBase::AddButton(std::function<void()> onclick, const std::string & text)
{
	Vector3 dims = Vector3(static_cast<float>(mButtonOn->TexWidth()), static_cast<float>(mButtonOn->TexHeight()), 0.0f);

	Button * b = new Button(onclick, mFont, text, mNextButtonPos, dims);

	mButton.push_back(b);
	
	//Update the next button position
	mNextButtonPos.y -= static_cast<float>(mButtonOn->TexHeight() + 20.0f);
}

void UIBase::Closing()
{
	mState = EClosing;
}


//Button
Button::Button(std::function<void()> onclick, class Font *font, const std::string & text, const Vector3 & position, const Vector3 & dims)
	:mOnclick(onclick),
	mFont(font),
	mPosition(position),
	mDims(dims),
	mHighlighted(false)
{
	SetButtonName(text);
}

Button::~Button()
{
	if (mTexture)
	{
		delete mTexture;
		mTexture = nullptr;
	}
}

void Button::SetButtonName(const std::string & text)
{
	mTexture = mFont->RenderTextBlended(text);
}

bool Button::ContainsPoint(const Vector3 & point)
{
	bool res =
		(point.x < mPosition.x - mDims.x / 2.0f) ||
		(point.x > mPosition.x + mDims.x / 2.0f) ||
		(point.y < mPosition.y - mDims.y / 2.0f) ||
		(point.y > mPosition.y + mDims.y / 2.0f);

	return !res;
}

//On click
void Button::Onclick()
{
	mOnclick();
}
