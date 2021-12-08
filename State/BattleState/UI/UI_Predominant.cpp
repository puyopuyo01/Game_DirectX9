#include"./UI.h"

namespace UI {
	PredominantBar::PredominantBar(float x, float y) :Field_Object(x,y,0.f) {
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
		PredTemp = 0;
	}


	/*—D¨ƒQ[ƒW*/
	void PredominantBar::UpdateGauge(int gauge) {
		

		if (PredTemp != gauge) {

			CurrentPoint.get()->Move(0.f, (float)(gauge));

			PlayerSide->VertexY(UPPERLEFT, CurrentPoint.get()->GetLocation().y + 1.f);
			PlayerSide->VertexY(UPPERRIGHT, CurrentPoint.get()->GetLocation().y + 1.f);

			EnemySide->VertexY(LOWERLEFT, CurrentPoint.get()->GetLocation().y + 1.f);
			EnemySide->VertexY(LOWERRIGHT, CurrentPoint.get()->GetLocation().y + 1.f);
			PredTemp = gauge;
		}

	}

	void PredominantBar::Draw() {
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