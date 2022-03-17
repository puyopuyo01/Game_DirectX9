#pragma once
#include"Bullet/BulletState/BulletState.h"
#include"Battle/CollisionObject/CollisionObject.h"
#include"Bullet/Bullet.h"

class BulletState;
class CollisionState;

class BulletCharacteristic{
	/*�Փ˂����Ƃ��̏����N���X��X�V�����N���X�̕ێ��A�܂��`�������N���X�ōs���B*/
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

/*���������������Ȃ����Ƃ������N���X�B*/
class NonCharacteristic :public BulletCharacteristic {
public:
	NonCharacteristic();
};

/*�V�[���h�������Ă���Ƃ������Ƃ������B���l�ȏ�̑��x�����H��ƏՓ˂��Ă����S���Ȃ��Ƃ������������B*/
class Shield :public BulletCharacteristic {
	
public:
	static void LoadIMG();
	Shield(int ID,float x,float y,float size);
	void Draw(Bullet* bullet) override;
private:
	std::unique_ptr<ImageBoard> board;
	static int ImageID;


};