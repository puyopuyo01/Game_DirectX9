#include"./UI.h"


namespace UI {
	ChargingBar::ChargingBar(float x, float y, float Width) : Field_Object(x, y, 0.f) {
		Origin = x-(Width/2.f);
		Remain = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE,
			x, y, 0.f,
			Width, 1.f,
			0.f, 0.7f, 0.3f, 1.f));
		Overall = make_unique<Primitive>(Primitive(SQUARELINE,
			x, y, 0.f,
			Width, 1.f,
			0.f, 0.3f, 0.8f, 7.f));

		this->Width = Width;

	}


	void ChargingBar::UpdateGauge(float Rate) {
		float val = Origin + (Rate*Width);
		this->Remain->VertexX(UPPERRIGHT, val);
		this->Remain->VertexX(LOWERRIGHT, val);

	}

	void ChargingBar::Draw() {
		this->Overall->Draw(this->GetMatrix());
		this->Remain->Draw(this->GetMatrix());
	}
}

