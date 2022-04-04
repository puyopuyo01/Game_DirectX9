#include"DXLib_Orig.h"
#include"Screen.h"

void m_loc::notification(HWND hWnd,float speed) {
	D3DVIEWPORT9    vp;
	if (FAILED(pD3DDevice->GetViewport(&vp))) {
		MessageBox(NULL,
			"カーソルの確保に失敗", "失敗", MB_OK);
		return;
	}
	field.right = (LONG)vp.Width;
	field.top = (LONG)vp.Height;
	aspect = (float)vp.Width / (float)vp.Height;
	x = 0;
	y = 0;	
	move_speed = speed;
}

m_loc::m_loc(HWND hWnd, LPDIRECTINPUTDEVICE8 mouse) {
	if (pD3DDevice == 0) {
			MessageBox(NULL,
				"デバイスがない(Mouse)", "失敗", MB_OK);
		return;
	}

	if (FAILED(pD3DDevice->CreateVertexBuffer(4 * sizeof(Mouse_VERTEX),
		D3DUSAGE_WRITEONLY,
		M_VERTEX_FVF,
		D3DPOOL_MANAGED, &pVB, NULL))) {
		MessageBox(NULL,
			"カーソルの確保に失敗2", "失敗", MB_OK);
		return;
		}

	this->mouse = mouse;

	pVB->Lock(0, 0, (void**)&vertex, 0);
	vertex[0].pos= D3DXVECTOR3(0.f, 0.f, 0.f);
	vertex[1].pos= D3DXVECTOR3(1.f, 0.f, 0.f);
	vertex[2].pos = D3DXVECTOR3(0.f, 1.f, 0.f);
	vertex[3].pos = D3DXVECTOR3(1.f, 1.f, 0.f);
	vertex[0].color = vertex[1].color = vertex[2].color = vertex[3].color = D3DXCOLOR(1.f , 1.f , 1.f , 1.f);
	pVB->Unlock();

	D3DXMatrixIdentity(&pos);
	cursor_width = cursor_height = 2.f;
	field.left = 0;
	field.bottom = 0;
	move_speed = 0.1f;
	notification(hWnd,0.1f);

}

/*クリックしたか判定する処理*/
bool m_loc::ClickLeft() {
	if (mouse == nullptr) { return false; }
	return m_state.rgbButtons[MOUSELEFT] & 0x80;
}

void m_loc::Update() {
	if (mouse == NULL) {
		MessageBox(NULL,
			"デバイスがない(Mouse)Update", "失敗", MB_OK);
		return;
	}
	ZeroMemory(&m_state, sizeof(DIMOUSESTATE));
	if (FAILED(mouse->GetDeviceState(
		sizeof(DIMOUSESTATE), &m_state))) {
		//MessageBox(NULL,"デバイスUpdate", "失敗", MB_OK);
	}

	if (FAILED(mouse->Acquire())) {
		//MessageBox(NULL,"マウスが取得不能", "失敗", MB_OK);
		return;
	}

	x +=(float)m_state.lX*move_speed;
	y -=(float)m_state.lY*move_speed;

	float r= -CAMERA_Z*std::tan(D3DXToRadian(45.0f / 2.f));

	/*画面外から出れないようにする*/
	if (x > ScreenRX()) { x = ScreenRX(); }
	else if (x < ScreenLX()) { x = ScreenLX(); }
	if (y > ScreenUpperY()) { y = ScreenUpperY(); }
	else if (y < ScreenLowerY()) { y = ScreenLowerY(); }
	D3DXMatrixTranslation(&pos, x, y, 0.f);


}

void m_loc::Draw() {
	pD3DDevice->SetTransform(D3DTS_WORLD, &pos);
	pD3DDevice->SetStreamSource(0, pVB, 0, sizeof(Mouse_VERTEX));
	pD3DDevice->SetFVF(M_VERTEX_FVF);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}