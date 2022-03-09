#include"./Battle_State.h"
#include"Player/Character/Character.h"
#include"State/InputIP.h"
#include"SingleTonImage/NumberIMG.h"
#include"Effect/Effect.h"

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
	File = FileMapping::GetInstance();
	ObjectMNG::GetMNG();

	
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
	this->KeyBoxes->Close();

	int* Pred = new int(0);

	state = new InGame();
	StateInBattle::BaseStateSet(this);
	schemelist = new SchemeBox();
	Predominant = new Numerical<int>(Pred, new NormalValue<int>(), 5, -5);



	pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	/*UI����(�J���������ɂ���ׂ����X�e���V���o�b�t�@�𗘗p)*/
	UI::UIMNG* ui = UI::UIMNG::GetInstance();
	ui->CreateUI(5);
	ui->textBoard->SetDelayFrame(delayFrame);
	objects.push_back((Field_Object*)ui->backGround.get());

	objects.push_back((Field_Object*)ObjectMNG::GetMNG()->drawObj);


	p_blue = Panel_Blue::GetInstance();
	objects.push_back(p_blue);





	int i = 0, j = 0;
	int fieldID = 0;
	int index_h=0;
	for (i = 0;i <= width;i++) {	
		for (j = 0;j < length;j++) {	
			if (i == 0)/*�v���C���[���p�l���̐���*/
			{
				DefensePanel[0][j] = new DefenseMass(
					PLAYER,&DMGPlayerHP,
					j, i, p_blue,
					Side_Location + (SIZE*j), Player_Location+(i*SIZE),1.f,
					1.f, 0.f, 0.f, 0.6f, SIZE);
				Panel_ALL[i][j] = DefensePanel[0][j];
				Panel_Field::AllPanel[i][j] = DefensePanel[0][j];
				continue;
			}
			if(i == width)	/*�G���p�l���̐���*/
			{
				DefensePanel[1][j] = new DefenseMass(
					ENEMY,&DMGEnemyHP,
					j, i+PANELWIDTH, p_blue,
					Side_Location + (SIZE*j), Enemy_Location + (i*SIZE), 1.f,
					1.f, 0.f, 0.f, 0.6f, SIZE);
				index_h = i+PANELWIDTH;
				Panel_ALL[index_h][j] = DefensePanel[1][j];
				Panel_Field::AllPanel[index_h][j] = DefensePanel[1][j];
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


	ObjectMNG::GetMNG()->player = new Hero(1, 1, Panel_ALL[1][1], PLAYER, &DMGPlayerHP, Pred,schemelist);
	ObjectMNG::GetMNG()->enemy = new HeroT(1, 6, Panel_ALL[6][1], ENEMY, &DMGEnemyHP, Pred,schemelist);


	/*UI�̐���*/
	ui->CreatePanel(ObjectMNG::GetMNG()->player->portrate, ObjectMNG::GetMNG()->enemy->portrate);
	objects.push_back((Field_Object*)ui->PlayerPanel);
	objects.push_back((Field_Object*)ui->EnemyPanel);

	objects.push_back((Field_Object*)ui->textBoard.get());
	objects.push_back((Field_Object*)ui->PlayerHP.get());
	objects.push_back((Field_Object*)ui->EnemyHP.get());
	objects.push_back((Field_Object*)ui->Predominant.get());
	objects.push_back((Field_Object*)ui->Charging);

	ui->SetMorale(ObjectMNG::GetMNG()->player->Morale->GetMax());
	objects.push_back((Field_Object*)ui->Morale);


	for (i = 0; i < 2; i++) {
		for (j = 0; j < length; j++) {
			objects.push_back((Field_Object*)DefensePanel[i][j]);
		}
	}

	for (i = 0; i < width - 1; i++) {
		for (j = 0; j < length; j++) {
			objects.push_back((Field_Object*)Player_Panel[i][j]);
			objects.push_back((Field_Object*)Enemy_Panel[i][j]);
		}
	}

	p_blue->Set(Panel_ALL[1][1]);


	Panel_ALL[1][1]->AddObject(ObjectMNG::GetMNG()->player);
	Panel_ALL[6][1]->AddObject(ObjectMNG::GetMNG()->enemy);
	ObjectMNG::GetMNG()->AddObject(ObjectMNG::GetMNG()->player);
	ObjectMNG::GetMNG()->AddObject(ObjectMNG::GetMNG()->enemy);

	BGM = new Sound("PerituneMaterial_Spook4_loop.wav");
	BGM->Play(true);
	DmgSE = new Sound("Damage.wav");

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

	BGM->Stop();
	delete BGM;
	delete DmgSE;

	this->KeyBoxes->Close();
	objects.clear();
}



Game_State* Battle_State::Update() { 
	printf("CreateID Test %d \n",CreateID);
	printf("ProcessID Test %d \n", ProcessID);
	/*���͒x�����̃t���[���ҋ@����B*/
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
	�Ȃ���Ύ�M���[�v�B1000�t���[���ȏ��M��������ΒʐM�G���[��
	�Q�[�����f�B
	*/
	while(!KeyBoxes->ReachEnemyPacket(ProcessID)) {
		bool Reach = false;
		while (true) {
			int a = Communication->Recv(recvKey);
			if (a < 1) {
				NoReach++;
				printf("�p�P�b�g������܂���\n");
				KeyBoxes->CreateSendKey(CreateID-1);
				KeyBoxes->CreateSendKey(ProcessID);
				return this;
			}
			if (NoReach > 1000) { 
				printf("�p�P�b�g���͂��Ȃ����ߒʐM���I��\n");
				Abort();  
				delete this;
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
		state = nullptr;
		state = stateTemp;
	}

	if (NextState != this) {
		delete this;
		return NextState;
	}
	

	/*UI�̍X�V����*/
	UpdateUI();


	/*�G�@�Ǝ��@�̗͍̑X�V*/
	Player* enemy = ObjectMNG::GetMNG()->enemy;
	Player* player = ObjectMNG::GetMNG()->player;

	if (DMGPlayerHP != 0 || DMGEnemyHP != 0) { DmgSE->Reset(); DmgSE->Play(false); }

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

	KeyBoxes->FinishPacket(ProcessID);

	if (ProcessID == INT_MAX) { Abort();  return NextState; } /*int�̍ő�l�܂ł����狭���I��*/
	ProcessID = NextFrame(ProcessID);
	return NextState; 
}


/*UI�̍X�V*/

void Battle_State::UpdateUI() {

	/*�D���Q�[�W�̍X�V*/
	UI::UIMNG::GetInstance()->Predominant->UpdateGauge((*Predominant->GetVal()),Panel_Field::GetPredmGauge());
	Predominant->AddValue(Panel_Field::GetPredmGauge());
	Panel_Field::ResetPredmGauge();


	/*HP�̍X�V*/
	Player* enem = ObjectMNG::GetMNG()->enemy;
	Player* ply = ObjectMNG::GetMNG()->player;

	UI::UIMNG::GetInstance()->PlayerHP->UpdateGauge(ply->MaxHP, *(ply->hp->GetVal()));
	UI::UIMNG::GetInstance()->EnemyHP->UpdateGauge(enem->MaxHP, *(enem->hp->GetVal()));


	/*�_���[�W���󂯂��ꍇ�󂯂����̃p�l���e�N�X�`�����_���[�W�p�ɕύX*/
	UI::UIMNG::GetInstance()->PlayerPanel->Update();
	UI::UIMNG::GetInstance()->EnemyPanel->Update();
	if (DMGPlayerHP > 0) { UI::UIMNG::GetInstance()->PlayerPanel->Dmg(ply->damage); }
	if (DMGEnemyHP > 0) { UI::UIMNG::GetInstance()->EnemyPanel->Dmg(enem->damage); }
	

	/*�K�E�Z�Q�[�W,�H��̃����[�h�Q�[�W�̍X�V*/
	int MaxMorale = ply->Morale->GetMaxCounter();
	int RemainMorale = ply->Morale->GetRemainCounter();
	float Morale = (float)RemainMorale/(float)MaxMorale;
	float SBullet = (float)ply->SBullet->GetRemainCounter() / (float)ply->SBullet->GetMaxCounter();
	float MBullet = (float)ply->MBullet->GetRemainCounter() / (float)ply->MBullet->GetMaxCounter();
	float BBullet = (float)ply->BBullet->GetRemainCounter() / (float)ply->BBullet->GetMaxCounter();

	UI::UIMNG::GetInstance()->Charging->UpdateGauge(SBullet,MBullet,BBullet,Morale);
	UI::UIMNG::GetInstance()->Charging->UpdateBullet(ply->SBullet->GetRemain(), 
		ply->MBullet->GetRemain(), ply->BBullet->GetRemain(),ply->Morale->GetRemain());

	float MoraleRate = ((float)ply->Morale->GetRemain()*(float)ply->Morale->GetMaxCounter() + (float)ply->Morale->GetRemainCounter()) /
		((float)ply->Morale->GetMax()*(float)ply->Morale->GetMaxCounter());

	UI::UIMNG::GetInstance()->Morale->UpdateGauge(MoraleRate,ply->Morale->GetRemain());

}

void Battle_State::Reset(){
	ObjectMNG::GetMNG()->SueSide();
	delayFrame -= MINIMUMFRAME;
	NextState = new Battle_State(delayFrame);
}

void Battle_State::Abort(){
	Communication->Close();
	NextState = new InputIP();
}

void Battle_State::LoadIMG() {
	UI::UIMNG::SaveImage();
	Number_Symbol::Init();
	Bullet::Init();
	EffectIMG::LoadImg();
}

