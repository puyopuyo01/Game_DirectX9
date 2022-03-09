#include"Screen.h"

/*���C���J�����̏����ʒu*/

const float CAMERA_X = 0.f;
const float CAMERA_Y = 0.f;
const float CAMERA_Z = -100.f;

const DWORD CLIENT_WIDTH = 1280;
const DWORD CLIENT_HEIGHT = 1080;

float aspect;
float const r = -CAMERA_Z * std::tan(D3DXToRadian(45.0f / 2.f)); //�J�����̊p�x�AZ������X�N���[�����W���v�Z����

void SetAspect() {
	D3DVIEWPORT9    vp;
	if (pD3DDevice != nullptr) {
		if (FAILED(pD3DDevice->GetViewport(&vp))) {
			MessageBox(NULL,
				"Screen", "���s", MB_OK);
			return;
		}
		aspect = (float)vp.Width / (float)vp.Height;
	}
	if (pD3DDevice == nullptr) {
	}
}

/*��ʍ��[�̍��W*/
float ScreenLX() {
	SetAspect();
	return (CAMERA_X - r * aspect) + 1.f;
	return (CAMERA_X-r)-1.f;
};

/*��ʉE�[�̍��W*/
float ScreenRX() {
	SetAspect();
	return (CAMERA_X + r * aspect) - 1.f;
	return (CAMERA_X+r);
};

/*��ʉ��̍��W*/
float ScreenLowerY(){
	SetAspect();
	return (CAMERA_Y - r) + 1.f;
	return ((CAMERA_Y-r)/ aspect)-1.f;
}

/*��ʏ�̍��W*/
float ScreenUpperY() { 
	SetAspect();
	return CAMERA_Y + r - 1.f;
	return (CAMERA_Y+r)/aspect; 
}

/*���x�������̍��W*/
float ScreenCenterX() {
	return ScreenLX() + (ScreenWidth()/2.f);
}

/*���y�������̍��W*/
float ScreenCenterY() {
	return (ScreenLowerY() + (ScreenHeigth()/2.f));
}

/*��ʂ̉��̒���*/
float ScreenWidth() {
	return (r * aspect) * 2+ 2.f;
}

/*��ʂ̏c�̒���*/
float ScreenHeigth() {
	SetAspect();
	return r * 2 +1.f+2.f;
}


void SetScreenSize(float* x, float* y, float* width, float* height) {
	*x = ScreenCenterX();
	*y = ScreenCenterY();
	*width = ScreenWidth();
	*height = ScreenHeigth();
}
