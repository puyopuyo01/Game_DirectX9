#include"Delay.h"

DelayMNG::DelayMNG() {
	this->SendID = 0;
	this->LatestID = 0;
	this->SendFinish = false;
	this->RecvFinish = false;
	int i;
	for (i = 0;i < NUMBER_AVERAGE;i++) {
		delayList[i] = new Delay(i);
	}
}

DelayMNG::~DelayMNG() {
	int i;
	for (i = 0;i < NUMBER_AVERAGE;i++) {
		delete delayList[i];
	}

}

/*遅延計測関数。計測が終わったらfalseを返す*/
bool DelayMNG::Update() {
	if (SendFinish && RecvFinish) {
		this->AverageFrame = (int)((this->AverageFrame + this->PartnerDelay) / 2);
		return true;
	}
	int i;
	for (i = 0;i < SendID;i++) {
		if (!delayList[i]->finish) {
			delayList[i]->Update();
			if (delayList[i]->wait >= MAXDELAY) {
				//このフレームを超えたらパケットロスと判断。再送信。
				delayList[i]->wait = 0;
				char send[20];
				snprintf(send,sizeof(send),"%s/%d",DELAYSEND, delayList[i]->ID);
				P2P::GetInstance()->Send(send);
			}
		}
	}

	if (SendID < NUMBER_AVERAGE) {
		char send[20];
		snprintf(send, sizeof(send), "%s/%d", DELAYSEND, SendID);
		P2P::GetInstance()->Send(send);
		SendID++;
	}
	
	int resp = 1;

	/*ping値を計測するための応答用パケットが来てないか、また応答用パケットを送る要請が確認するためのループ*/
	while(resp >= 1){
		char recvkey[1023] = { '\0' };
		resp = P2P::GetInstance()->Recv(recvkey);
		if (resp<1) {break;}
		printf("%s\n", recvkey);
		char* split[5];
		Split(recvkey, split, '/');
		/*相手から応答用パケットを送ってほしいと要請が来た*/
		if (strncmp(split[0],DELAYSEND,7) == 0){
			char reply[20] = { '\0' };
			snprintf(reply, sizeof(reply), "%s/%s", DELAYREPLY,split[1]);
			P2P::GetInstance()->Send(reply);
			printf("split = %s\n",split[1]);	

		}
		/*ping値を計測するための応答用パケットが来た*/
		else if (strncmp(split[0], DELAYREPLY,7) == 0){
			int ID = atoi(split[1]);
			printf("ID = %d\n", ID);
			delayList[ID]->Finish();
			if (ID > this->LatestID) {
				this->LatestID = ID;
			}
		}
		/*通信相手から計測終了の通知が来た*/
		else if (strncmp(split[0], DELAYFINISH, 12) == 0) {
			printf("DelayFinishを処理\n");
			RecvFinish = true;
			this->PartnerDelay = atoi(split[1]);
			break;
		}
		else if(strncmp(split[0],FINISHACK, 10)==0){
			SendFinish = true;
		}
		else {
			break;
		}
	}
	if (this->LatestID >= NUMBER_AVERAGE-1){
		this->AverageFrame = this->Average();
		//50回計測出来たら終わったことを伝えるパケットを送信。
		char finish[20] = { '\0' };
		snprintf(finish, sizeof(finish), "%s/%d",DELAYFINISH,this->AverageFrame);
		printf("finish %s\n", finish);
		//相手の計測が終わるまで送り続ける
		P2P::GetInstance()->Send(finish); 
		if (RecvFinish) {
			int i = 0;
			for (i = 0;i < 10;i++) {P2P::GetInstance()->Send(finish);}
		}
		SendFinish = true;
	}
	return false;

}

/*計測した遅延から平均を求める*/
int DelayMNG::Average() {
	int i;
	int denom=0;
	int sum = 0;
	for (i = 0;i < NUMBER_AVERAGE;i++) {
		if(delayList[i]->finish){
			denom++;
			sum += delayList[i]->delay;
		}
	}
	if (denom == 0) {
		MessageBox(NULL,
	"P", "delayが計測出きません", MB_OK);
	}
	return int((sum / denom) + 0.5);
}


Delay::Delay(int ID) {
	this->ID = ID;
	this->wait = 0;
	this->finish = false;
}

void Delay::Finish() {
	this->delay = int((this->wait/2)+0.5);
	printf("delay = %d,%d\n", this->delay,this->ID);
	this->finish = true;
}


void Delay::Update() {
	this->wait++;
}