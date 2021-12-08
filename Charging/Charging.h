#pragma once
#include"Counter/Counter.h"


/*�`���[�W�n����(�����[�h��)�̊��N���X �l(�K�E�Z�|�C���g��H��̎c��)�����̃N���X�ŊǗ�*/
class Charging {
public:
	Charging(int Remain,int Max, int count);
	~Charging();

	void Update();
	bool Available(int Consum); /* ����镪�̒l�������Ă��邩�m�F����֐� */
	bool Consumption(int Consum); /* �l�������֐� */

	int GetRemain();
	int GetMax();

	int GetRemainCounter();
	int GetMaxCounter();

protected:
	int Remain;
	int Max;
	Counter* counter;
};