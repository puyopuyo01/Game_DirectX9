#include"./BulletState.h"

bool BulletNormal::Draw(Bullet* bullet){
	return true;
}

void BulletNormal::Update(Bullet* bullet,int vec) {
	/*移動量を自身の持つパラメータ、FPS、ベクトルから算出する。*/
	float MoveToY=(*bullet->speed->GetVal()/FRAMEPERSEC)* (float)vec;
	MoveToY += bullet->GetLocation().y;
	bullet->Move(bullet->GetLocation().x, MoveToY);

}