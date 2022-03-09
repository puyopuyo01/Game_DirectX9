#include"./DrawObject.h"

DrawObject::DrawObject(float x, float y) :Field_Object(x, y, 1.f) { Death = false; }
bool DrawObject::GetDeath() { return Death; }




DrawObjectMNG::DrawObjectMNG():Field_Object(0.f,0.f,0.f){}
DrawObjectMNG::~DrawObjectMNG() {
	list<DrawObject*>::iterator itr = drawobj.begin();
	while (itr != drawobj.end()) {
		delete (*itr);
		itr = drawobj.erase(itr);
	}
}


/*管理しているDrawObjectを更新させる。*/
void DrawObjectMNG::Update() {
	if ((int)drawobj.size() == 0) { return; }
	list<DrawObject*>::iterator itr = drawobj.begin();
	while (itr != drawobj.end()) {
		(*itr)->Update();
		/*DrawObjectは演出等ためのクラスなのでアニメーションが終わればリストから消す。*/
		if ((*itr)->GetDeath()) {
			delete (*itr);
			itr = drawobj.erase(itr);
		}
		else { itr++; }
	}
}


void DrawObjectMNG::Draw() {
	if ((int)drawobj.size() == 0) { return; }
	list<DrawObject*>::iterator itr = drawobj.begin();
	if (itr == drawobj.end()){ return; }
	while (itr != drawobj.end()) {
		(*itr)->Draw();
		itr++;
	}
}


void DrawObjectMNG::AddObject(DrawObject* obj){
	drawobj.push_back(obj);
}