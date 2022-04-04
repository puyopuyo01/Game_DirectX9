#include"Player/Player_State/Player_State.h"

/*移動状態を管理するクラス(Bridgeパターンで実装)*/
HandleMove* IdleMove::Update(Player* player) {
	if (KeyBox::GetInstance()->updateframe == nullptr) { printf("nullです\n"); }
	char* position = KeyBox::GetInstance()->
						updateframe->GetKey(player->GetID(), POSITION);
	printf("position %s Player %d\n", position, player->GetID());
	/*playerの位置するマスの情報 x_yは,xがマスの横の位置、yが縦の位置を意味する。*/
	char* pos[3];
	Split(position,pos, '_');
	printf("why %s %s\n", pos[0],pos[1]);

	int x = atoi(pos[0]);
	int y = atoi(pos[1]);

	/*通信相手の場合の位置を計算する*/
	if (player->GetID() == ENEMY) { 
		y = (width*2)-1 - y; 
		x = length-1 - x;
		printf("成功Enemy %d %d\n", x, y);
	}


	/*移動を開始*/
	Field_Move_Mass* p = Battle_State::Panel_ALL[y][x];
	player->StandPos = p;
	player->Move(p->GetLocation().x, p->GetLocation().y);
	return this;
}
