#pragma once
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/DrawObject/DrawObject.h"

class Player;
class BattleObject;
class Bullet;

/*試合のオブジェクトを管理する*/
class ObjectMNG {
public:
	ObjectMNG();

	static ObjectMNG* GetMNG(); /*SingleTon*/
	void SueSide(); /*リスト内のオブジェクトを解放*/
	void AddObject(BattleObject* obj);
	void Delete(BattleObject* obj);

	void AddBullet(Bullet* bullet);


	list<BattleObject*> Get_Object(int ID);
	list<Bullet*> GetBullet(int ID);

	Player* player; /*自機、敵機クラスはこのクラスの変数で保持。*/
	Player* enemy;
	list<BattleObject*> AllObject; /*フィールドに存在する全てのオブジェクト。衝突判定を行うときはこのリストを使う。*/

	DrawObjectMNG* drawObj;



private:
	list<unique_ptr<BattleObject>> object;
	/*Player側ID、Enemey側IDごとにリストで保持しておく。*/
	list<BattleObject*> playerObject;
	list<BattleObject*> enemyObject;
	

	/*弾は、Bullet型でも保持しておく*/
	list<Bullet*> playersBullet;
	list<Bullet*> enemysBullet;
	list<Bullet*> AllBullet;
	static ObjectMNG* SingleTon;
};