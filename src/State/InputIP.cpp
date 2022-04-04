#include"./InputIP.h"


InputIP::InputIP() {
	index = 0;
	inui = make_unique<InputUI>(buf);
	objects.push_back((Field_Object*)inui.get());
	AvalInp = false;
	printf("%d\n", INT_MAX);
}

InputIP::~InputIP() {
}

/*IP�A�h���X�����*/
Game_State* InputIP::Update(){
	if (AvalInp) {
		if (interval++ >= 10) { AvalInp = false; }
		return this;
	}
	if (FAILED(controller->init())) {
		//MessageBox(NULL,"P", "���s", MB_OK);
		return this;
	}
	if (controller->Press(BACK)){
		buf[--index] = '\0';
		if (index < 0) { index = 0; }
		interval = 0;
		AvalInp = true;
	}
	char B=GetNumber();
	if (B != '\0') {
		if (index <=((int)sizeof(buf) / (int)sizeof(buf[0]))) {
			interval = 0;
			buf[index++] = B;
			AvalInp = true;
		}
	}
	else if (controller->Press(ENT)) {
		printf("���͊���\n");
		return new EstablishCommunicate(buf);
	}
	
	return this;
}




InputUI::InputUI(char *buf):Field_Object(0.f, 0.f, 0.f) {
	Text = Font::GetInstance();
	this->buf = buf;
}

void InputUI::Draw() {
	int imgx = (int)(ScreenLX() + (ScreenWidth() / 4.f));
	int imgy = (int)ScreenUpperY();

	const char *res = buf;

	Text->Draw(imgx, imgy, 1000, 1000, 
		"IP�A�h���X����͂��ĉ������B\nWiFi�����L���Ă���ꍇ�̓��[�J��IP����͂��Ă��������B\n�R�}���h�v�����v�g��ipconfig�R�}���h���Ń��[�J��IP�𒲂ׂ邱�Ƃ��o���܂��B");
	Text->Draw(imgx, imgy+300, 1000, 2000, res);
	FPS::GetInstance()->Draw();
}




