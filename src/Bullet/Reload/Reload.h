#pragma once
#include"Charging/Charging.h"

/*���@�A�G�@���H������Ă鐔�A���Ă�H�삪+1�����܂ł̃`���[�W�ʂ��Ǘ�����B*/
class Reload:public Charging{
public:
	Reload(int Remain,int MaxBullet,int count);
	~Reload();

	void AddBullet(int bullet);
	void ChangeMaxBullet(int MaxBullet); /*���Ă�H��̍ő�l��ύX����B*/
	void AddMaxBullet(int AddBullet);/*���Ă�H��̍ő�l�����Z����B*/

	void AddCount(int Count); /*���Ă�H�삪 + 1�����܂ł̃`���[�W�ʂ�ύX����*/
	void ChangeCount(int Count);/*���Ă�H�삪 + 1�����܂ł̃`���[�W�ʂ����Z����*/

};