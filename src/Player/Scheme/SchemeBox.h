#pragma once
#include"./Scheme.h"
#include"State/BattleState/StateInBattle/Battle_State_Sub.h"
#include"DX_Lib/Sound/Sound.h"
#include<vector>

class StateInBattle;


/*
�ʐM����Ə����𖵏������Ȃ����߁A�v���C���[���K�E�Z�̃{�^������������ShemeBox�ɓo�^����B
�@���[�J���v���C���[�ƃ����[�g�v���C���[�̕K�E�Z�{�^�����������t���[�������Ԃ�����
 �Ȃ��������Ƃɂ���B
*/
class SchemeBox {
public:
	SchemeBox();
	~SchemeBox();
	void InsertScheme(Scheme* scheme);
	StateInBattle* Update(StateInBattle* nowState);
private:
	std::vector<Scheme*> schemelist;
	Sound* SchemeSE;
};