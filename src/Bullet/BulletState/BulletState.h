#pragma once
#include"Bullet.h"
#include"Battle/BattleDefines.h"

class BattleObject;
class Bullet;


/*
�H��̏��(�����Ȃ������ԓ��������\��)
*/
class BulletState {
public:
	virtual bool Draw(Bullet* bullet) { return false; };
	virtual void Update(Bullet* bullet,int vec) {};
};

class BulletNormal :public BulletState {
public:
	bool Draw(Bullet* bullet) override;
	void Update(Bullet* bullet,int vec) override;
};