#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	ChargingUI::ChargingUI(float x, float y) : Field_Object(x, y, 0.f) {
		Text = Font::GetInstance();
		S = new Bullet(ENEMY, SMALLBULLET, 1, y, new NonCharacteristic(), x-8.f, y-4.f, SIZE / 3.f);
		M = new Bullet(ENEMY, MIDDLEBULLET, 1, y, new Shield(PLAYER, x, y, SIZE / 2.3f), x-8.f, y, SIZE / 2.3f);
		B = new Bullet(ENEMY, BIGBULLET, 1, y, new NonCharacteristic(), x-8.f, y+4.f, SIZE / 1.6f);


		SBar = new ChargingBar(x,y-4.f,8.f);
		MBar =  new ChargingBar(x, y, 8.f);
		BBar = new ChargingBar(x, y + 4.f, 8.f);
		Morale = new ChargingBar(x, y + 8.f, 8.f);
		SB[0] =  '\0'; MB[0] = '\0'; BB[0] = '\0';Mo[0] = '\0';
	}

	UI::ChargingUI::~ChargingUI() {
		delete S;
		delete M;
		delete B;
	}

	void ChargingUI::UpdateGauge(float S_Rate, float M_Rate, float B_Rate, float MoraleRate) {
		SBar->UpdateGauge(S_Rate);
		MBar->UpdateGauge(M_Rate);
		BBar->UpdateGauge(B_Rate);
		Morale->UpdateGauge(MoraleRate);



	}

	void ChargingUI::UpdateBullet(int S, int M, int B,int Morale) {
		snprintf(SB, sizeof(SB), "~%d", S);
		snprintf(MB, sizeof(MB), "~%d", M);
		snprintf(BB, sizeof(BB), "~%d", B);
		snprintf(Mo, sizeof(Mo), "‹Z~%d", Morale);

	}

	void ChargingUI::Draw() {
		S->Draw();
		M->Draw();
		B->Draw();

		Morale->Draw();

		SBar->Draw();
		MBar->Draw();
		BBar->Draw();

		Text->Draw(271, 385, 1000, 2000, Mo);
		Text->Draw(282, 427, 1000, 2000, BB);
		Text->Draw(282, 470, 1000, 1000, MB);
		Text->Draw(282, 519, 1000, 1000, SB);
	}
}