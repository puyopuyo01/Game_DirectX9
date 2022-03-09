#include"DXLib_Orig.h"
#include"./FileMapping.h"

/*画像の読み込み管理クラス*/


Images* Images::SingleTon;

void Images::Release() {
	if (Images::SingleTon != nullptr) {
		SingleTon->Init();
		delete SingleTon;
		SingleTon = nullptr;
	}
}

Images* Images::GetInstance() {
	if (Images::SingleTon == nullptr) { Images::SingleTon = new Images(); }
	return SingleTon;
}

Images::Images() {
	Init();
}

void Images::Init() {
	vector<LPDIRECT3DTEXTURE9*>::iterator itr;
	itr = images.begin();
	while (itr != images.end()) {  delete *itr; *itr = nullptr; itr++; }
	images.clear();
	ImageIdentifier = 0;
}

/*画像を登録する。戻り値の値をLoadImageのIdentifierに指定すれば、画像を表示させることができる。*/
int Images::SaveImage(const char* file_name) {
	ImageIdentifier+=1;
	images.push_back(new LPDIRECT3DTEXTURE9);


	MyFileInfo* texture = FileMapping::GetInstance()->GetFile(file_name);
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

}

/*テクスチャを持つオブジェクトは描画後にこの関数を呼び出す。*/
void Images::Reset() {
	pD3DDevice->SetTexture(0,nullptr);
}

/*SaveImage関数で登録した画像を読み込む関数。*/
void Images::LoadImage(int Identifier,int Stage) {
	if (Identifier-1 < 0) { return; }
	pD3DDevice->SetTexture(Stage,*images[Identifier-1]);
}