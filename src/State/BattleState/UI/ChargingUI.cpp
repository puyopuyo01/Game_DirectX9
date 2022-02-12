#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	ChargingUI::ChargingUI(float x, float y) : Field_Object(x, y, 0.f) {
		float sy = y - 4.f;
		float my = y;
		float by = y + 4.f;
		
		Text = Font::GetInstance();
		S = new Bullet(ENEMY, SMALLBULLET, x - 8.f, y - 4.f,SIZE / 3.f);
		M = new Bullet(ENEMY, MIDDLEBULLET, x - 8.f, y, SIZE / 2.3);
		B = new Bullet(ENEMY, BIGBULLET, x - 8.f, y + 4.f, SIZE / 1.6f);


		SBar = new ChargingBar(x,y-4.f,8.f);
		MBar =  new ChargingBar(x, y, 8.f);
		BBar = new ChargingBar(x, y + 4.f, 8.f);
		Morale = new ChargingBar(x, y + 8.f, 8.f);

		float numberSize = 1.5f;
		float numberHeigth = 3.f;

		SNumber = new Number_Symbol(x+(8.f/2.f)+3.f,sy, numberSize, numberHeigth,2,MULTI);
		MNumber = new Number_Symbol(x + (8.f / 2.f) + 3.f, my, numberSize, numberHeigth, 2,MULTI);
		BNumber = new Number_Symbol(x + (8.f / 2.f) + 3.f, by, numberSize, numberHeigth, 2,MULTI);
		SB[0] =  '\0'; MB[0] = '\0'; BB[0] = '\0';Mo[0] = '\0';
	}

	UI::ChargingUI::~ChargingUI() {
		delete S;
		delete M;
		delete B;

		delete SBar;
		delete MBar;
		delete BBar;

		delete SNumber;
		delete MNumber;
		delete BNumber;

		
	}

	void ChargingUI::UpdateGauge(float S_Rate, float M_Rate, float B_Rate, float MoraleRate) {
		SBar->UpdateGauge(S_Rate);
		MBar->UpdateGauge(M_Rate);
		BBar->UpdateGauge(B_Rate);
		Morale->UpdateGauge(MoraleRate);



	}

	void ChargingUI::UpdateBullet(int S, int M, int B,int Morale) {
		SNumber->Update(S);
		MNumber->Update(M);
		BNumber->Update(B);


	}

	void ChargingUI::Draw() {

		S->Draw();
		M->Draw();
		B->Draw();

		//Morale->Draw();

		SBar->Draw();
		MBar->Draw();
		BBar->Draw();

		SNumber->Draw();
		MNumber->Draw();
		BNumber->Draw();
	}
}