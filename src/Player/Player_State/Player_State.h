#pragma once
#include"DXLib_Orig.h"
#include"Value_State.h"
#include"Player.h"
#include"Shape.h"
#include"State/Battle_State.h"
#include"State/Key/KeyBox.h"
#include"DX_Lib/Sound/Sound.h"

#define MATCHKEYPRESS 0


class CollisionObject;
class Field_Object;
class BattleObject;
class HandleMove;

class BulletState;

class Handle {
public:
	virtual bool Excution() { return false; };	//��������̓�����s���Ă��邩��t/f�ŕԂ��B
};

/*

----------------------------------------�ړ��n�̃n���h��----------------------------------------


*/

class HandleMove :public Handle {
public:
	virtual HandleMove* Update(Player* player) { return NULL; };
	virtual bool IsMovable() { return true; };
private:
	Player* player;
};

class IdleMove:public HandleMove{
public:
	HandleMove* Update(Player* player) override;
	IdleMove() {};
};


/*
--------------------------------------�K�E�Z�n���h��------------------------------------------
*/

class Player;

class HandleScheme:public Handle{
public:
	virtual HandleScheme* Update(Player* player);
};

class IdleScheme:public HandleScheme{
public:
	HandleScheme* Update(Player* player) override;
};

class SchemeWaitingForInput :public HandleScheme {
public:
	HandleScheme* Update(Player* player) override;
};



/*

----------------------------------------�e�n�̃n���h��----------------------------------------


*/
#include"Bullet.h"
class Bullet;

class HandleBullet:public Handle {
public:
	virtual HandleBullet* Update(Player* player) { return nullptr; };
protected:
	int SmallB;
	int MiddleB;
	int BigB;
	bool Small;
	bool Middle;
	bool Big;
};


class IdleBullet :public HandleBullet {
public:
	IdleBullet();
	~IdleBullet();
	HandleBullet* Update(Player* player) override;
private:
	unique_ptr<Sound> BulletSE;
};

