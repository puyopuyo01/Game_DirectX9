#include"EstCom.h"


EstablishCommunicate::EstablishCommunicate(char *ip) {
	this->ip = ip;
	p2p = P2P::GetInstance();
	InitRes=p2p->Init(ip);
}

EstablishCommunicate::~EstablishCommunicate() {

}


Game_State* EstablishCommunicate::Update(){
	if (InitRes == -3) {
		MessageBox(NULL,
			"失敗しました。IPアドレスを再入力してください。", "失敗", MB_OK);
		return new InputIP();
	}
	if (FAILED(controller->init())) {
		MessageBox(NULL,
			"P", "失敗", MB_OK);
		return this;
	}
	int res = p2p->Connect(); /*ここでNAT越えを行う*/
	if(res==1){
		return new DelayMes();
	}

	return this;
}