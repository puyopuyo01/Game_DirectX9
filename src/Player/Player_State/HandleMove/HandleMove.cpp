#include"Player/Player_State/Player_State.h"

/*�ړ���Ԃ��Ǘ�����N���X(Bridge�p�^�[���Ŏ���)*/
HandleMove* IdleMove::Update(Player* player) {
	if (KeyBox::GetInstance()->updateframe == nullptr) { printf("null�ł�\n"); }
	char* position = KeyBox::GetInstance()->
						updateframe->GetKey(player->GetID(), POSITION);
	printf("position %s Player %d\n", position, player->GetID());
	char* pos[3];
	Split(position,pos, '_');
	printf("why %s %s\n", pos[0],pos[1]);

	int x = atoi(pos[0]);
	int y = atoi(pos[1]);

	/*�ʐM����̏ꍇ�̈ʒu���v�Z����*/
	if (player->GetID() == ENEMY) { 
		y = (width*2)-1 - y; 
		x = length-1 - x;
		printf("����Enemy %d %d\n", x, y);
	}


	/*�ړ����J�n*/
	Panel_Field* p = Battle_State::Panel_ALL[y][x];
	player->StandPos = p;
	player->Move(p->GetLocation().x, p->GetLocation().y);
	return this;

	if (p != nullptr && p != player->StandPos) {
		player->StandPos = p;
		float movex = (float)(p->GetLocation().x - player->GetLocation().x);
		float movey = (float)(p->GetLocation().y - player->GetLocation().y);
		float mx = (float)(p->GetLocation().x + (player->GetLocation().x*Code(movex)));
		float my = (float)(p->GetLocation().y + (player->GetLocation().y*Code(movey)));
		player->Move(p->GetLocation().x, p->GetLocation().y);
	}

	return this;
}
