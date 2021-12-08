#include"./Battle_State.h"
#include"Player/Character/Character.h"
#include"State/InputIP.h"

float UpperPanel;
float ButtomPanel;

Panel_Field* Battle_State::Panel_ALL[width * 2][length];

int NextFrame(int FrameID) {
	if (FrameID == INT_MAX) { return 0; }
	else { FrameID++;  return FrameID; }
}

void Separate(char *recv,int CreateID) {
	char* IDType[3];
	Split(recv, IDType, '/');
	KeyBox::GetInstance()->ReceiveKey(IDType[1], CreateID);
}

void Game_State::Draw() {
	Update_Draw(objects);
}

int Game_State::AddDrawObject(Field_Object* obj) { objects.push_back(obj); return (int)(objects.size()-1); }
void Game_State::deleteObject(int index) { objects.erase(objects.begin() + index); } 
 
Battle_State::Battle_State(int delay)
{
	Bullet::Init();
	BGM = new Sound("PerituneMaterial_Spook4_loop.wav"); 
	BGM->Play(true);
	File = FileMapping::GetInstance();
	this->Finish = false;

	delayFrame = delay;
	delayFrame += MINIMUMFRAME;
	wait = true;
	WaitingFrame = 0;
	NoReach = 0;
	CreateID = 0;
	ProcessID = 0;
	Communication = P2P::GetInstance();
	KeyBoxes = KeyBox::GetInstance();


	state = new InGame();
	StateInBattle::BaseStateSet(this);
	schemelist = new SchemeBox();
	Predominant = new Numerical<int>(new int(0), new NormalValue<int>(), 100, -100);

	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	/*UI����(�J���������ɂ���ׂ����X�e���V���o�b�t�@�𗘗p)*/
	UI::UIMNG* ui=UI::UIMNG::GetInstance();
	ui->textBoard->SetDelayFrame(delayFrame);
	objects.push_back((Field_Object*)ui->backGround.get());
	objects.push_back((Field_Object*)ui->textBoard.get());
	objects.push_back((Field_Object*)ui->PlayerHP.get());
	objects.push_back((Field_Object*)ui->EnemyHP.get());
	objects.push_back((Field_Object*)ui->Predominant.get());
	objects.push_back((Field_Object*)ui->Charging);

	p_blue = Panel_Blue::GetInstance();
	objects.push_back(p_blue);


	int i = 0, j = 0;
	int fieldID = 0;
	int index_h=0;
	for (i = 0;i <= width;i++) {	//�c
		for (j = 0;j < length;j++) {	//��
			if (i == 0)/*�v���C���[���p�l��*/
			{
				DefensePanel[0][j] = new DefenseMass(
					PLAYER,&DMGPlayerHP,
					j, i, p_blue,
					Side_Location + (SIZE*j), Player_Location+(i*SIZE),1.f,
					1.f, 0.f, 0.f, 0.6f, SIZE);
				Panel_ALL[i][j] = DefensePanel[0][j];
				Panel_Field::AllPanel[i][j] = DefensePanel[0][j];
				objects.push_back((Field_Object*)DefensePanel[0][j]);
				continue;
			}
			if(i == width)	/*�G�p�l��*/
			{
				DefensePanel[1][j] = new DefenseMass(
					ENEMY,&DMGEnemyHP,
					j, i+PANELWIDTH, p_blue,
					Side_Location + (SIZE*j), Enemy_Location + (i*SIZE), 1.f,
					1.f, 0.f, 0.f, 0.6f, SIZE);
				index_h = i+PANELWIDTH;
				Panel_ALL[index_h][j] = DefensePanel[1][j];
				Panel_Field::AllPanel[index_h][j] = DefensePanel[1][j];
				objects.push_back((Field_Object*)DefensePanel[1][j]);
				continue;
			}


			Player_Panel[fieldID][j]=new Panel_Field(j,i,p_blue,
				Side_Location+(SIZE*j), Player_Location+(i*SIZE),1.f,
				0.f, 1.f, 1.f, 0.6f,SIZE,PLAYER);


			Enemy_Panel[fieldID][j]=new Panel_Field(j,i+PANELWIDTH,p_blue,
				Side_Location+(SIZE*j),Enemy_Location+(i*SIZE),1.f,
				1.f, 1.f, 0.f, 0.6f, SIZE,ENEMY);

			Panel_ALL[i][j] = Player_Panel[fieldID][j];
			Panel_Field::AllPanel[i][j] = Player_Panel[fieldID][j];
			index_h = i + PANELWIDTH;
			Panel_ALL[index_h][j] = Enemy_Panel[fieldID][j];
			Panel_Field::AllPanel[index_h][j] = Enemy_Panel[fieldID][j];
			if(j==length-1)fieldID++;

		}
#ifdef _DEBUG
		printf("Call BattleState\n");
#endif
	}

	for (i = 0;i < width-1;i++) {	
		for (j = 0;j < length;j++) {
			objects.push_back((Field_Object*)Player_Panel[i][j]);
			objects.push_back((Field_Object*)Enemy_Panel[i][j]);
		}
	}
	p_blue->Set(Panel_ALL[1][1]);
	ObjectMNG::GetMNG()->player = new Hero(1, 1, Panel_ALL[1][1], PLAYER,&DMGPlayerHP,schemelist);//, Panel_ALL[1][1]->GetLocation().x, Panel_ALL[1][1]->GetLocation().y
	Panel_ALL[1][1]->AddObject(ObjectMNG::GetMNG()->player);

	ObjectMNG::GetMNG()->enemy = new HeroT(1, 6, Panel_ALL[6][1], ENEMY,&DMGEnemyHP,schemelist);
	Panel_ALL[6][1]->AddObject(ObjectMNG::GetMNG()->enemy);

	this->NextState = this;
	return;
}

Battle_State::~Battle_State(){
	int i,j;
	for (i = 0;i < width-1;i++) {	//�c
		for (j = 0;j < length;j++) {	//��
			delete Player_Panel[i][j];
			delete Enemy_Panel[i][j];
		}
	}
	for (i = 0;i < 2;i++) {
		for (j = 0;j < length;j++) {
			delete DefensePanel[i][j];
		}
	}

	delete Predominant;
	delete state;
	delete schemelist;

	delete BGM;

	this->KeyBoxes->Close();
	objects.clear();
}



Game_State* Battle_State::Update() { 
	printf("CreateID Test %d \n",CreateID);
	printf("ProcessID Test %d \n", ProcessID);
	if (NoReach == 0 || wait) {
		//���[�J���v���C���[�̃L�[���擾�BFramePacket�N���X�̐����B
		KeyBoxes->CreateFramePacket(CreateID);
		KeyBoxes->GetPlayerKey(CreateID);
		ObjectMNG::GetMNG()->player->RecordPosition(CreateID);
		KeyBoxes->CreateSendKey(CreateID);
		CreateID = NextFrame(CreateID);
		KeyBoxes->UpdateFrame(ProcessID);
		if (WaitingFrame++ == delayFrame) { wait = false; }
	}

	if (wait) { return this; }
	char recvKey[1023];

	/*
	��������t���[���ɑ���̃L�[�����邩�m�F�B
	�Ȃ���Ύ�M���[�v�B100�t���[���ȏ��M��������ΒʐM�G���[��
	�Q�[�����f�B
	*/
	while(!KeyBoxes->ReachEnemyPacket(ProcessID)) {
		bool Reach = false;
		//�]���ȃp�P�b�g�������疳��
		while (true) {
			int a = Communication->Recv(recvKey);
			if (a < 1) {
				NoReach++;
				printf("�p�P�b�g������܂���\n");
				KeyBoxes->CreateSendKey(CreateID-1);
				KeyBoxes->CreateSendKey(ProcessID);
				return this;
			}
			if (NoReach > 100) {
				printf("�p�P�b�g���͂��Ȃ����ߒʐM���I��\n");
				Abort();  
				return NextState;
			}
			printf("�͂��� %s\n", recvKey);
			if (strncmp(recvKey, "BATTLE", 6) != 0) { printf("��v���Ă��܂���\n"); }
			if (strncmp(recvKey, "BATTLE", 6) == 0) { break; }
		}
		NoReach = 0;
		/*�t���[������M�Bwait+(ping/2)�t���[�����҂ĂΉ�������͂��B*/
		char* IDType[3];
		Split(recvKey, IDType, '/');
		if (strncmp(recvKey, "BATTLE", 6) == 0) { 
			KeyBoxes->ReceiveKey(IDType[1], CreateID); 
		}
		if (KeyBoxes->updateframe == nullptr) { return this; }
	}

	int n;
	n = Communication->Recv(recvKey);
	if(n >= 1){ 
		if (strncmp(recvKey, "BATTLE", 6) == 0) {
			char* IDType[3];
			Split(recvKey,IDType, '/');
			KeyBoxes->ReceiveKey(IDType[1], CreateID);
		}
	}

	StateInBattle* stateTemp = state->update(this);
	if (stateTemp != state) {
		printf("�Ăяo�� stateTemp\n");
		//delete state; �Ȃ����G���[
		state = nullptr;
		state = stateTemp;
	}

	Player* enemy = ObjectMNG::GetMNG()->enemy;
	Player* player = ObjectMNG::GetMNG()->player;

	enemy->hp->AddValue(-DMGEnemyHP);
	player->hp->AddValue(-DMGPlayerHP);
	DMGPlayerHP = 0.f;
	DMGEnemyHP = 0.f;


	if (*player->hp->GetVal() == 0.f || *enemy->hp->GetVal() == 0.f){
		if (!Finish) {
			delete state;
			state = new Result(player, enemy);
			Finish = true;
		}
	}

	UpdateUI();

	KeyBoxes->FinishPacket(ProcessID);

	if (ProcessID == INT_MAX) { Abort();  return NextState; } /*int�̍ő�l�܂ł����狭���I��*/
	ProcessID = NextFrame(ProcessID);

	if (NextState != this) { 
		printf("�Ăяo�� statep\n");
		delete this; }
	return NextState; 
}


/*UI�̍X�V*/

void Battle_State::UpdateUI() {
	PredmGauge += Panel_Field::GetPredmGauge();
	Panel_Field::ResetPredmGauge();

	UI::UIMNG::GetInstance()->Predominant->UpdateGauge(PredmGauge);

	Player* enem = ObjectMNG::GetMNG()->enemy;
	Player* ply = ObjectMNG::GetMNG()->player;


	UI::UIMNG::GetInstance()->PlayerHP->UpdateGauge(ply->MaxHP, *(ply->hp->GetVal()));
	UI::UIMNG::GetInstance()->EnemyHP->UpdateGauge(enem->MaxHP, *(enem->hp->GetVal()));
	
	int MaxMorale = ply->Morale->GetMaxCounter();
	int RemainMorale = ply->Morale->GetRemainCounter();
	float Morale = (float)RemainMorale/(float)MaxMorale;
	float SBullet = (float)ply->SBullet->GetRemainCounter() / (float)ply->SBullet->GetMaxCounter();
	float MBullet = (float)ply->MBullet->GetRemainCounter() / (float)ply->MBullet->GetMaxCounter();
	float BBullet = (float)ply->BBullet->GetRemainCounter() / (float)ply->BBullet->GetMaxCounter();

	UI::UIMNG::GetInstance()->Charging->UpdateGauge(SBullet,MBullet,BBullet,Morale);
	UI::UIMNG::GetInstance()->Charging->UpdateBullet(ply->SBullet->GetRemain(), 
		ply->MBullet->GetRemain(), ply->BBullet->GetRemain(),ply->Morale->GetRemain());

}

void Battle_State::Reset(){
	delayFrame -= MINIMUMFRAME;
	NextState = new Battle_State(delayFrame);
}

void Battle_State::Abort(){
	Communication->Close();
	NextState = new InputIP();
}

