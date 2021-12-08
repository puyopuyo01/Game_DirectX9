#pragma once
#include"../DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"

using namespace std;

/*フォント処理クラス*/

class Font {
public:
	Font();
	void Release();
	static Font* GetInstance();
	void Draw(int x,int y,int width,int height,LPCTSTR Text);
private:
	LPCSTR FontName;
	LPD3DXFONT g_pFont;
	DWORD FontNum;

	HANDLE fontHandle;
	static unique_ptr<Font> SingleTon;
};
