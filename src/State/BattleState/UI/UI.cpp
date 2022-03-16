#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	UI_Base::UI_Base(float x, float y, float z) :Field_Object(x/*(2.f / 3.f)*/, y, z) {
	}

	void UI_Base::Draw() {
		img->Draw(this->GetMatrix());
	}


	/*背景*/

	int BackGround::TextureNumber;

	BackGround::BackGround(float x, float y) :UI_Base(x, y, -2.f) {
		float imgx = ((ScreenLX() + ScreenWidth()) / 2.f)*(2.f/3.f);
		float imgy = (ScreenUpperY() + ScreenHeigth()) / 2.f;
		img = make_unique<Primitive>(SQUARE, ScreenCenterX()-1.f, y, -2.f, ScreenWidth()/*(2.f/3.f)*/, ScreenHeigth(),1.f, 1.f, 1.f, 1.f);
	}

	void BackGround::LoadIMG() {
		TextureNumber = Images::GetInstance()->SaveImage("center2.png");
	}

	void BackGround::Draw() {
		pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		Images::GetInstance()->LoadImage(TextureNumber, 0);
		img->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();

	}



	/*体力バー*/

	int HitPointBar::GaugeTexture;
	int HitPointBar::GaugeCoverTexture;
	int HitPointBar::GaugeBaseTexture;
	
	void HitPointBar::LoadIMG() {
		GaugeTexture = Images::GetInstance()->SaveImage("gauge.png");
		GaugeCoverTexture = Images::GetInstance()->SaveImage("gaugeCover.png");
		GaugeBaseTexture = Images::GetInstance()->SaveImage("gaugeBase.png");
	}

	HitPointBar::HitPointBar(const int LR, float x, float y) :Field_Object(x, y, 0.f) {
		LorR = LR;
		HPwidth = (ScreenWidth() / 2.f)-10.f;
		OriginX = x + ((HPwidth/2.f)*LR);


		Remain = make_unique<PrimitiveUp>(SQUARE,
			x, y, 0.f,
			HPwidth, 3.f,
			1.f, 1.f, 1.f, 1.f);


		if (LR != RIGHTHP) {
			Overall = make_unique<Primitive>(SQUARE,
				x, y, 0.f,
				HPwidth, 3.f,
				1.f, 1.f, 1.f, 1.f,true);
			Cover = make_unique<Primitive>(SQUARE,
				x, y, 0.f,
				HPwidth+2.f, 4.f,
				1.f, 1.f, 1.f, 1.f, true);
			Remain->UVRevers();
		}

		else {
			Overall = make_unique<Primitive>(SQUARE,
				x, y, 0.f,
				HPwidth, 3.f,
				1.f, 1.f, 1.f, 1.f);
			Cover = make_unique<Primitive>(SQUARE,
				x, y, 0.f,
				HPwidth+2.f, 4.f,
				1.f, 1.f, 1.f, 1.f);
		}


	}


	void HitPointBar::UpdateGauge(float MAXHP, float HP) {
		float val = OriginX + ((HP / MAXHP)*HPwidth)*(LorR*-1);
		
		if (LEFTHP == LorR) {
			Remain->VertexX(UPPERLEFT, val);
			Remain->VertexX(LOWERLEFT, val);
		}
		else if (RIGHTHP == LorR) {
			Remain->VertexX(UPPERRIGHT, val);
			Remain->VertexX(LOWERRIGHT, val);
		}
		
	}

	void HitPointBar::Update() {}


	void HitPointBar::Draw() {
		BackGroundTransparent();
		Images::GetInstance()->LoadImage(GaugeBaseTexture, 0);
		Overall->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();
		BackGroundTransparent();
		Images::GetInstance()->LoadImage(GaugeTexture, 0);
		Remain->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();
		BackGroundTransparent();
		Images::GetInstance()->LoadImage(GaugeCoverTexture, 0);
		Cover->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();
	}


	/*テキスト*/

	TextBoard::TextBoard(float x, float y)
		:Field_Object(x, y, 0.f)/*FieldObjectのインスタンス*/ {


		Text = Font::GetInstance();
	}


	void TextBoard::StringUpdate(const int index, string newstr) {
		STR[index] = newstr;
	}

	void TextBoard::SetDelayFrame(const int delay) {
		this->delayFrame = delay;
	}


	void TextBoard::Draw() {

		char d[20];
		snprintf(d, sizeof(d), "delay %d f",this->delayFrame);
		Text->Draw(150, 200, 1500, 1500,d);

		FPS::GetInstance()->Draw();
	}



	unique_ptr<UIMNG> UIMNG::SingleTon;

	UIMNG* UIMNG::GetInstance() {
		if (SingleTon.get() == nullptr) {
			SingleTon.reset(new UIMNG());
		}

		return SingleTon.get();
	}

	UIMNG::UIMNG() {
	}

	void UIMNG::SaveImage() {
		HitPointBar::LoadIMG();
		BackGround::LoadIMG();

	}

	void UIMNG::CreateUI(int PredMax) {
		printf("UI Create \n");

		Predominant = make_unique<PredominantBar>(0.f, 1.f,PredMax);
		printf("Call Predominant Dest \n");


		Charging = new ChargingUI(30.f,0.f);
		printf("Call Charging Dest \n");

		backGround = make_unique<BackGround>(CAMERA_X, CAMERA_Y);
		printf("Call BackGround Dest \n");

		float imgx = CAMERA_X;
		float imgy = CAMERA_Y;
		textBoard = make_unique<TextBoard>(imgx, imgy);

		imgx = ScreenLX() + (ScreenWidth() / 4.f)-1.f;
		imgy = ScreenUpperY();
		PlayerHP = make_unique<HitPointBar>(LEFTHP, imgx, imgy);

		imgx = ScreenLX()+ScreenWidth()*(3.f/4.f)-3.f;
		EnemyHP = make_unique<HitPointBar>(RIGHTHP, imgx, imgy);

		printf("End UI Create \n");
		


	}

	void UIMNG::SetMorale(int MaxMorale) {
		Morale = new MoraleUI(-10.f, -30.f, MaxMorale);
		
	}

	void UIMNG::CreatePanel(int Player, int Enemy) {
		PlayerPanel = new CharacterPanelUI(ScreenLX()+3.f, 0.f,Player);
		EnemyPanel = new CharacterPanelUI(ScreenRX()-10.f, 0.f, Enemy);
	}

	void UIMNG::Release() {

		if (backGround.get() != nullptr) { backGround.reset(); }
		if (textBoard.get() != nullptr) { textBoard.reset(); }
		if (PlayerHP.get() != nullptr) { PlayerHP.reset(); }
		if (EnemyHP.get() != nullptr) { EnemyHP.reset(); }
		if (Predominant.get() != nullptr) { Predominant.reset(); }

		if (Charging != nullptr) { 
			delete Charging;
			Charging = nullptr;
		}
		if (Morale != nullptr) {
			delete Morale;
			Morale = nullptr;
		}
		if (PlayerPanel != nullptr) {
			delete PlayerPanel;
			PlayerPanel = nullptr;
		}
		if (EnemyPanel != nullptr) {
			delete EnemyPanel;
			EnemyPanel = nullptr;
		}
	}

}