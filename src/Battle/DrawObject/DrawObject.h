#pragma once
#include"DX_Lib/DXLib_Orig.h"

class DrawObject :public Field_Object {
public:
	DrawObject(float x,float y);

	bool GetDeath();
protected:
	bool Death;
};

class DrawObjectMNG :public Field_Object {
public:
	DrawObjectMNG();
	~DrawObjectMNG();
	void AddObject(DrawObject* obj);

	void Update() override;
	void Draw() override;
private:
	list<DrawObject*> drawobj;
};