#include"./CollisionObject.h"

class CollisionState;

int CollisionObject::GetID() {
	return 0;
}

int CollisionObject::GetPow() { return 100; } /*「強さ」のステータス。自機、敵機は100。*/
float CollisionObject::GetSpeed() { return 0.f; }

int CollisionObject::GetObjectID() { return 0; }

CollisionObject::CollisionObject(CollisionState* state) {
	CollisionBridge=unique_ptr<CollisionState>(std::move(state));
}

CollisionObject::~CollisionObject() {
}

void CollisionObject::BaseCollision(CollisionObject* HitObj) {
	CollisionBridge->Judge(HitObj, this);
}


/*Visitorパターンでお互いの衝突処理を1度のみにする。*/
void CollisionObject::Visit(CollisionObject* HitObj) {
	BaseCollision(HitObj);
}

void CollisionObject::Accept(CollisionObject* HitObj) {
	HitObj->Visit(this);
	BaseCollision(HitObj);
}



void CollisionObject::Ability(CollisionObject* HitObj) {
}

void CollisionObject::ChangeState(CollisionState* newState){
	CollisionBridge.reset(newState);
}


void CollisionObject::AddPower(int pow) {}
void CollisionObject::AddSpeed(float speed){}



/*
---------------------------------------ステート処理—------------------------------------------
*/

/*オブジェクトのIDから敵のオブジェクトか味方のオブジェクトか判別する。*/
void CollisionState::Judge(CollisionObject* HitObj, CollisionObject* me) {
	if (HitObj->GetID() == me->GetID()) {
		CollisionAlly(HitObj, me);
	}
	if (HitObj->GetID() != me->GetID()) {
		CollisionEnemy(HitObj, me);
	}
}

/*味方のオブジェクトと衝突したときの処理。*/
void CollisionState::CollisionAlly(CollisionObject* HitObj, CollisionObject* me) {}

/*敵と衝突したときの衝突処理。「強さ」が自身より大きいか、敵のスピードが一定値以上あれば死ぬ。*/
void CollisionState::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) {
	HitObj->Ability(me);
	if (HitObj->GetPow() >= me->GetPow() || HitObj->GetSpeed() >= 30.f) {
		me->TemporaryFlag = true;
	}
}


/*自機や敵機に当たった時の処理。固定値でダメージを与える。衝突したオブジェクトは、自機や敵機は強さのステータスが100あるため必ず負ける。*/
PlayerCollisionState::PlayerCollisionState(float *HP) {
	this->HP = HP;
}

void PlayerCollisionState::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) {
	/*同時に幽霊と衝突するとバグ？*/
	(*HP) += 30.f;
	HitObj->TemporaryFlag = true;
	printf("CollisionPlayer %lf\n",(*HP));
}
