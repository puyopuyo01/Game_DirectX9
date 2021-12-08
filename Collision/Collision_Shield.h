#pragma once
#include"Player/CollisionObject.h"

class CollisionShield :public CollisionState {
public:
	void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) override;
};