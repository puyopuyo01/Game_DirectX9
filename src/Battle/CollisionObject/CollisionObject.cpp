#include"./CollisionObject.h"

class CollisionState;

int CollisionObject::GetID() {
	return 0;
}

int CollisionObject::GetObjectID() { return 0; }

CollisionObject::CollisionObject(CollisionState* state) {
	CollisionBridge=unique_ptr<CollisionState>(std::move(state));
	//this->status = status;
}

CollisionObject::~CollisionObject() {
}


void CollisionObject::BaseCollision(CollisionObject* HitObj) {
	CollisionBridge->Judge(HitObj, this);
	if(TemporaryFlag){}
}

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
void CollisionState::Judge(CollisionObject* HitObj, CollisionObject* me) {
	if (HitObj->GetID() == me->GetID()) {
		CollisionAlly(HitObj, me);
	}
	if (HitObj->GetID() != me->GetID()) {
		CollisionEnemy(HitObj, me);
	}
}

void CollisionState::CollisionAlly(CollisionObject* HitObj, CollisionObject* me) {}

void CollisionState::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) {
	HitObj->Ability(me);
	if (HitObj->GetPow() >= me->GetPow() || HitObj->GetSpeed() >= 0.4f) {
		me->TemporaryFlag = true;
	}
}



PlayerCollisionState::PlayerCollisionState(float *HP) {
	this->HP = HP;
}

void PlayerCollisionState::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) {
	(*HP) += 30.f;
}
