#pragma once
#include"Bullet/BulletState/BulletState.h"
#include"Battle/CollisionObject/CollisionObject.h"
#include"Bullet/Bullet.h"

class BulletState;
class CollisionState;

class BulletCharacteristic{
	/*衝突したときの処理クラスや更新処理クラスの保持、また描画を特性クラスで行う。*/
public:
	BulletCharacteristic();
	~BulletCharacteristic();

	virtual void Draw(Bullet* bullet);

	BulletCharacteristic* GetPrev();
	BulletCharacteristic* GetState();

	virtual BulletCharacteristic* ChangeCharacteristic(BulletCharacteristic* chara);

	CollisionState* collisionState;
	BulletState* bulletState;


protected:
	BulletCharacteristic* PrevState;
	BulletCharacteristic* State;
};


class NonCharacteristic :public BulletCharacteristic {
public:
	NonCharacteristic();
};


class Shield :public BulletCharacteristic {
	/*速度に影響されない特性を持つ。*/
public:
	Shield(int ID,float x,float y,float size);
	void Draw(Bullet* bullet) override;
private:
	std::unique_ptr<ImageBoard> board;
	static int ImageID;


};