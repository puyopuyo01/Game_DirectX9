#include"ImageBoard.h"


ImageBoard::ImageBoard() {
}

ImageBoard::~ImageBoard(){
	
}

void ImageBoard::Draw(D3DXMATRIX location) {
}


void ImageBoard::Square(ImageVertex imgvertex[],float x, float y, float z, float imgWidth, float imgHeight,float r, float g, float b,float a) {
	/*É|ÉäÉSÉìÇçÏê¨*/
	imgvertex[0].pos = D3DXVECTOR3(x - (imgWidth / 2.f), y + (imgHeight / 2.f), 0.f);
	imgvertex[1].pos = D3DXVECTOR3(x + (imgWidth / 2.f), y + (imgHeight / 2.f), 0.f);
	imgvertex[2].pos = D3DXVECTOR3(x - (imgWidth / 2.f), y - (imgHeight / 2.f), 0.f);
	imgvertex[3].pos = D3DXVECTOR3(x + (imgWidth / 2.f), y - (imgHeight / 2.f), 0.f);
	imgvertex[0].color = imgvertex[1].color = imgvertex[2].color = imgvertex[3].color = D3DXCOLOR(r, g, b,a);
}


void ImageBoard::SquareLine(ImageVertex* imgvertex,float x, float y, float z,float imgWidth, float imgHeight, float r, float g, float b, float a) {
	imgvertex[0].pos = D3DXVECTOR3(x - (imgWidth / 2), y + (imgHeight / 2), 0.f);
	imgvertex[1].pos = D3DXVECTOR3(x + (imgWidth / 2), y + (imgHeight / 2), 0.f);
	imgvertex[2].pos = D3DXVECTOR3(x + (imgWidth / 2), y - (imgHeight / 2), 0.f);
	imgvertex[3].pos = D3DXVECTOR3(x - (imgWidth / 2), y - (imgHeight / 2), 0.f);
	imgvertex[4].pos = imgvertex[0].pos;
	imgvertex[0].color = imgvertex[1].color = imgvertex[2].color = imgvertex[3].color = imgvertex[4].color = D3DXCOLOR(r, g, b, a);
}