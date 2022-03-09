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
			"¸”s‚µ‚Ü‚µ‚½BIPƒAƒhƒŒƒX‚ğÄ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B", "¸”s", MB_OK);
		delete this;
		return new InputIP();
	}
	if (FAILED(controller->init())) {
		MessageBox(NULL,
			"P", "¸”s", MB_OK);
		return this;
	}
	int res = p2p->Connect(); /*‚±‚±‚ÅNAT‰z‚¦‚ğs‚¤*/
	if(res==1){
		delete this;
		return new DelayMes();
	}

	return this;
}