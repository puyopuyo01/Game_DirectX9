#include"./NetWork.h"

std::unique_ptr<P2P> P2P::SingleTon;

P2P* P2P::GetInstance() {
	if (P2P::SingleTon.get() == nullptr) {
		P2P::SingleTon = std::make_unique<P2P>(P2P());
	}
	return SingleTon.get();
}


/*�������boarder�ŋ�؂�z��ɕ�����*/
void Split(char* a, char *b[], char boarder) {
	int i=0;

	while (*a != '\0') {
		if (*a != boarder) {	//�擪�̕�����boarder�ɂȂ��ĂȂ���
			b[i++] = a;
		}
		while (*a != boarder) { 
			a++; 
			if (*a == '\0') { break; }
		}

		if (*a == '\0') {
			b[i] = nullptr;
			break; 
		}
		*a = '\0'; //boarder���k�������ɕϊ��B
		a++;
	}


}


P2P::~P2P() {
	Close();
}


void P2P::Close() {
	closesocket(s);
	WSACleanup();
}


int P2P::Init(char *ip) {

	const char* IP = ip;

	if (WSAStartup(MAKEWORD(2, 2), &NetData)) {
		std::cout << "Error" << std::endl;
		return 0;
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);


	CommunicationMethod = 1;
	ioctlsocket(s, FIONBIO, &CommunicationMethod);	//FIONBIO�ɓn�����ƂŃu���b�L���OI/O��ݒ�B

	if (s < 0) {
		MessageBox(NULL,
			"Network�̊m�ۂɎ��sSocket", "���s", MB_OK);
		WSACleanup();
		return -1;
	}
	memset(&send, 0, sizeof(send));
	send.sin_family = AF_INET;
	send.sin_port = htons(PORT);
	if(inet_pton(send.sin_family, IP, &send.sin_addr.s_addr) != 1) {
		printf("���s\n");
		closesocket(s);
		WSACleanup();
		return -3;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);


	printf("%ul\n", send.sin_addr.s_addr);
	int n = bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	if (n == SOCKET_ERROR) {
		printf("bind SOCKET_ERROR �G���[���e�@%d\n",WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -3;
	}


	return 1;
}

#define YSTATE 0


/*�ʐM���肩��p�P�b�g���͂����m�F����֐��B�@���[�v�����邱�Ƃ�NAT�z�����s���B*/
int P2P::Connect() {


	/*�u���g�̐ڑ����|����̐ڑ���ԁv�𑗂肨�݂��̏�Ԃ��m�F�������B�������Ȃ���΂ǂ��炩������ڑ��ł��Ă��Е����ł��Ă��Ȃ��܂܎��̏�Ԃ֐i��ł��܂��B*/
	char MState[1024]="FALSE";

	char YS[10] = "FALSE";
	char *YState = (char*)"FALSE";
	char *RecvState[1024];


	sockaddr_in from;
	bool connection = false;

	int fromlen = (int)sizeof(from);

	char RecvBuf[1024];

	int n = recvfrom(s, RecvBuf, (int)sizeof(RecvBuf),0,(sockaddr *)&from,&fromlen);

	/*
	WSAGetLastError�̖߂�l
	WSAWOULDBLOCK�c�p�P�b�g���͂��ĂȂ�
	0�c�p�P�b�g���͂���
	*/

	if (n < 1) {
		if (WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != 0) { 
			MessageBox(NULL,
				"WSAGetLastError", "���s", MB_OK);
			std::cout << "�G���[���e " << WSAGetLastError() << std::endl; 
			return 2;
		}
		else {
			printf("�p�P�b�g���͂��Ă��܂���\n");
		}
	}
	else {
		char recvip[32];
		inet_ntop(from.sin_family,(in_addr*)&from.sin_addr.s_addr,recvip,sizeof(recvip));
		printf("Recv from %s!!\n",recvip);
		printf("%s\n", RecvBuf);
		connection = true;
		strncpy_s(MState, sizeof(MState),"TRUE",4);

		Split(RecvBuf,RecvState, '|');
		YState=RecvState[YSTATE];
		printf("%s\n%s\n", RecvState[0], RecvState[YSTATE]);
	}

	char SendBuf[1024];
	snprintf(SendBuf, 1024, "%s|%s", MState, YState);

	int sendID = sendto(s, SendBuf, (int)strlen(SendBuf), 0, (LPSOCKADDR)&send, sizeof(send));

	if (strncmp(MState,"TRUE",4)==0 && strncmp(YState,"TRUE",4)==0) {
		printf("%s %s\n", YState, MState);

		printf("Success Connection!!!!\n");
		return 1;
	}

	return 0;
}


int P2P::Send(char msg[]) {
	int sendID = sendto(s,msg,(int)strlen(msg)+1,0,(LPSOCKADDR)&send,sizeof(send));
	return sendID;
}

int P2P::Recv(char* msg) {
	sockaddr_in from;
	int fromlen = (int)sizeof(from);
	int n = recvfrom(s, msg,(int)sizeof(char) * 1023, 0, (sockaddr *)&from,&fromlen);
	if (WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != 0) {
		printf("%d\n", WSAGetLastError()); //10040
		printf("%s\n", msg);
		MessageBox(NULL,
			"WSAGetLastError", "���s", MB_OK);
		std::cout << "�G���[���e " << WSAGetLastError() << std::endl;
	}
	return n;
}