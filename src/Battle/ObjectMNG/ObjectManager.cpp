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
	if (obj->GetID() == PLAYER) { playerObject.push_back(obj); }
	if (obj->GetID() == ENEMY){ enemyObject.push_back(obj); }
	object.push_back(unique_ptr<BattleObject>(obj)); 
	return;
}

void ObjectMNG::AddBullet(Bullet* bullet) {
	if (bullet->GetID() == PLAYER) { playersBullet.push_back(bullet); }
	if (bullet->GetID() == ENEMY) { enemysBullet.push_back(bullet); }
}

void ObjectMNG::Delete(BattleObject* obj) {
	obj->Death();
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
	object.remove_if([&obj](const unique_ptr<BattleObject>& object) { return object.get() == obj; });
}


list<Bullet*> ObjectMNG::GetBullet(int ID) {
	if (ID == PLAYER) { return playersBullet; }
	if (ID == ENEMY) { return enemysBullet; }
}

list<BattleObject*> ObjectMNG::Get_Object(int ID){
	if (ID == PLAYER) { return playerObject; }
	if (ID == ENEMY) { return enemyObject; }
}

void ObjectMNG::SueSide() {
	delete drawObj;
	delete SingleTon;
}