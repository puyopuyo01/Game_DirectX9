#include"DXLib_Orig.h"


/*DirectX��p���ĕ`���X�V������ꍇ�A
���̃N���X���p������DirectX�̊֐������������ɋɗ͏o���Ȃ��悤�ɂ���*/

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