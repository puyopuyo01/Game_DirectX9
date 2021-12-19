#pragma once
#include"DXLib_Orig.h"
#include"Screen.h"

/*試合に必要な定義*/

#define length 3 //横マス
#define width 4 //縦マス(プレイヤーマス+防衛ラインマス)
#define PANELWIDTH 3

#define SIZE 5.f

/*画面中央にパネルの中心がくるようにする。*/
#define Side_Location -12.f-((length/2.f)*SIZE) 	/*パネルの横軸の座標 画面中央を指定*/

/*パネルの縦軸の座標*/
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