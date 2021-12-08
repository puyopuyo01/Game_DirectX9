#pragma once
#include"DX_Lib/Imageboard/ImageBoard.h"
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Screen.h"

void SetPosition(float *x, float *y);

class CharacterPanel:public Field_Object {
	/*�J�b�g�C���p�̃p�l���B
	�E�͕K�v�ȏ���\�����Ă���̂ō�������荶����o��B*/
public:
	CharacterPanel(float x,float y,int TextureNumber);
	~CharacterPanel();

	void Draw() override;
	void UpdateMove(float speed,int vec);

	float Width;
	float Height;
private:
	unique_ptr<ImageBoard> img;
	int TextureNumber;
};