#include"./Battle_State_Sub.h"
#include"State/CharacterPanel/CharacterPanel.h"


void InterputState::init(StateInBattle* next, int TextureNumber){
	name = "Interput";
	NextState = new WaitingNextState(10, next);
	float x, y;
	SetPosition(&x, &y);

	InFrame = 30; /*キャラクターパネル画像が画面外から入ってくるまでのフレーム*/
	StayFrame = 90; /*キャラクターパネル画像が入ってきて留まるフレーム*/
	OutFrame = 30; /*キャラクターパネル画像が画面外へ出るまでのフレーム*/
	

	CutIn = make_unique<CutInCharacter>(x, y, InFrame, StayFrame, OutFrame, TextureNumber,1,0,-1);
	PanelNum = baseState->AddDrawObject((Field_Object*)CutIn->Panel.get());


	TextNum = -1;

}


InterputState::InterputState(StateInBattle* next, int TextureNumber, string name, string intro) {
	init(next, TextureNumber);
	text = make_unique<TextBox>(200,300,name,intro,30,90,30);
	TextNum = baseState->AddDrawObject((Field_Object*)this->text.get());
}
InterputState::~InterputState() {
	baseState->deleteObject(PanelNum);
	if (text != nullptr) {
		baseState->deleteObject(TextNum - 1);
	}
}

StateInBattle* InterputState::update(Battle_State* state) {
	text->Update();
	if (CutIn->Update()) {
		return NextState;
	}

	return this;
}