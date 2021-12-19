#pragma once
#include<winsock2.h>
#include <ws2tcpip.h>
#include<stdio.h>
#include<iostream>

#define PORT 56027


void Split(char* a,char *b[] /*ポインタの配列*/ ,char boarder);


/*サーバとの通信クラス…今後実装予定*/
class ConnectServer {
public:
	//int Connect();
private:
	WSADATA NetData;
	SOCKET s;
	sockaddr_in addr;
};




class P2P {
public:
	static P2P* GetInstance();

	~P2P();

	int Init(char *ip);
	int Connect();
	void Close();

	int Send(char msg[]);
	int Recv(char* msg);

	void MtdChange();/*いらないかも*/
protected:
	WSADATA NetData;
	SOCKET s;
	sockaddr_in addr; /*受信用*/
	sockaddr_in send; /*送信用*/

	u_long CommunicationMethod;
private:
	static std::unique_ptr<P2P> SingleTon;
};

