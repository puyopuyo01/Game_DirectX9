#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	UI_Base::UI_Base(float x, float y, float z) :Field_Object(x*(2.f / 3.f), y, z) {
	}

	void UI_Base::Draw() {
		img->Draw(this->GetMatrix());
	}


	/*背景*/

	int BackGround::TextureNumber;

	BackGround::BackGround(float x, float y) :UI_Base(x, y, -2.f) {
		float imgx = ((ScreenLX()+ScreenWidth()) / 2.f)*(2.f/3.f);
		float imgy = (ScreenUpperY() + ScreenHeigth()) / 2.f;
		img = make_unique<Primitive>(Primitive(SQUARE, -12.f, y, -2.f, ScreenWidth()*(2.f/3.f), ScreenHeigth(),1.f, 1.f, 1.f, 1.f));
		TextureNumber = Images::GetInstance()->SaveImage("center2.png");
	}

	void BackGround::Draw() {
		//pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		Images::GetInstance()->LoadImage(TextureNumber, 0);
		img->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();

	}



	/*体力バー*/


	HitPointBar::HitPointBar(const int LR, float x, float y) :Field_Object(x, y, 0.f) {
		LorR = LR;
		HPwidth = (ScreenWidth() / 2.f)-4.f;
		OriginX = x + ((HPwidth/2.f)*LR);
		Overall = make_unique<Primitive>(Primitive(SQUARE,
			x, y, 0.f,
			HPwidth, 3.f,
			1.f, 0.f, 0.f, 1.f));
		Remain = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE,
			x, y, 0.f,
			HPwidth, 3.f,
			0.f, 1.f, 0.f, 1.f));

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
		pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		Overall->Draw(this->GetMatrix());
		Remain->Draw(this->GetMatrix());
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

	void UIMNG::CreateUI() {
		Predominant = make_unique<PredominantBar>(PredominantBar(0.f, 1.f));

		Charging = new ChargingUI(30.f,0.f);

		backGround.reset(new BackGround(CAMERA_X, CAMERA_Y));

		float imgx = CAMERA_X;
		float imgy = CAMERA_Y;
		textBoard.reset(new TextBoard(imgx, imgy));

		imgx = ScreenLX() + (ScreenWidth() / 4.f)-1.f;
		imgy = ScreenUpperY();
		PlayerHP.reset(new HitPointBar(LEFTHP, imgx, imgy));

		imgx = ScreenLX()+ScreenWidth()*(3.f/4.f)-3.f;
		EnemyHP.reset(new HitPointBar(RIGHTHP, imgx, imgy));


	}

	void UIMNG::SetMorale(int MaxMorale) {
		Morale = new MoraleUI(0.f, 0.f, MaxMorale);
		
	}

	void UIMNG::Release() {
		delete Charging;
		delete Morale;
	}

}