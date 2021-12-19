#pragma once
#include"DXLib_Orig.h"

#define ENT 0x1C

#define BACK 0x0E

#define Q 0x10
#define W 0x11
#define E 0x12
#define R 0x13
#define F 0x21
#define G 0x22
#define SHIFT DIK_LSHIFT
#define Space DIK_SPACE
#define ALLKEY 0x10 | 0x11 | 0x12 | 0x13
#define KeyMax 256


class KeyBord {
public:
	KeyBord() {};
	HRESULT init();
	bool Press(int keycode);
private:
	BYTE diks[KeyMax];
};

char GetNumber();