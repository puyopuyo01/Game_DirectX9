#include"Screen.h"

/*メインカメラの初期位置*/

const float CAMERA_X = 0.f;
const float CAMERA_Y = 0.f;
const float CAMERA_Z = -100.f;

const DWORD CLIENT_WIDTH = 1280;
const DWORD CLIENT_HEIGHT = 1080;

float aspect;
float const r = -CAMERA_Z * std::tan(D3DXToRadian(45.0f / 2.f)); //カメラの角度、Z軸からスクリーン座標を計算する

void SetAspect() {
	D3DVIEWPORT9    vp;
	if (pD3DDevice != nullptr) {
		if (FAILED(pD3DDevice->GetViewport(&vp))) {
			MessageBox(NULL,
				"Screen", "失敗", MB_OK);
			return;
		}
		aspect = (float)vp.Width / (float)vp.Height;
	}
	if (pD3DDevice == nullptr) {
	}
}

/*画面左端の座標*/
float ScreenLX() {
	SetAspect();
	return (CAMERA_X - r * aspect) + 1.f;
	return (CAMERA_X-r)-1.f;
};

/*画面右端の座標*/
float ScreenRX() {
	SetAspect();
	return (CAMERA_X + r * aspect) - 1.f;
	return (CAMERA_X+r);
};

/*画面下の座標*/
float ScreenLowerY(){
	SetAspect();
	return (CAMERA_Y - r) + 1.f;
	return ((CAMERA_Y-r)/ aspect)-1.f;
}

/*画面上の座標*/
float ScreenUpperY() { 
	SetAspect();
	return CAMERA_Y + r - 1.f;
	return (CAMERA_Y+r)/aspect; 
}

/*画面x軸中央の座標*/
float ScreenCenterX() {
	return ScreenLX() + (ScreenWidth()/2.f);
}

/*画面y軸中央の座標*/
float ScreenCenterY() {
	return (ScreenLowerY() + (ScreenHeigth()/2.f));
}

/*画面の横の長さ*/
float ScreenWidth() {
	return (r * aspect) * 2+ 2.f;
}

/*画面の縦の長さ*/
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
