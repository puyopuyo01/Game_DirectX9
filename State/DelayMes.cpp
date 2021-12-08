#include"./DelayMes.h"


DelayMes::DelayMes() {
	delay = new DelayMNG();
	this->WaitTime = 60;
	this->wait = 0;
}

Game_State* DelayMes::Update() {
	if (!delay->Update()) {
		return this;
	}
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
	delete delay;
	delete this;
	return new Battle_State(res);
}