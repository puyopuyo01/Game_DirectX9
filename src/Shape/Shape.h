#pragma once
#include"DXLib_Orig.h"
#include"Imageboard/ImageBoard.h"


#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/BattleDefines.h"

class Panel_Field;
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
	static void Set(Panel_Field* offset);
	bool EXIST;
public:
	Panel_Blue();
	void notif(Panel_Field* location,int x,int y);
	void Update() override;

	void Draw() override;

	Panel_Field* Location;/*�Q�[�����J�[�\�����p�l���̏�ɂ���Ƃ��A���̃p�l����ێ�����*/
private :
	int LocationX, LocationY;
	float size;
private:
	static unique_ptr<Panel_Blue> SingleTon;

};


#include"Battle/ObjectMNG/ObjectManager.h"


/*�����t�B�[���h�̃p�l���BPlayer���̃t�B�[���h�AEnmey���̃t�B�[���h�ǂ����3�~3�}�X*/
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
	void CollisionAll();


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