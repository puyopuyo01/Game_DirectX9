#pragma once

class CollisionObject;

/*

-------------------ステート処理-------------------------------
Bridgeパターンで実装
当たったときの処理を状態によって変化させる。


*/

class CollisionState {
public:
	virtual void Judge(CollisionObject* HitObj, CollisionObject* me);/*IDによる判別*/
protected:
	virtual void CollisionAlly(CollisionObject* HitObj, CollisionObject* me);
	virtual void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me);
};

class NormalCollisionState :public CollisionState {
};

/*プレイヤーと弾が衝突した場合、プレイヤーのHPを減らす*/
class PlayerCollisionState : public CollisionState {
public:
	PlayerCollisionState(float *HP);
	void CollisionEnemy(CollisionObject* HitObj, CollisionObject* me) override;

private:
	float *HP;
};