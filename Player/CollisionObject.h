#pragma once
#include"DXLib_Orig.h"
#include"Value_State.h"
#include"CollisionState.h"
#include"Battle/ChangeStatusStruct.h"

class CollisionState;

class CollisionObject {
public:
	CollisionObject(CollisionState* state);
	~CollisionObject() ;
	/*固有の能力。値を変更する場合は、フラグなどを建てるようにして、最後の更新処理でまとめて行う。*/
	virtual void Ability(CollisionObject* HitObj);	 //virtualの必要ないかも。
	virtual void ChangeState(CollisionState* newState);
	virtual void AddPower(int pow);
	virtual void AddSpeed(float speed);

	/*
	Acceptは、バトルステートから呼び出される関数。当たったオブジェクトに通知する。
	Visitは当てられたオブジェクト。自身の処理のみ行う。
	 */
	void Accept(CollisionObject* HitObj);
	void Visit(CollisionObject* HitObj);



	/*
	オブジェクトからの値はオーバーライドで取り出す。
	*/
	virtual int GetID();// { return 0; }
	virtual int GetObjectID();
	virtual int GetPow() { return 100; }
	virtual float GetSpeed() { return 0.f; }
	/*
	仮の死亡フラグ。これをしないと処理によっては、通信相手との矛盾を生む。
	*/
	bool TemporaryFlag;
private:
	unique_ptr<CollisionState> CollisionBridge;
	void BaseCollision(CollisionObject* HitObj);

};



