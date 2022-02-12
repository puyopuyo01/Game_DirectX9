/*#include"./TextureFromFont.h"

FontTexture* FontTexture::SingleTon;


int FontTexture::SaveImage(const wchar_t* ch) {
	ImageIdentifier += 1;
	images.push_back(new LPDIRECT3DTEXTURE9);

	UINT code = (UINT)* ch;
	const int gradFlag = GGO_GRAY4_BITMAP;
	// ŠK’²‚ÌÅ‘å’l
	int grad = 0;
	switch (gradFlag)
	{
	case GGO_GRAY2_BITMAP:
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}

	TEXTMETRIC tm;

	HDC hdc = GetDC(NULL);
	GetTextMetrics(hdc, &tm);
	GLYPHMETRICS gm;
	CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
	DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE *pMono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);



	//MyFileInfo* texture = FileMapping::GetInstance()->GetFile(file_name);
	D3DXCreateTextureFromFileInMemoryEx(
		pD3DDevice,
		FileMapping::GetInstance()->GetPointer(file_name),
		texture->m_FileSize,
		0, 0, 0, 0,
		D3DFMT_A1R5G5B5,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,
		0, NULL, NULL,
		images[ImageIdentifier - 1]
	);


	return ImageIdentifier;

}:*/