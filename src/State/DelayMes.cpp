#include"./DelayMes.h"


DelayMes::DelayMes() {
	delay = make_unique<DelayMNG>();
	this->WaitTime = 60;
	this->wait = 0;
}

Game_State* DelayMes::Update() {
	if (!delay->Update()) { /*遅延計測*/
		return this;
	}
	/*計測が終わったら1秒間待機*/
	if (wait <= WaitTime) {
		wait++;
		char recv[1023] = { '\0' };
		int n;
		n=P2P::GetInstance()->Recv(recv);
		char *Battle[3];
		Split(recv, Battle, '/');
		if (strncmp(recv, "Battle", 6) != 0) {
			return this;
		}
	}

	int res = delay->AverageFrame;
	printf("averageDelay = %d\n", delay->AverageFrame);
	return new Battle_State(res);
}