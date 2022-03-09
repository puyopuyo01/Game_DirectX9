#pragma once
#include<list>
#include<iostream>
#include"DXLib_Orig.h"
#include"State/NetWork/FramePacket/Frame.h"

#define SENDPREVKEY 10

class FramePacket; //newできない


/*試合のキー入力を管理するクラス*/
class KeyBox {
public:
	static KeyBox* GetInstance();

	KeyBox();
	void Close();

	void GetPlayerKey(int LatestID);
	void SetPlayerPosition(const int FrameID,int x, int y);

	void CreateSendKey(const int FrameID);
	void CreateFramePacket(const int FrameID);
	void ReceiveKey(const char* key,const int CreateID);


	bool FinishPacket(const int FrameID);


	bool ReachEnemyPacket(const int ProcessID);

	void IntReset();


	void UpdateFrame(const int FrameID);
	FramePacket* updateframe;


private:
	static std::unique_ptr<KeyBox> SingleTon;
	std::list<unique_ptr<FramePacket>> PacketQueue;
	std::list<FramePacket*> WaitingPacket;/*まだ通信相手のキー入力が届いてないFramePacketクラスのリスト*/

	int LatestRecvID;	/*最新のフレームIDを保持*/

	FramePacket* SearchFrame(const int FrameID);
	char PrevSending[1023]; 
};