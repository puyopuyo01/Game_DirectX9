#include"./UI.h"


namespace UI {
	MoraleUI::MoraleUI(float x,float y,int MoraleNum) : Field_Object(x, y, 0.f) {
		/*ïKéEÉQÅ[ÉWÇÃÉoÅ[êßçÏ*/
		float Width = 55.f;
		float Height = 1.f;
		MoraleBar = new ChargingBar(x,y,Width,1.f,0.f,0.f,0.6f,1.f,1.f,1.f,1.f);

		int i;
		float TempWidth;
		if (MoraleNum != 0) {
			TempWidth = (Width / (float)MoraleNum);
		}
		else { TempWidth = 0.f; }
		for (i = 0; i < MoraleNum; i++) {
			float pos = (float)i - ((float)MoraleNum / 2.f);
			float pos_x = x+(TempWidth * pos)+TempWidth/2.f;
			Frame.push_back(new Primitive(SQUARELINE,
											pos_x, y, 0.f,
											TempWidth, Height,
											1.f, 1.f, 1.f, 1.f));
			if(i == MoraleNum-1){ Number = new Number_Symbol(pos_x + 6.f, y, 1.5f, 3.f, 2, MULTI); }
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
		delete Number;
	}

	void MoraleUI::UpdateGauge(float MoraleRate,int Mol) {
		MoraleBar->UpdateGauge(MoraleRate);
		Number->Update(Mol);
	}

	void MoraleUI::Draw() {
		MoraleBar->Draw();
		Number->Draw();

		vector<Primitive*>::iterator itr = Frame.begin();
		/*ïKéEÉQÅ[ÉWÇÃògÇï`âÊ*/
		while (itr != Frame.end()) {
			(*itr)->Draw(this->GetMatrix());
			itr++;
		}

	}
}