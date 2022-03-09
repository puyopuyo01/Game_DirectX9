#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	ChargingUI::ChargingUI(float x, float y) : Field_Object(x, y, 0.f) {
		float sy = y - 4.f;
		float my = y;
		float by = y + 4.f;
		
		Text = Font::GetInstance();

		float bx = 22.f;
		S = new Bullet(ENEMY, SMALLBULLET, x - bx, y - 4.f,SIZE / 3.f);
		M = new Bullet(ENEMY, MIDDLEBULLET, x - bx, y, SIZE / 2.3);
		B = new Bullet(ENEMY, BIGBULLET, x - bx, y + 4.f, SIZE / 1.6f);

		float cx = 16.f;

		SBar = new ChargingBar(x-cx,y-4.f,8.f);
		MBar =  new ChargingBar(x-cx, y, 8.f);
		BBar = new ChargingBar(x-cx, y + 4.f, 8.f);
		Morale = new ChargingBar(x-cx, y + 8.f, 8.f);

		float numberSize = 1.5f;
		float numberHeigth = 3.f;


		float nx = 10.f;
		SNumber = new Number_Symbol(x-nx,sy, numberSize, numberHeigth,2,MULTI);
		MNumber = new Number_Symbol(x-nx, my, numberSize, numberHeigth, 2,MULTI);
		BNumber = new Number_Symbol(x - nx, by, numberSize, numberHeigth, 2, MULTI);
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

		SBar->Draw();
		MBar->Draw();
		BBar->Draw();

		SNumber->Draw();
		MNumber->Draw();
		BNumber->Draw();
	}
}