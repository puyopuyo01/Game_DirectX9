#include"./NetWork.h"

std::unique_ptr<P2P> P2P::SingleTon;

P2P* P2P::GetInstance() {
	if (P2P::SingleTon.get() == nullptr) {
		P2P::SingleTon = std::make_unique<P2P>(P2P());
	}
	return SingleTon.get();
}


/*文字列をboarderで区切り配列に分ける*/
void Split(char* a, char *b[], char boarder) {
	int i=0;

	while (*a != '\0') {
		if (*a != boarder) {	//先頭の文字列がboarderになってないか
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
		*a = '\0'; //boarderをヌル文字に変換。
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
	ioctlsocket(s, FIONBIO, &CommunicationMethod);	//FIONBIOに渡すことでブロッキングI/Oを設定。

	if (s < 0) {
		MessageBox(NULL,
			"Networkの確保に失敗Socket", "失敗", MB_OK);
		WSACleanup();
		return -1;
	}
	memset(&send, 0, sizeof(send));
	send.sin_family = AF_INET;
	send.sin_port = htons(PORT);
	if(inet_pton(send.sin_family, IP, &send.sin_addr.s_addr) != 1) {
		printf("失敗\n");
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
		printf("bind SOCKET_ERROR エラー内容　%d\n",WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -3;
	}


	return 1;
}

#define YSTATE 0


/*通信相手からパケットが届くか確認する関数。　ループさせることでNAT越えを行う。*/
int P2P::Connect() {


	/*「自身の接続状態|相手の接続状態」を送りお互いの状態を確認し合う。そうしなければどちらか一方が接続できても片方ができていないまま次の状態へ進んでしまう。*/
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
	WSAGetLastErrorの戻り値
	WSAWOULDBLOCK…パケットが届いてない
	0…パケットが届いた
	*/

	if (n < 1) {
		if (WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != 0) { 
			MessageBox(NULL,
				"WSAGetLastError", "失敗", MB_OK);
			std::cout << "エラー内容 " << WSAGetLastError() << std::endl; 
			return 2;
		}
		else {
			printf("パケットが届いていません\n");
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
			"WSAGetLastError", "失敗", MB_OK);
		std::cout << "エラー内容 " << WSAGetLastError() << std::endl;
	}
	return n;
}