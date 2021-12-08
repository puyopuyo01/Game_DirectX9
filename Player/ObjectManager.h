#pragma once
#include"BattleObject.h"

class Player;
class BattleObject;
class Bullet;

/*�����̃I�u�W�F�N�g���Ǘ�����*/
class ObjectMNG {
public:
	static ObjectMNG* GetMNG();
	void SueSide();
	void AddObject(BattleObject* obj);
	void Delete(BattleObject* obj);


	void AddBullet(Bullet* bullet);


	list<BattleObject*> Get_Object(int ID);
	list<Bullet*> GetBullet(int ID);

	Player* player;
	Player* enemy;



private:
	list<unique_ptr<BattleObject>> object;
	list<BattleObject*> playerObject;
	list<BattleObject*> enemyObject;

	/*�e�́ABullet�^�ł��ێ����Ă���*/
	list<Bullet*> playersBullet;
	list<Bullet*> enemysBullet;
	static ObjectMNG* SingleTon;
};