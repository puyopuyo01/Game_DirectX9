#pragma once
#include"DXLib_Orig.h"
#include"Screen.h"

/*�����ɕK�v�Ȓ�`*/

#define length 3 //���}�X
#define width 4 //�c�}�X(�v���C���[�}�X+�h�q���C���}�X)
#define PANELWIDTH 3

#define SIZE 5.f

/*��ʒ����Ƀp�l���̒��S������悤�ɂ���B*/
#define Side_Location -12.f-((length/2.f)*SIZE) 	/*�p�l���̉����̍��W ��ʒ������w��*/

/*�p�l���̏c���̍��W*/
#define Player_Location -7.f
#define Enemy_Location (Player_Location+(PANELWIDTH*SIZE))

#define PLAYER 1
#define ENEMY -1

#define OPERATOR 1
#define BULLET 2

extern bool Finish;

extern int Code(float x); //Panel_Field.cpp

extern float UpperPanel;
extern float BottomPanel;