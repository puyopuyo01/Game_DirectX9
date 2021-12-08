#pragma once
#include"Battle/CollisionObject/CollisionState/CollisionState.h"
#include"Battle/CollisionObject/CollisionObject.h"


/*「シールド」特性の実装*/
class CollisionShield :public CollisionState {
public:
	void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) override;
};