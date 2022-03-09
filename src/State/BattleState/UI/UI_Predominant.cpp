#include"./UI.h"

namespace UI {
	PredominantBar::PredominantBar(float x, float y,int Max) :Field_Object(x,y,0.f) {
		this->Max = Max;

		Height = (ScreenHeigth() / 3.f) - 5.f;
		float baseHeight = Height / 2.f;

		offsetX = x;
		offsetY = y;
		CurrentPoint = make_unique<PredominantPointer>(PredominantPointer(x,y));
		PlayerSide = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE,x, y - baseHeight, 0.f,
			1.f, Height,
			1.f, 0.1f, 0.1f, 0.8f));
		EnemySide = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE, x, y + baseHeight, 0.f,
			1.f, Height,
			0.1f, 0.1f, 1.0f, 0.8f));

		float lv1_y = y+Height*(1.f / (float)Max); 
		float lv2_y = y+Height*(3.f / (float)Max); 
		float lv3_y = y+Height*(5.f / (float)Max)-0.2f;
		lv1 = make_unique <Primitive>(Primitive(SQUARE, x + 1.f,lv1_y, 0.f,
					2.f,0.5f,
					1.f,1.f,1.f,1.f));
		lv2 = make_unique <Primitive>(Primitive(SQUARE, x + 1.f, lv2_y, 0.f,
			2.f, 0.5f,
			1.f, 1.f, 1.f, 1.f));

		lv3 = make_unique <Primitive>(Primitive(SQUARE, x + 1.f, lv3_y, 0.f,
			2.f, 0.5f,
			1.f, 1.f, 1.f, 1.f));
		lv1Num = make_unique<Number_Symbol>(Number_Symbol(x+4.f,lv1_y,2.f,2.f,1));
		lv2Num = make_unique<Number_Symbol>(Number_Symbol(x+4.f,lv2_y, 2.f, 2.f, 1));
		lv3Num = make_unique<Number_Symbol>(Number_Symbol(x+4.f,lv3_y, 2.f, 2.f, 1));
		lv1Num->Update(1);
		lv2Num->Update(2);
		lv3Num->Update(3);

		PredTemp = 0;
	}


	/*—D¨ƒQ[ƒW*/
	void PredominantBar::UpdateGauge(int gauge,int increase) {
		
		if (increase != 0) {
			if (gauge + increase > Max) { increase = Max-gauge; }
			else if (gauge + increase < -Max) { increase = Max+gauge; }

			CurrentPoint.get()->Move(0.f, CurrentPoint.get()->GetLocation().y+Height*((float)increase/(float)Max));

			PlayerSide->VertexY(UPPERLEFT, CurrentPoint.get()->GetLocation().y + 1.f);
			PlayerSide->VertexY(UPPERRIGHT, CurrentPoint.get()->GetLocation().y +1.f);

			EnemySide->VertexY(LOWERLEFT, CurrentPoint.get()->GetLocation().y + 1.f);
			EnemySide->VertexY(LOWERRIGHT, CurrentPoint.get()->GetLocation().y + 1.f);
			PredTemp = gauge;
		}

	}

	void PredominantBar::Draw() {
		lv1->Draw(this->GetMatrix());
		lv2->Draw(this->GetMatrix());
		lv3->Draw(this->GetMatrix());
		lv1Num->Draw();
		lv2Num->Draw();
		lv3Num->Draw();
		PlayerSide->Draw(this->GetMatrix());
		EnemySide->Draw(this->GetMatrix());
		CurrentPoint->Draw();
	}

	PredominantPointer::PredominantPointer(float x, float y) :Field_Object(0.f, 0.f, 0.f) {
		CurrentPoint = make_unique<Primitive>(Primitive(SQUARE,
			x, y, 0.f,
			2.f, 1.f,
			1.f, 1.f, 1.f, 1.f));
	}

	void PredominantPointer::Draw() {
		CurrentPoint->Draw(this->GetMatrix());
	}
}