#include"DXLib_Orig.h"


/*DirectXを用いて描画や更新をする場合、
このクラスを継承してDirectXの関数を実装部分に極力出さないようにする*/

Field_Object::Field_Object(float x, float y,float depth) {
	pos.x = x;
	pos.y = y;
	pos.z = depth;
	D3DXMatrixIdentity(&loc);
	D3DXMatrixIdentity(&rot);
	D3DXMatrixIdentity(&output);
	D3DXMatrixMultiply(&output, &rot, &loc);

}


Field_Object::~Field_Object(){}
void Field_Object::Update() {}
void Field_Object::Draw(){}


D3DXMATRIX Field_Object::GetMatrix() {
	return output;
}
D3DXVECTOR3 Field_Object::GetLocation() {
	return pos;
}

void Field_Object::Move(float x, float y) {
	pos.x = x;
	pos.y = y;
	D3DXMatrixTranslation(&loc,pos.x,pos.y,0.f);
	D3DXMatrixMultiply(&output, &rot, &loc);

}

void Field_Object::Rot(float a) {
	D3DXMatrixRotationYawPitchRoll(&rot, 0.f, D3DXToRadian(180.0f)/*D3DXToRadian(180.0f)*/, 0.f /*D3DXToRadian(45.0f)*/);
	D3DXMatrixMultiply(&output, &rot, &loc);
}

void Field_Object::Inversion() {
	D3DXMatrixRotationYawPitchRoll(&rot, D3DXToRadian(180.0f), 0.f, 0.f);
	D3DXMatrixMultiply(&output, &rot, &loc);
}

void Field_Object::BackGroundTransparent() {
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
}