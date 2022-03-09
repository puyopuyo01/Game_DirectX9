#include"./KeyBox.h"

std::unique_ptr<KeyBox> KeyBox::SingleTon;
KeyBox::KeyBox() {
	LatestRecvID = 0;
}
FramePacket* KeyBox::SearchFrame(const int FrameID) {
	auto itr = PacketQueue.begin();
	while (itr != PacketQueue.end()) {
		if ((*itr).get()->GetFrame() == FrameID) {
			return (*itr).get();
		}
		itr++;
	}
	return nullptr;
}
KeyBox* KeyBox::GetInstance() {
	if (KeyBox::SingleTon.get() == nullptr) {
		printf("Create KeyBox\n");
		KeyBox::SingleTon = std::make_unique<KeyBox>(KeyBox());
	}
	return KeyBox::SingleTon.get();
}

/*現在処理しているフレームの通信相手の入力が届いているか判定する関数。*/
bool KeyBox::ReachEnemyPacket(const int ProcessID) {
	FramePacket* frame = SearchFrame(ProcessID);
	if (frame == nullptr) { printf("なし\n"); }
	return frame->CheckEnemyKey();
}


/*キー入力を取得し、FramePacketクラスに記録する関数。*/
void KeyBox::GetPlayerKey(int LatestID) {
	bool create = false;
	FramePacket* Frame = SearchFrame(LatestID);
	if (Frame == nullptr) { 
		FramePacket* newFrame = new FramePacket(LatestID);
		PacketQueue.push_back(unique_ptr<FramePacket>(std::move(newFrame)));
		WaitingPacket.push_back(PacketQueue.back().get());
		Frame = SearchFrame(LatestID);
		create = true;
	}

	/*キーボード初期化*/
	if (FAILED(controller->init())) {
		MessageBox(NULL,
			"P", "失敗", MB_OK);
		return;
	}

	const char* box[] = {"0","1"};

	int i;
	int result[KeyOnly];
	for (i = 0;i < KeyOnly;i++) {
		result[i] = 0;
	}
	if (controller->Press(Q)) { result[QB] = 1; }
	if (controller->Press(W)) { result[WB] = 1; }
	if (controller->Press(E)) { result[EB] = 1; }
	if (controller->Press(R)) { result[RB] = 1; }
	if (controller->Press(F)) { result[FB] = 1; }
	if (controller->Press(G)) { result[GB] = 1; }
	if (controller->Press(SHIFT)) { result[LEFTSHIFT] = 1; }
	if (controller->Press(Space)) { result[SPACE] = 1; }


	for (i = 0;i < KeyOnly;i++) {
		int a = result[i];
		Frame->InsertPlayerKeyForIndex(i, box[a]);
	}

	return;
}


/*プレイヤーの位置を取得し、FramePacketクラスに記録する関数。*/
void KeyBox::SetPlayerPosition(const int FrameID,int x, int y) {
	FramePacket* frame=SearchFrame(FrameID);
	if (frame != nullptr){
		char position[6];
		printf("x = %d,y = %d\n",x,y);
		snprintf(position, sizeof(position), "%d_%d\0", x, y);
		frame->InsertPlayerKeyForIndex(POSITION, position);
		frame->SeparatePlayerKey();
	}
	if (frame == nullptr) {
		printf("SetPlayerPosition is null!! %d\n",FrameID);
	}

}

/*最新のFramePacketクラスを生成する関数。*/
void KeyBox::CreateFramePacket(const int FrameID) {
	if (SearchFrame(FrameID) != nullptr) { return; }
	if (LatestRecvID < FrameID) { LatestRecvID = FrameID; }
	PacketQueue.push_back(make_unique<FramePacket>(FramePacket(FrameID)));
	WaitingPacket.push_back(PacketQueue.back().get());
}
void KeyBox::CreateSendKey(const int FrameID) {
	FramePacket* frame;
	frame = SearchFrame(FrameID);
	char PrevKey[1023] = { '\0' };
	int i;

	/*パケットロスして前のフレームのキー入力が届いていなかったときのため、過去10フレームの入力も送る。*/
	for (i = 1;i <= SENDPREVKEY;i++) {
		FramePacket* prev = SearchFrame(FrameID - i);
		char temp[1023];
		char PrevKeyCpy[1023];
		if (prev == nullptr) { break; }
		snprintf(temp, sizeof(temp), ",%d|%s\0",prev->GetFrame(),prev->GetSendKey());
		strncpy_s(PrevKeyCpy, sizeof(PrevKeyCpy),PrevKey,sizeof(PrevKeyCpy));
		snprintf(PrevKey, sizeof(PrevKey), "%s%s\0",PrevKeyCpy,temp);
	}
	if (frame != nullptr) {
		frame->CreateSendKey(FrameID, PrevKey);
	}
}

/*通信相手から受け取ったパケットを必要な情報ごとに分割する関数*/
void KeyBox::ReceiveKey(const char* key,const int CreateID) {
	if (LatestRecvID <= CreateID) { LatestRecvID = CreateID; }

	int MaxFrame = 0;
	/*	フレームごとに分割　*/
	char Keys[1023];
	strncpy_s(Keys, sizeof(Keys), key, sizeof(Keys));
	char* ID[50];
	Split(Keys,ID,',');	
	std::list<FramePacket*> newPacket;
	int i = 0;
	while(ID[i] != nullptr){
		char* Frame[3];
		Split(ID[i], Frame, '|'); //フレーム番号ごとに分割
		/*受け取ったパケットのフレームIDが自身の端末の最新フレームIDより大きければ、そのフレームIDのFramePacketクラスを生成し、最新フレームIDを更新する*/
		if (LatestRecvID < atoi(Frame[0])) {
			FramePacket* newFrame = new FramePacket(atoi(Frame[0]));
			printf("newパケット\n");
			newFrame->InsertEnemyKeyForIndex(Frame[1]);/*FramePacketクラスに通信相手のキー入力を登録*/
			PacketQueue.push_back(unique_ptr<FramePacket>(std::move(newFrame)));
			MaxFrame = atoi(Frame[0]);
			i++;
			LatestRecvID = MaxFrame;
			continue;
		}
		list<FramePacket*>::iterator itr = WaitingPacket.begin();
		while (itr != WaitingPacket.end()) {
			if ((*itr)->GetFrame() == atoi(Frame[0])) {
				printf("待ちパケット\n");
				(*itr)->InsertEnemyKeyForIndex(Frame[1]);
				itr = WaitingPacket.erase(itr);
				break;
			}
			itr++;
		}
		if (LatestRecvID<MaxFrame) { LatestRecvID = MaxFrame; }
		i++;
	}
}
void KeyBox::UpdateFrame(const int FrameID) {
	/*これから処理するフレームのFramePacketに更新する*/
	updateframe = SearchFrame(FrameID);
	if (updateframe == nullptr) {
		printf("updateFrame == nullptr\n");
	}
	printf("ProcessID %d\n", updateframe->GetFrame());
}
bool KeyBox::FinishPacket(const int FrameID) {
	printf("PacketQueue %d\n",(int)PacketQueue.size());
	list<unique_ptr<FramePacket>>::iterator itr = PacketQueue.begin();
	while (itr != PacketQueue.end()) {
		if ((*itr).get()->GetFrame() == FrameID) {
			itr = PacketQueue.erase(itr);
			updateframe = nullptr;
			return true;
		}
		itr++;
	}
	return false;
}

void KeyBox::Close() {
	WaitingPacket.clear();
	PacketQueue.clear();
	LatestRecvID = 0;


}

void KeyBox::IntReset() {
	LatestRecvID = 0;
}