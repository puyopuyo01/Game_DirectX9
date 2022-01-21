#include"./UI.h"


namespace UI {

	void ChargingBar::init(float x, float y, float Width, float r, float g, float b,float a,float fr, float fg, float fb,float fa) {
		Origin = x - (Width / 2.f);
		Remain = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE,
			x, y, 0.f,
			Width, 1.f,
			r,g,b,a));
		Overall = make_unique<Primitive>(Primitive(SQUARELINE,
			x, y, 0.f,
			Width, 1.f,
			fr,fg,fb,fa));

		this->Width = Width;

	}

	ChargingBar::ChargingBar(float x, float y, float Width) : Field_Object(x, y, 0.f) {
		init(x, y, Width, 0.f, 0.7f, 0.3f,1.f,0.f, 0.3f, 0.8f,0.7f);
	}

	ChargingBar::ChargingBar(float x, float y, float Width, float r, float g, float b,float a,
							float fr, float fg, float fb,float fa) : Field_Object(x, y, 0.f) {
		init(x, y, Width,r,g,b,a,fr,fg,fb,fa);
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

