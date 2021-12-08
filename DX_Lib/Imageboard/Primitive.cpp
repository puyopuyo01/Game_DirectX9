#include"ImageBoard.h"

Primitive::Primitive(D3DPRIMITIVETYPE type,float x, float y, float z, float imgWidth, float imgHeight, float r, float g, float b, float a) {
	this->type = type;
	if (pD3DDevice == 0) {
		MessageBox(NULL,
			"ƒfƒoƒCƒX‚ª‚È‚¢(Primitive)", "Ž¸”s", MB_OK);
		return;
	}
	if (type == SQUARE) { VNum = 4; }
	else if (type == SQUARELINE) { VNum = 5; }

	if (FAILED(pD3DDevice->CreateVertexBuffer(VNum * sizeof(ImageVertex),
		D3DUSAGE_WRITEONLY,
		IMG_VERTEX_FVF,
		D3DPOOL_MANAGED, &pVB, NULL))) {
		MessageBox(NULL,
			"Primitive‚ÌŠm•Û‚ÉŽ¸”s2", "Ž¸”s", MB_OK);
		return;
	}

	pVB->Lock(0, 0, (void**)&imgvertex, 0);
	if (type == SQUARE) { 
		Square(imgvertex,x,y,z,imgWidth,imgHeight,r,g,b,a);
		imgvertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
		imgvertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
		imgvertex[2].uv= D3DXVECTOR2(0.0f, 1.0f);
		imgvertex[3].uv= D3DXVECTOR2(1.0f, 1.0f);
	}
	else if(type == SQUARELINE){
		SquareLine(imgvertex,x, y, z,imgWidth,imgHeight, r, g, b, a);
	}
	pVB->Unlock();

	if (type == SQUARE) { VNum = 2; }
	else if (type == SQUARELINE) { VNum = 4; }

	D3DXMatrixIdentity(&pos);
}

Primitive::~Primitive() {
}


void Primitive::Draw(D3DXMATRIX location) {
	if (pVB == 0) {
		MessageBox(NULL,
			"Primitive.Draw()‚ÌŽ¸”s", "Ž¸”s", MB_OK);
		return;
	}
	pD3DDevice->SetTransform(D3DTS_WORLD, &location);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pD3DDevice->SetStreamSource(0, pVB, 0, sizeof(ImageVertex));
	pD3DDevice->SetFVF(IMG_VERTEX_FVF);
	pD3DDevice->DrawPrimitive(this->type, 0, VNum);
}