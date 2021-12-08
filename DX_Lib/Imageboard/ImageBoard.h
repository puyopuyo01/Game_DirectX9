#pragma once
#include"DXLib_Orig.h"

#define SQUARE D3DPT_TRIANGLESTRIP
#define SQUARELINE D3DPT_LINESTRIP


/*
	�|���S���쐬�N���X�B�Q�[�������ł킴�킴�|���S�����쐬����K�v���Ȃ��Ȃ�B
	�摜�f�[�^�����I�u�W�F�N�g�Ɍp��(2D)
*/

class ImageBoard {
public:
	ImageBoard();
	virtual ~ImageBoard();
	virtual void Draw(D3DXMATRIX location);
	void Square(ImageVertex imgvertex[],float x, float y, float z,float imgWidth, float imgHeight, float r, float g, float b,float a);
	void SquareLine(ImageVertex* imgvertex,float x,float y,float z,float imgWidth, float imgHeight,float r, float g, float b,float a);
protected:
	D3DPRIMITIVETYPE type;
	LPDIRECT3DVERTEXBUFFER9	pVB;
	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIX pos;
	int VNum;

};

class Primitive :public  ImageBoard {
public:
	Primitive(D3DPRIMITIVETYPE type, float x, float y, float z,float imgWidth, float imgHeight, float r, float g, float b, float a);
	~Primitive();
	void Draw(D3DXMATRIX location) override;
private:
	ImageVertex* imgvertex;
};

/*Square�̂Ƃ��̂ݎg����*/
#define UPPERLEFT 0
#define LOWERLEFT 2
#define UPPERRIGHT 1
#define LOWERRIGHT 3

class PrimitiveUp :public ImageBoard {
public:
	PrimitiveUp(D3DPRIMITIVETYPE type, float x, float y, float z,float imgWidth, float imgHeight, float r, float g, float b, float a);
	void Draw(D3DXMATRIX location) override;
	void VertexPosition(const int index, float x, float y, float z);
	void VertexX(const int index, float x);
	void VertexY(const int index, float y);
	void VertexColor(const int index, float r, float g,float b,float a);

private:
	ImageVertex imgvertex[4];
};
