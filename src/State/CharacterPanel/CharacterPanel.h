#pragma once
#include"DX_Lib/Imageboard/ImageBoard.h"
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Screen.h"

void SetPosition(float *x, float *y);

class CharacterPanel:public Field_Object {
	/*カットイン用のパネル。
	右は必要な情報を表示しているので左から入り左から出る。*/
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