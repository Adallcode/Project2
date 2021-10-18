#pragma once


#include <string>
#include <vector>

#include "Math.h"
#include "SDL.h"

#include <functional>

class Button
{
public:
	Button(std::function<void()> onclick, class Font *font, const std::string& text, const  Vector3 & pos, const Vector3& dims);
	~Button();


	class Texture * const Name()const { return mTexture; }

	void SetButtonName(const std::string& text);
	bool ContainsPoint(const Vector3& point);
	Vector3 Position()const { return mPosition; }
	

	//Highlighted
	void SetHighlighted(bool h) { mHighlighted = h; }
	bool Highlighted()const { return mHighlighted; }

	//On click
	void Onclick();
	
protected:
	std::function<void()> mOnclick;
	
	class Font *mFont;

	class Texture * mTexture;

	Vector3 mPosition;
	Vector3 mDims;

	//Highlighted
	bool mHighlighted;
};


class UIBase
{
public:
	UIBase(class Game * game);
	virtual ~UIBase();

	enum State{EActive, EClosing};

	//Virtual
	virtual void ProcessInput(const Uint8* key);
	virtual void Update(float delta);
	virtual void DrawTexture(class Shader * shader, const Vector3& pos, class Texture * texture, float scale = 1.0f);
	virtual void HandleKey(int key);

	void Draw(class Shader * shader);

	void SetTitle(const std::string& text, const Vector3& color = Color::White, int size = 30);

	//Background
	void SetBackground(class Texture * t) { mBackgroundTexture = t; }

	//Button
	void AddButton(std::function<void()> onclick, const std::string& text);

	void Closing();

	//State
	void SetState(State state) { mState = state; }
	State GetState()const { return mState; }

	//Position
	void SetPosition(const Vector3& pos) { mPosition = pos; }

protected:
	//Font
	class Font * mFont;
	
	//Textures
	class Texture * mTitleTex;
	class Texture * mBackgroundTexture;
	class Texture * mButtonOn;
	class Texture * mButtonOff;


	//Button
	std::vector<Button *> mButton;

	//Game
	class Game * mGame;

	//Position
	Vector3 mPosition;

	//Nex button position
	Vector3 mNextButtonPos;

	State mState;
};

