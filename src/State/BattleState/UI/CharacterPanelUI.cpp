#include"./UI.h"
#include"Counter/Counter.h"

using namespace UI;
namespace UI {
	CharacterPanelUI::CharacterPanelUI(float x, float y, int TextureNumber) :Field_Object(0.f, 0.f, -2.f) {
		this->TextureNumber = TextureNumber;
		this->TextureMem = TextureNumber;
		this->Height = ScreenHeigth() - 7.f;
		this->Width = this->Height*0.7f;
		img = make_unique<Primitive>(Primitive(SQUARE, 0.f, 0.f, -2.f, this->Width, this->Height, 1.f, 1.f, 1.f, 1.f));

		counter = new Counter(60);
		DMG = false;

		Move(x, y);
	}

	CharacterPanelUI::~CharacterPanelUI() {
		delete counter;
	}

	void CharacterPanelUI::Update() {
		if (!DMG) { return; }
		if (counter->Update()) {
			DMG = false;
			TextureNumber = TextureMem;
		}
	}

	void CharacterPanelUI::Draw() {
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
		Images::GetInstance()->LoadImage(this->TextureNumber, 0);
		img->Draw(this->GetMatrix());
		Images::GetInstance()->Reset();
	}

	void CharacterPanelUI::Dmg(int texture) {
		counter->Reset();
		DMG = true;
		TextureNumber = texture;
	}


	
}


