#pragma once
#include"../NetWork.h"
#include"Battle/BattleDefines.h"
#include<list>
#define Wait 4
#define NumOfKeys 10
#define KeyOnly 8

/*		Player(Enemy)Keyの添え字	 */
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


/*FrameID番目に相手と自分がどの入力をしたか保持するクラス*/
class FramePacket{
public:
	FramePacket(int FrameID,char key[]); /*いらないかも*/
	FramePacket(int FrameID);
	~FramePacket();

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
	char* EnemyKey[NumOfKeys]; /*各入力ごとに分けるための配列*/
	char* PlayerKey[NumOfKeys];

	char SendKeyCpy[1023];
	char SendKey[1023]; //Player側
	char RecvKey[1023]; //Enemy側

	bool used;

};
