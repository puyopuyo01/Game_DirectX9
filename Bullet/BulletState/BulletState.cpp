#include"./BulletState.h"

bool BulletNormal::Draw(Bullet* bullet){
	return true;
}

void BulletNormal::Update(Bullet* bullet,int vec) {
	float MoveToY=*bullet->speed->GetVal()* (float)vec;
	MoveToY += bullet->GetLocation().y;
	bullet->Move(bullet->GetLocation().x, MoveToY);
}