#pragma once
#include"BattleObject.h"

class Player;
class BattleObject;
class Bullet;

/*試合のオブジェクトを管理する*/
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

	/*弾は、Bullet型でも保持しておく*/
	list<Bullet*> playersBullet;
	list<Bullet*> enemysBullet;
	static ObjectMNG* SingleTon;
};