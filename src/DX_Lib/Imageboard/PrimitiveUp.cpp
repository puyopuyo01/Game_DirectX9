#include"ImageBoard.h"


/*
PrimitiveUp�Ń|���S�����쐬����B
�|���S���̒�����F���ς��Ƃ���PrimitiveUp�Ń|���S�������B
*/
void PrimitiveUp::init(D3DPRIMITIVETYPE type, float x, float y, float z, float imgWidth, float imgHeight, float r, float g, float b, float a) {
	this->type = type;
	if (pD3DDevice == 0) {
		MessageBox(NULL,
			"�f�o�C�X���Ȃ�(PrimitiveUp)", "���s", MB_OK);
		return;
	}

	if (type == SQUARE) { VNum = 4; }
	else if (type == SQUARELINE) { VNum = 5; }


	if (type == SQUARE) {
		Square(imgvertex, x, y, z, imgWidth, imgHeight, r, g, b, a);
		imgvertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
		imgvertex[1].uv = D3DXVECTOR2(1.f, 0.0f);
		imgvertex[2].uv = D3DXVECTOR2(0.0f, 1.0f);
		imgvertex[3].uv = D3DXVECTOR2(1.0f, 1.0f);
	}
	else if (type == SQUARELINE) {
		SquareLine(imgvertex, x, y, z, imgWidth, imgHeight, r, g, b, a);
	}

	if (type == SQUARE) { VNum = 2; }
	else if (type == SQUARELINE) { VNum = 4; }

	LX = 0; RX = 1; LY = 2, RY = 3;
}

PrimitiveUp::~PrimitiveUp() {
}


/*
UV_X�c���ɉ��������邩.
UV_Y�c�c�ɉ��������邩.
*/
PrimitiveUp::PrimitiveUp(D3DPRIMITIVETYPE type, float x, float y, float z, float imgWidth, float imgHeight, float r, float g, float b, float a) {
	init(type, x, y, z, imgWidth, imgHeight, r, g, b, a);
	UV_X = 1.f;
	UV_Y = 1.f;
}

PrimitiveUp::PrimitiveUp(D3DPRIMITIVETYPE type, float x, float y, float z, float imgWidth, float imgHeight, float r, float g, float b, float a, float UV_X, float UV_Y) {
	init(type, x, y, z, imgWidth, imgHeight, r, g, b, a);
	this->UV_X = (float)UV_X;
	this->UV_Y = (float)UV_Y;
}

/*�摜�𔽓]������֐��B*/
void PrimitiveUp::UVRevers() {
	LX = 1; RX = 0; LY = 3, RY = 2;
	imgvertex[0].uv = D3DXVECTOR2(1.f,0.f);
	imgvertex[1].uv = D3DXVECTOR2(0.f,0.f);
	imgvertex[2].uv = D3DXVECTOR2(1.f,1.f);
	imgvertex[3].uv = D3DXVECTOR2(0.f,1.f);
}

/*�摜�ׂ̍����ꕔ��\��������Ƃ��Ɏg�p����֐�*/
void PrimitiveUp::SetUV(float xLeft, float xRight, float yU, float yL) {
	imgvertex[LX].uv = D3DXVECTOR2(xLeft,yU);
	imgvertex[RX].uv = D3DXVECTOR2(xRight,yU);
	imgvertex[LY].uv = D3DXVECTOR2(xLeft,yL);
	imgvertex[RY].uv = D3DXVECTOR2(xRight,yL);
}


/*�A�j���[�V�����̍Đ��Ɏg�p����֐��B*/
void PrimitiveUp::SetUV(float index_X,float index_Y) {
	imgvertex[LX].uv = D3DXVECTOR2(index_X/ UV_X, index_Y/ UV_Y);
	imgvertex[RX].uv = D3DXVECTOR2((index_X+ 1.f) / UV_X,index_Y /UV_Y);
	imgvertex[LY].uv = D3DXVECTOR2((index_X)/ UV_X,(index_Y+ 1.f) / UV_Y);
	imgvertex[RY].uv = D3DXVECTOR2((index_X+ 1.f) / UV_X,(index_Y+ 1.f) / UV_Y);
}

void PrimitiveUp::VertexPosition(const int index, float x, float y, float z) {
	imgvertex[index].pos = D3DXVECTOR3(x,y,z);

}

void PrimitiveUp::VertexX(const int index, float x) {
	imgvertex[index].pos.x = x;
}

void PrimitiveUp::VertexY(const int index, float y) {
	imgvertex[index].pos.y = y;
}

void PrimitiveUp::VertexColor(const int index, float r, float g, float b, float a) {
	imgvertex[index].color= D3DXCOLOR(r, g, b, a);
}


void PrimitiveUp::Draw(D3DXMATRIX location) {
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);

	pD3DDevice->SetTransform(D3DTS_WORLD, &location);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pD3DDevice->SetFVF(IMG_VERTEX_FVF);
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,VNum,imgvertex,sizeof(ImageVertex));

	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}