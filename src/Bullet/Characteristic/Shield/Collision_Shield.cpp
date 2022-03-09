#include"./Collision_Shield.h"


void CollisionShield::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me){
	HitObj->Ability(me);
	if (HitObj->GetPow() >= me->GetPow()) {/*速度の値に関係ない衝突処理を行う。*/
		me->TemporaryFlag = true;
	}
}