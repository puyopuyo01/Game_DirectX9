#pragma once
#include"Battle/CollisionObject/CollisionState/CollisionState.h"
#include"Battle/CollisionObject/CollisionObject.h"


/*�u�V�[���h�v�����̎���*/
class CollisionShield :public CollisionState {
public:
	void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) override;
};