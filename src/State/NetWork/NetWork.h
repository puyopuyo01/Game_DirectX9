#pragma once
#include<winsock2.h>
#include <ws2tcpip.h>
#include<stdio.h>
#include<iostream>

#define PORT 56027


void Split(char* a,char *b[] /*�|�C���^�̔z��*/ ,char boarder);


/*�T�[�o�Ƃ̒ʐM�N���X�c��������\��*/
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

	void MtdChange();/*����Ȃ�����*/
protected:
	WSADATA NetData;
	SOCKET s;
	sockaddr_in addr; /*��M�p*/
	sockaddr_in send; /*���M�p*/

	u_long CommunicationMethod;
private:
	static std::unique_ptr<P2P> SingleTon;
};

