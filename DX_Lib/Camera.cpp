#include"DXLib_Orig.h"
#include"Screen.h"

Camera::Camera() {
	tilt = D3DXVECTOR3(0.f,1.f,0.f);
	vector = D3DXVECTOR3(0.f, 0.f, 0.f);
	location = D3DXVECTOR3(CAMERA_X,CAMERA_Y,CAMERA_Z);
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixLookAtLH(&m_view, &location,&vector,&tilt);
	Update();
}

Camera::~Camera() {
}

void Camera::Update() {
	D3DVIEWPORT9    vp;
	if (FAILED(pD3DDevice->GetViewport(&vp))) {
		return;
	}
	float aspect;
	aspect = (float)vp.Width / (float)vp.Height;
	// ŽË‰es—ñ‚Ì‰Šú‰»
	D3DXMatrixIdentity(&m_proj);
	D3DXMatrixPerspectiveFovLH(&m_proj, D3DXToRadian(45.0f), aspect, 0.f, 1000.0f);
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_proj);
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_view);
}