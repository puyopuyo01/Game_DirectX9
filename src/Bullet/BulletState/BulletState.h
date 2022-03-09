#pragma once
#include"Bullet.h"
#include"Battle/BattleDefines.h"

class BattleObject;
class Bullet;


/*
幽霊の状態(動けなくする状態等を実装予定)
*/
class BulletState {
public:
	virtual bool Draw(Bullet* bullet) { return false; };
	virtual void Update(Bullet* bullet,int vec) {};
};

/*通常時の幽霊。更新処理では移動処理のみを行う。*/
class BulletNormal :public BulletState {
public:
	bool Draw(Bullet* bullet) override;
	void Update(Bullet* bullet,int vec) override;
};