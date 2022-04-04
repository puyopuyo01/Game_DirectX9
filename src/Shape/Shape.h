#pragma once
#include"DXLib_Orig.h"
#include"Imageboard/ImageBoard.h"


#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/BattleDefines.h"

class Field_Move_Mass;
class BattleObject;
class ObjectMNG;


/*�����t�B�[���h�ł���,�p�l���N���X*/

class Shape:public Field_Object{
public:
	Shape(float x,float y,float z);

	int x, y;/*���݈ʒu���瑊�ΓI�Ɉړ��}�X�����߂�*/
protected:
	unique_ptr<ImageBoard> img;
};


/*�Q�[�����J�[�\�����ǂ̃p�l���̏�ɂ��邩�\�������邽�߂̃p�l��*/
class Panel_Blue :public Shape{
public:
	static Panel_Blue* GetInstance();
	static void Set(Field_Move_Mass* offset);
	bool EXIST;
public:
	Panel_Blue();
	void notif(Field_Move_Mass* location,int x,int y);
	void Update() override;

	void Draw() override;

	Field_Move_Mass* Location;/*�Q�[�����J�[�\�����p�l���̏�ɂ���Ƃ��A���̃p�l����ێ�����*/
private :
	int LocationX, LocationY;
	float size;
private:
	static unique_ptr<Panel_Blue> SingleTon;

};


#include"Battle/ObjectMNG/ObjectManager.h"


/*�����t�B�[���h�̃p�l���BPlayer���̃t�B�[���h�AEnmey���̃t�B�[���h�ǂ����3�~3�}�X*/
class Field_Move_Mass :public Shape{
public:
	Field_Move_Mass(int x, int y, Panel_Blue* panel,float lx, float ly, float lz, float r, float g,float b,float a, float size,int ID);
	~Field_Move_Mass();

	float GetSize();

	int ID;

	void Update() override;
	void MoveUpdate();
	void CollisionUpdate();
	void DeathUpdate();
	void CollisionAll();


	void Draw() override;
	void AddObject(BattleObject* object,float x,float y);
	void AddObject(BattleObject* object);
	void MoveObject();
	static Field_Move_Mass* AllPanel[width*2][length];
	Field_Move_Mass* Notif(Field_Object* obj);

	void ApplyStatus();


	bool ExistPanel(int x,int y);
	Field_Move_Mass* GetPanel(int x, int y);
	list<BattleObject*> GetBattleObject(int ID, bool Except);
	list<BattleObject*> GetBattleObject();

	list<BattleObject*> obj;

	static int GetPredmGauge();
	static int* GetPredAddr();
	static void ResetPredmGauge();
	void AddPredmGauge(int add);

protected:
	list<BattleObject*> MoveObjTemp; /*���̃I�u�W�F�N�g�Ǘ����X�g�B�ʃp�l�����炫���I�u�W�F�N�g�͂��̃t���[���ł͊Ǘ��������t���[������Ǘ�����B*/
	Panel_Blue* panel;
private:
	float size;
	bool ent_cursor;
	static int PredmGauge;

};


/*���̃p�l���ɃI�u�W�F�N�g������ƃ_���[�W��^����*/
class DefenseMass :public Field_Move_Mass{
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