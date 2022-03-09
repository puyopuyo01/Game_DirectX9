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
			"���s���܂����BIP�A�h���X���ē��͂��Ă��������B", "���s", MB_OK);
		delete this;
		return new InputIP();
	}
	if (FAILED(controller->init())) {
		MessageBox(NULL,
			"P", "���s", MB_OK);
		return this;
	}
	int res = p2p->Connect(); /*������NAT�z�����s��*/
	if(res==1){
		delete this;
		return new DelayMes();
	}

	return this;
}