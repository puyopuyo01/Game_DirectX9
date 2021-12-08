#pragma once
#include"DXLib_Orig.h"
#include"Imageboard/ImageBoard.h"


#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/BattleDefines.h"

class Panel_Field;
class BattleObject;
class ObjectMNG;


/*試合フィールドである,パネルクラス*/

class Shape:public Field_Object{
public:
	Shape(float x,float y,float z);

	int x, y;/*現在位置から相対的に移動マスを求める*/
protected:
	unique_ptr<ImageBoard> img;
};



class Panel_Blue :public Shape{
public:
	static Panel_Blue* GetInstance();
	static void Set(Panel_Field* offset);
	bool EXIST;
public:
	Panel_Blue();
	void notif(Panel_Field* location,int x,int y);
	void Update() override;

	void Draw() override;

	Panel_Field* Location;
private :
	int LocationX, LocationY;
	float size;
private:
	static unique_ptr<Panel_Blue> SingleTon;

};


#include"Battle/ObjectMNG/ObjectManager.h"


/*オブジェクトが存在するパネル*/
class Panel_Field :public Shape{
public:
	Panel_Field(int x, int y, Panel_Blue* panel,float lx, float ly, float lz, float r, float g,float b,float a, float size,int ID);
	~Panel_Field();

	float GetSize();

	int ID;

	void Update() override;
	void MoveUpdate();
	void CollisionUpdate();
	void DeathUpdate();


	void Draw() override;
	void AddObject(BattleObject* object,float x,float y);
	void AddObject(BattleObject* object);
	void MoveObject();
	static Panel_Field* AllPanel[width*2][length];
	Panel_Field* Notif(Field_Object* obj);

	void ApplyStatus();


	bool ExistPanel(int x,int y);
	Panel_Field* GetPanel(int x, int y);
	list<BattleObject*> GetBattleObject(int ID, bool Except);
	list<BattleObject*> GetBattleObject();

	list<BattleObject*> obj;

	static int GetPredmGauge();
	static void ResetPredmGauge();
	void AddPredmGauge(int add);

protected:
	list<BattleObject*> MoveObjTemp;
	Panel_Blue* panel;
private:
	float size;
	bool ent_cursor;
	static int PredmGauge;

};


/*このパネルにオブジェクトが入るとダメージを与える*/
class DefenseMass :public Panel_Field{
public:
	DefenseMass(int ID,float* Dmg,int x, int y, Panel_Blue* panel, float lx, float ly, float lz, float r, float g, float b, float a, float size);
	void Update() override;
	void Draw() override;
	void AddObject(BattleObject* object);
private:
	float* Dmg;
	int ID;
};






#define SHAPE_VERTEX_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)