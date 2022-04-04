#pragma once
#include"State/NetWork/NetWork.h"
#include<vector>

#define MINIMUMDELAY 3

#define MAXDELAY 30

#define NUMBER_AVERAGE 50

#define DELAYSEND "RESPREQ"
#define DELAYREPLY "RESPONE"
#define DELAYFINISH "DELAYFINISH"
#define FINISHACK "FINISHACK"

/*Delay�̌v���c���݂��Ɍv���I�������delay�l�����������Ă��̕��ς��Ƃ�B*/

class Delay;

class DelayMNG {
public:
	~DelayMNG();
	DelayMNG();

	int AverageFrame;


	bool Update();
	int Average();
	Delay* delayList[NUMBER_AVERAGE];
private:
	int FrameID;
	int SendID;
	int LatestID;
	bool SendFinish;
	bool RecvFinish;

	int PartnerDelay;
};


class Delay {
public:
	Delay(int ID);
	void Update();
	void Finish();
	bool finish;
	int wait;

	int delay;
	int ID;
};