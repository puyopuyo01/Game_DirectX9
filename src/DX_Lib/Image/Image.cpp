#include"DXLib_Orig.h"
#include"./FileMapping.h"

/*�摜�̓ǂݍ��݊Ǘ��N���X*/


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

/*�摜��o�^����B�߂�l�̒l��LoadImage��Identifier�Ɏw�肷��΁A�摜��\�������邱�Ƃ��ł���B*/
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

/*�e�N�X�`�������I�u�W�F�N�g�͕`���ɂ��̊֐����Ăяo���B*/
void Images::Reset() {
	pD3DDevice->SetTexture(0,nullptr);
}

/*SaveImage�֐��œo�^�����摜��ǂݍ��ފ֐��B*/
void Images::LoadImage(int Identifier,int Stage) {
	if (Identifier-1 < 0) { return; }
	pD3DDevice->SetTexture(Stage,*images[Identifier-1]);
}