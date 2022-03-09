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

/*���ݏ������Ă���t���[���̒ʐM����̓��͂��͂��Ă��邩���肷��֐��B*/
bool KeyBox::ReachEnemyPacket(const int ProcessID) {
	FramePacket* frame = SearchFrame(ProcessID);
	if (frame == nullptr) { printf("�Ȃ�\n"); }
	return frame->CheckEnemyKey();
}


/*�L�[���͂��擾���AFramePacket�N���X�ɋL�^����֐��B*/
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

	/*�L�[�{�[�h������*/
	if (FAILED(controller->init())) {
		MessageBox(NULL,
			"P", "���s", MB_OK);
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


/*�v���C���[�̈ʒu���擾���AFramePacket�N���X�ɋL�^����֐��B*/
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

/*�ŐV��FramePacket�N���X�𐶐�����֐��B*/
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

	/*�p�P�b�g���X���đO�̃t���[���̃L�[���͂��͂��Ă��Ȃ������Ƃ��̂��߁A�ߋ�10�t���[���̓��͂�����B*/
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

/*�ʐM���肩��󂯎�����p�P�b�g��K�v�ȏ�񂲂Ƃɕ�������֐�*/
void KeyBox::ReceiveKey(const char* key,const int CreateID) {
	if (LatestRecvID <= CreateID) { LatestRecvID = CreateID; }

	int MaxFrame = 0;
	/*	�t���[�����Ƃɕ����@*/
	char Keys[1023];
	strncpy_s(Keys, sizeof(Keys), key, sizeof(Keys));
	char* ID[50];
	Split(Keys,ID,',');	
	std::list<FramePacket*> newPacket;
	int i = 0;
	while(ID[i] != nullptr){
		char* Frame[3];
		Split(ID[i], Frame, '|'); //�t���[���ԍ����Ƃɕ���
		/*�󂯎�����p�P�b�g�̃t���[��ID�����g�̒[���̍ŐV�t���[��ID���傫����΁A���̃t���[��ID��FramePacket�N���X�𐶐����A�ŐV�t���[��ID���X�V����*/
		if (LatestRecvID < atoi(Frame[0])) {
			FramePacket* newFrame = new FramePacket(atoi(Frame[0]));
			printf("new�p�P�b�g\n");
			newFrame->InsertEnemyKeyForIndex(Frame[1]);/*FramePacket�N���X�ɒʐM����̃L�[���͂�o�^*/
			PacketQueue.push_back(unique_ptr<FramePacket>(std::move(newFrame)));
			MaxFrame = atoi(Frame[0]);
			i++;
			LatestRecvID = MaxFrame;
			continue;
		}
		list<FramePacket*>::iterator itr = WaitingPacket.begin();
		while (itr != WaitingPacket.end()) {
			if ((*itr)->GetFrame() == atoi(Frame[0])) {
				printf("�҂��p�P�b�g\n");
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
	/*���ꂩ�珈������t���[����FramePacket�ɍX�V����*/
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