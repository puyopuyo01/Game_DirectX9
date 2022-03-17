#include"Shape.h"
using namespace std;


unique_ptr<Panel_Blue> Panel_Blue::SingleTon;
Panel_Blue* Panel_Blue::GetInstance() {
	if (SingleTon == nullptr) {
		SingleTon = make_unique<Panel_Blue>();
	}
	return SingleTon.get();
}

void Panel_Blue::Set(Panel_Field* offset) {
	if (SingleTon.get() == nullptr) {
		return;
	}
	SingleTon.get()->Location = nullptr;
}



Panel_Blue::Panel_Blue():Shape(0.f,0.f,0.f)
{
	EXIST = true;
	LocationX = 0;
	LocationY = 0;
	size = SIZE;
	img = make_unique<Primitive>(SQUARE,0.f, 0.f, -1.f,SIZE,SIZE,0.f, 0.f, 1.f, 1.f);
	return;
};


/*ゲーム内カーソルがPanel_Field上にきたらそのパネルを保持する。*/
void Panel_Blue::notif(Panel_Field* location,int x,int y){
	if (location == nullptr) {
		Location = nullptr;
		EXIST = false;
		return;
	}
	Location = location;
	this->x = x; this->y = y;
	this->Move(location->GetLocation().x,location->GetLocation().y);
	if (!EXIST) { EXIST = true; }

	return;
}

void Panel_Blue::Update() {

}

void Panel_Blue::Draw() {
	if (Location == nullptr) {
		return;
	}
	Images::GetInstance()->Reset();
	img->Draw(GetMatrix());
}