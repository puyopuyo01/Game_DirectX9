#include"Frame.h"

FramePacket::FramePacket(int FrameID,char key[]) {
	this->FrameID = FrameID;
	this->RecvKey[0] = '\0';
	this->SendKey[0] = '\0';
}
FramePacket::FramePacket(int FrameID){
	this->FrameID = FrameID;
	this->RecvKey[0] = '\0';
	this->SendKey[0] = '\0';

	used = false;

}

void FramePacket::InsertEnemyKeyForIndex(const char key[]) {
	printf("EnemyKey is %s %d\n", key, this->FrameID);
	strncpy_s(RecvKey,sizeof(RecvKey), key, sizeof(RecvKey));
	Split(RecvKey, EnemyKey, '-');

}

void FramePacket::InsertPlayerKeyForIndex(const int index,const char* key) {
	//printf("%s\n", key);
	char temp[1023];
	strncpy_s(temp,sizeof(SendKey),SendKey,sizeof(SendKey));
	if (temp[0] == '\0') {
		snprintf(SendKey, sizeof(SendKey), "%s\0" ,key);
		return;
	}
	//printf("%s\n", temp);
	snprintf(SendKey, sizeof(SendKey), "%s-%s\0",temp, key);
}

void FramePacket::SeparatePlayerKey() {
	strncpy_s(SendKeyCpy, sizeof(SendKeyCpy),SendKey, sizeof(SendKey));
	Split(SendKeyCpy,PlayerKey, '-');
	printf("PlayerKey %s\n",SendKey);
}

int FramePacket::GetFrame() const{
	return FrameID;
}
char* FramePacket::GetKey(int PlayerID,int index) {
	if (PlayerID == PLAYER) {
		return PlayerKey[index];
	}
	else if (PlayerID == ENEMY) {
		return EnemyKey[index];
	}

	MessageBox(NULL,
		"PlayerIDがありません", "FramePacket::GetKey", MB_OK);
	return nullptr;
}
void FramePacket::Used() {
	used = true;
	return;
}
bool FramePacket::CheckEnemyKey() {
	if (RecvKey[0] == '\0') {
		return false;
	}
	return true;
}
bool FramePacket::operator<(const FramePacket& frame) const{
	return this->FrameID < frame.FrameID;
}
bool FramePacket::operator==(const int id)const {
	return FrameID == id;
}

bool FramePacket::operator==(const FramePacket& frame) const {
	return FrameID == frame.GetFrame();
}
void InsertFrame(list<FramePacket> frame, FramePacket* packet){
	
	return;
}


char *FramePacket::GetSendKey() {
	return SendKey;
}


//TODO ......
void FramePacket::CreateSendKey(const int FrameID,char prevInput[]) {
	char Sending[1023];
	char temp[1023] = { '\0' };
	//strncpy_s(temp,sizeof(SendKey),SendKey,sizeof(SendKey));
	/* パケット種類/フレーム番号|キー入力-入力-…,フレーム番号|キー入力-入力-… */
	snprintf(temp, sizeof(temp), "%d|%s\0", FrameID,SendKey);
	//prevInputは,から始まるからこっちで,を付け足さなくていい
	//tempとprevInの繋がりが上手くいっていない
	snprintf(Sending, sizeof(Sending), "%s/%s%s","BATTLE",temp,prevInput);
	printf("CreateKey is %s\n", Sending);
	printf("temp is %s\n", temp);
	printf("SendKey is %s\n", SendKey);
	int sendID = P2P::GetInstance()->Send(Sending);
	return;
}