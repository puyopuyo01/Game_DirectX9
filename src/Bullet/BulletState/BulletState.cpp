#include"./BulletState.h"

bool BulletNormal::Draw(Bullet* bullet){
	return true;
}

void BulletNormal::Update(Bullet* bullet,int vec) {
	/*�ړ��ʂ����g�̎��p�����[�^�AFPS�A�x�N�g������Z�o����B*/
	float MoveToY=(*bullet->speed->GetVal()/FRAMEPERSEC)* (float)vec;
	MoveToY += bullet->GetLocation().y;
	bullet->Move(bullet->GetLocation().x, MoveToY);

}