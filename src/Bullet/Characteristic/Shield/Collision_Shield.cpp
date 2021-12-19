#include"./Collision_Shield.h"


void CollisionShield::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me){
	HitObj->Ability(me);
	if (HitObj->GetPow() >= me->GetPow()) {
		me->TemporaryFlag = true;
	}
}