#include"./Collision_Shield.h"


void CollisionShield::CollisionEnemy(CollisionObject* HitObj, CollisionObject* me){
	HitObj->Ability(me);
	if (HitObj->GetPow() >= me->GetPow()) {/*���x�̒l�Ɋ֌W�Ȃ��Փˏ������s���B*/
		me->TemporaryFlag = true;
	}
}