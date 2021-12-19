#include"./UI.h"


namespace UI {
	MoraleUI::MoraleUI(float x,float y,int MoraleNum) : Field_Object(x, y, 0.f) {
		/*MoraleÉoÅ[êßçÏ*/
		float Width = 20.f;
		float Height = 1.f;
		MoraleBar = new ChargingBar(x,y,Width);

		int i;
		float TempWidth;
		if (MoraleNum != 0) {
			TempWidth = (Width / (float)MoraleNum);
		}
		else { TempWidth = 0.f; }
		for (i = 0; i < MoraleNum; i++) {
			//float pos_x = (TempWidth/2.f)*i - (TempWidth/2.f);
			float pos = (float)i - ((float)MoraleNum / 2.f);
			float pos_x = (TempWidth * pos)+TempWidth/2,f;
			Frame.push_back(new Primitive(SQUARELINE,
											pos_x, y, 0.f,
											TempWidth, Height,
											1.f, 1.f, 1.f, 0.6f));
		}
	}

	MoraleUI::~MoraleUI() {
		vector<Primitive*>::iterator itr = Frame.begin();

		while (itr != Frame.end()) {
			delete *itr;
			*itr = nullptr;
			itr++;
		}

		delete MoraleBar;
	}

	void MoraleUI::UpdateGauge(float MoraleRate) {
		MoraleBar->UpdateGauge(MoraleRate);
	}

	void MoraleUI::Draw() {
		MoraleBar->Draw();

		vector<Primitive*>::iterator itr = Frame.begin();

		while (itr != Frame.end()) {
			(*itr)->Draw(this->GetMatrix());
			itr++;
		}

	}
}