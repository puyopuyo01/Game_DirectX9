#include"BattleState/UI/UI.h"
#include"Bullet/Bullet.h"

namespace UI {
	ChargingUI::ChargingUI(float x, float y) : Field_Object(x, y, 0.f) {
		float sy = y - 4.f;
		float my = y;
		float by = y + 4.f;
		
		Text = Font::GetInstance();

		float bx = 22.f;
		S = make_unique<Bullet>(ENEMY, SMALLBULLET, x - bx, y - 4.f,SIZE / 3.f);
		M = make_unique<Bullet>(ENEMY, MIDDLEBULLET, x - bx, y, SIZE / 2.3f);
		B = make_unique<Bullet>(ENEMY, BIGBULLET, x - bx, y + 4.f, SIZE / 1.6f);

		float cx = 16.f;

		SBar = make_unique<ChargingBar>(x-cx,y-4.f,8.f);
		MBar = make_unique<ChargingBar>(x-cx, y, 8.f);
		BBar = make_unique<ChargingBar>(x-cx, y + 4.f, 8.f);
		Morale = make_unique<ChargingBar>(x-cx, y + 8.f, 8.f);

		float numberSize = 1.5f;
		float numberHeigth = 3.f;


		float nx = 10.f;
		SNumber = make_unique<Number_Symbol>(x-nx,sy, numberSize, numberHeigth,2,MULTI);
		MNumber = make_unique<Number_Symbol>(x-nx, my, numberSize, numberHeigth, 2,MULTI);
		BNumber = make_unique<Number_Symbol>(x - nx, by, numberSize, numberHeigth, 2, MULTI);
	}

	UI::ChargingUI::~ChargingUI() {
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