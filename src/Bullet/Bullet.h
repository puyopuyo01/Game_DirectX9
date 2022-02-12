#pragma once
#include"DXLib_Orig.h"
#include"Imageboard/ImageBoard.h"
#include"Value_State.h"
#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"BulletState/BulletState.h"
#include"./Characteristic/Characteristic.h"
#include"Effect/Effect.h"

#define SMALLBULLET 0
#define MIDDLEBULLET 1
#define BIGBULLET 2

class BulletState;
class BulletCharacteristic;
class StatusBox;


class Bullet:public BattleObject{
public:
	Bullet(int GroupID,int BulletID,int power, float speedx,BulletCharacteristic* BState,float posx,float posy,float size);
	Bullet(int GroupID, int BulletID, float posx, float posy, float size); //ï`âÊî¬çÏê¨óp 
	~Bullet();


	static void Init();

	static int GetTexture();

	void Update() override;
	void Draw() override;

	void ApplyStatus() override;
	void AddPower(int pow) override;
	void AddSpeed(float speed) override;

	int GetPredominate() override;

	bool Siege(float* Dmg) override;
	void Death() override;

	ValueState<int>* power;
	ValueState<float>* speed;

	int GetBulletID();
	int GetID() override;
	int GetObjectID() override;
	int GetPow() override;
	float GetSpeed() override;

protected:
	static int Body; 
	static int Eye;
	int BulletID;
	int GroupID;

private:
	float speedx;
	BulletState* state;
	unique_ptr<ImageBoard> board;
	unique_ptr<ImageBoard> eye;

	BulletCharacteristic* charac;

	StatusBox* status;

	int vec;
	
};
