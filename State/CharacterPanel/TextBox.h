#pragma once
#include"DX_Lib/DXLib_Orig.h"

class TextState {
public:
	virtual TextState* Update();
	void Set(int Frame,TextState* next,int *hei);
	bool Finish();
protected:
	TextState* next;
	int Frame;
	int FrameMax;
	int *Height;
	bool finish;
};
class TextInterput:public TextState{
public:
	TextState* Update() override;
};
class TextStay:public TextState{
public:
	TextState* Update() override;
};
class TextO :public TextState {
public:
	TextState* Update() override;
};



class TextBox :public Field_Object {
	/*テキスト*/
public:
	TextBox(int x, int y,string name,string intro,int In,int Stay,int Out);
	~TextBox();
	void Draw() override;
	void Update() override;
private:
	Font* font;
	string SchemeName;
	string intro;

	TextState* In;
	TextState* Stay;
	TextState* Out;

	TextState* NowState;

	int Height;
	int x, y;
};
