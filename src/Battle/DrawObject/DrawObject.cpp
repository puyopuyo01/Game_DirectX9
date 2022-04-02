#include"./DrawObject.h"

DrawObject::DrawObject(float x, float y) :Field_Object(x, y, 1.f) { Death = false; }
DrawObject::~DrawObject() {  }
bool DrawObject::GetDeath() { return Death; }




DrawObjectMNG::DrawObjectMNG():Field_Object(0.f,0.f,0.f){}
DrawObjectMNG::~DrawObjectMNG() {
	list<unique_ptr<DrawObject>>::iterator itr = drawobj.begin();
	while (itr != drawobj.end()) {
		itr = drawobj.erase(itr);
	}
}


/*�Ǘ����Ă���DrawObject���X�V������B*/
void DrawObjectMNG::Update() {
	if ((int)drawobj.size() == 0) { return; }
	list<unique_ptr<DrawObject>>::iterator itr = drawobj.begin();
	while (itr != drawobj.end()) {
		(*itr)->Update();
		/*DrawObject�͉��o�����߂̃N���X�Ȃ̂ŃA�j���[�V�������I���΃��X�g��������B*/
		if ((*itr)->GetDeath()) {
			itr = drawobj.erase(itr);
		}
		else { itr++; }
	}
}


void DrawObjectMNG::Draw() {
	if ((int)drawobj.size() == 0) { return; }
	list<unique_ptr<DrawObject>>::iterator itr = drawobj.begin();
	if (itr == drawobj.end()){ return; }
	while (itr != drawobj.end()) {
		(*itr)->Draw();
		itr++;
	}
}


void DrawObjectMNG::AddObject(DrawObject* obj){
	drawobj.push_back(unique_ptr<DrawObject>(std::move(obj)));
}