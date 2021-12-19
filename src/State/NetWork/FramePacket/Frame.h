#pragma once
#include"../NetWork.h"
#include"Battle/BattleDefines.h"
#include<list>
#define Wait 4
#define NumOfKeys 10
#define KeyOnly 8

/*		Player(Enemy)Key‚Ì“Y‚¦š	 */
#define QB 0
#define WB 1
#define EB 2
#define RB 3
#define FB 4
#define GB 5
#define LEFTSHIFT 6
#define SPACE 7
#define POSITION 8


using namespace std;

class FramePacket;

void InsertFrame(list<unique_ptr<FramePacket>> frame,FramePacket* packet);


/*FrameID”Ô–Ú‚É‘Šè‚Æ©•ª‚ª‚Ç‚Ì“ü—Í‚ğ‚µ‚½‚©•Û‚·‚éƒNƒ‰ƒX*/
class FramePacket{
public:
	FramePacket(int FrameID,char key[]); /*‚¢‚ç‚È‚¢‚©‚à*/
	FramePacket(int FrameID);
	char *GetKey(int PlayerID,int index);
	 
	void InsertPlayerKeyForIndex(const int index,const char* key);
	void SeparatePlayerKey();

	void InsertEnemyKeyForIndex(const char key[]);
	void CreateSendKey(const int Frame,char prevInput[]);


	char *GetSendKey();


	bool CheckEnemyKey();

	void Used();
	int GetFrame()const;

	bool operator==(const FramePacket& frame) const;
	bool operator==(int id)const;

	bool operator<(const FramePacket& frame) const;

private:
	int FrameID;
	int delay;
	char* EnemyKey[NumOfKeys];
	char* PlayerKey[NumOfKeys];

	char SendKeyCpy[1023];
	char SendKey[1023]; //Player‘¤
	char RecvKey[1023]; //Enemy‘¤

	bool used;

};
