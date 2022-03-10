#include"./ObjectManager.h"
#include"Bullet/Bullet.h"

ObjectMNG* ObjectMNG::SingleTon;

ObjectMNG* ObjectMNG::GetMNG() {
	if (SingleTon == nullptr) {
		SingleTon = new ObjectMNG();
	}
	return SingleTon;
}

ObjectMNG::ObjectMNG() {
	drawObj = new DrawObjectMNG();
}


void ObjectMNG::AddObject(BattleObject* obj) {
	object.push_back(unique_ptr<BattleObject>(obj));
	/*各IDごとで保持する。*/
	if (obj->GetID() == PLAYER) { playerObject.push_back(obj); }
	if (obj->GetID() == ENEMY){ enemyObject.push_back(obj); }
	AllObject.push_back(obj);
	return;
}

void ObjectMNG::AddBullet(Bullet* bullet) {
	if (bullet->GetID() == PLAYER) { playersBullet.push_back(bullet); }
	if (bullet->GetID() == ENEMY) { enemysBullet.push_back(bullet); }
	AllBullet.push_back(bullet);
}

void ObjectMNG::Delete(BattleObject* obj) {
	/*死亡アニメーションはここで呼び出す。*/
	obj->Death();

	/*各リストから引数のオブジェクトを削除する*/
	list<Bullet*> i;
	list<Bullet*>::iterator itr;
	list<Bullet*>::iterator end;
	if (obj->GetID() == PLAYER) { 
		playerObject.remove(obj);
		itr = playersBullet.begin(); 
		end = playersBullet.end();
		i = playersBullet;
	}
	if (obj->GetID() == ENEMY) { 
		enemyObject.remove(obj);
		itr = enemysBullet.begin(); 
		end = enemysBullet.end();
		i = enemysBullet;
	}
	while(itr != end){ 
		if ((*itr)->TemporaryFlag) { itr=i.erase(itr); continue; }
		itr++;
	}
	itr = AllBullet.begin();
	while (itr != AllBullet.end()) {
		if ((*itr)->TemporaryFlag) { itr = AllBullet.erase(itr); continue; }
		itr++;
	}


	list<BattleObject*>::iterator allObj = AllObject.begin();
	while (allObj != AllObject.end()) { 
		if ((*allObj) == obj) { 
			allObj = AllObject.erase(allObj); continue;
		} 
		allObj++;
	}
	printf("AllObject %d\n",(int)AllObject.size());

	object.remove_if([&obj](const unique_ptr<BattleObject>& object) { return object.get() == obj; });
}


list<Bullet*> ObjectMNG::GetBullet(int ID) {
	if (ID == PLAYER) { return playersBullet; }
	if (ID == ENEMY) { return enemysBullet; }
	return playersBullet;
}

list<BattleObject*> ObjectMNG::Get_Object(int ID){
	if (ID == PLAYER) { return playerObject; }
	if (ID == ENEMY) { return enemyObject; }
	return playerObject;
}

void ObjectMNG::SueSide() {
	object.clear();
	delete drawObj;
	drawObj = nullptr;
	delete SingleTon;
	SingleTon = nullptr;
}