#include"./TextBox.h"


TextState* TextState::Update() { return nullptr; }
void TextState::Set(int frame, TextState* next,int* hei) { 
	Frame = frame; FrameMax = frame; this->next = next; finish = false; 
	Height = hei;
}
bool TextState::Finish() { return finish; }



TextState* TextInterput::Update() {
	Frame--;
	(*Height) += (int)(1000 / FrameMax);
	if (Frame == 0) { return next; }
	return this;
}

TextState* TextStay::Update() {
	Frame--; 
	if (Frame == 0) { return next; } 
	return this;
}
TextState* TextO::Update(){
	(*Height) -= (int)(1000 / FrameMax);
	if ((*Height) <= 0) {
		(*Height) = 0;
	}
	Frame--;
	if (Frame == 0) { finish = true; return next; }
	return this;
}



TextBox::TextBox(int x, int y, string name, string intro,int In,int Stay,int Out):Field_Object(0.f,0.f,0.f){
	this->x = x;
	this->y = y;
	SchemeName = name;
	this->intro = intro;
	this->In = make_unique<TextInterput>();
	this->Stay = make_unique<TextStay>();
	this->Out = make_unique<TextO>();
	this->In->Set(In, this->Stay.get(), &Height);
	this->Stay->Set(Stay, this->Out.get(), &Height);
	this->Out->Set(Out, this->Out.get(), &Height);
	this->NowState = this->In.get();

	Height = 0;

	font = Font::GetInstance();
}

TextBox::~TextBox() {

}


void TextBox::Update() {
	this->NowState = this->NowState->Update();
}

void TextBox::Draw() {
	string tex = SchemeName + ":" + intro;
	font->Draw(x, y, 1000, (int)Height, tex.c_str());
}