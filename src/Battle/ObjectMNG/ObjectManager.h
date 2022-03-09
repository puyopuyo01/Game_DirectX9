#pragma once
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/DrawObject/DrawObject.h"

class Player;
class BattleObject;
class Bullet;

/*�����̃I�u�W�F�N�g���Ǘ�����*/
class ObjectMNG {
public:
	ObjectMNG();

	static ObjectMNG* GetMNG(); /*SingleTon*/
	void SueSide(); /*���X�g���̃I�u�W�F�N�g�����*/
	void AddObject(BattleObject* obj);
	void Delete(BattleObject* obj);

	void AddBullet(Bullet* bullet);


	list<BattleObject*> Get_Object(int ID);
	list<Bullet*> GetBullet(int ID);

	Player* player; /*���@�A�G�@�N���X�͂��̃N���X�̕ϐ��ŕێ��B*/
	Player* enemy;
	list<BattleObject*> AllObject; /*�t�B�[���h�ɑ��݂���S�ẴI�u�W�F�N�g�B�Փ˔�����s���Ƃ��͂��̃��X�g���g���B*/

	DrawObjectMNG* drawObj;



private:
	list<unique_ptr<BattleObject>> object;
	/*Player��ID�AEnemey��ID���ƂɃ��X�g�ŕێ����Ă����B*/
	list<BattleObject*> playerObject;
	list<BattleObject*> enemyObject;
	

	/*�e�́ABullet�^�ł��ێ����Ă���*/
	list<Bullet*> playersBullet;
	list<Bullet*> enemysBullet;
	list<Bullet*> AllBullet;
	static ObjectMNG* SingleTon;
};