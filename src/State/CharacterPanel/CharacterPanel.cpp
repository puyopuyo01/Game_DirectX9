#include"./CharacterPanel.h"

float Height = ScreenHeigth();
float Width = Height * 0.7f;

void SetPosition(float *x, float *y) {
	*x = ScreenLX()-(Width/2.f);
	*y = ScreenCenterY();
}

CharacterPanel::CharacterPanel(float x, float y,int TextureNumber):Field_Object(0.f,0.f,-1.f){
	this->TextureNumber = TextureNumber;
	this->Height = ScreenHeigth()-7.f;
	this->Width = this->Height*0.7f;
	img = make_unique<Primitive>(Primitive(SQUARE, 0.f, 0.f, -1.f,this->Width,this->Height, 1.f, 1.f, 1.f, 1.f));

	Move(x,y);

}


CharacterPanel::~CharacterPanel() {
}


void CharacterPanel::Draw(){
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
	Images::GetInstance()->LoadImage(this->TextureNumber, 0);
	img->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();
}


void CharacterPanel::UpdateMove(float speed,int vec) {
	float  MoveToX = (speed + this->GetLocation().x);
	Move(MoveToX, this->GetLocation().y);
}