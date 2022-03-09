#include"./Font.h"



unique_ptr<Font> Font::SingleTon;

Font* Font::GetInstance() {
	if (Font::SingleTon.get() == nullptr) {
		Font::SingleTon = make_unique<Font>(Font());
	}
	return SingleTon.get();
}

/*フォントの解放*/
void Font::Release() {
	if(RemoveFontMemResourceEx(fontHandle)){}
	else{	
		MessageBox(NULL,
			"フォント解放失敗", "失敗", MB_OK);
	}
	g_pFont->Release();
	SingleTon.reset();
}

Font::Font() {
	FontName = "KleeOne-Regular.ttf";
	FontNum = 0;
	MyFileInfo* font = FileMapping::GetInstance()->GetFile(FontName);
	fontHandle = AddFontMemResourceEx(
		(LPVOID)FileMapping::GetInstance()->GetPointer(FontName),
		font->m_FileSize,
		0,
		&FontNum
		);

	if(fontHandle){}
	else{
		MessageBox(NULL,
			"フォント読みこみ失敗", "失敗", MB_OK);
		return;
	}
	D3DXCreateFont(
		pD3DDevice,
		20,
		10,
		FW_REGULAR,
		NULL,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("KleeOne-Regular"),
		&g_pFont
	);
	

}


void Font::Draw(int x,int y,int width,int height,LPCTSTR Text){
	RECT rc = {
		x,		// 左上のx座標
		y,		// 左上のy座標
		x+width,		// 右下のx座標
		y+height
	};


	g_pFont->DrawText(
		NULL,
		Text,
		-1,	/*-1で全文字を表示*/
		&rc,
		DT_CENTER,
		D3DCOLOR_ARGB(255, 0, 255, 255)
	);

	return;

}