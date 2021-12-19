#include"DXLib_Orig.h"
#include"KeyBord.h"

HRESULT KeyBord::init() {
	if (Keybord == NULL) { return E_FAIL; }

	ZeroMemory(diks, sizeof(diks));
	if (FAILED(Keybord->GetDeviceState(sizeof(diks), diks))) {
		HRESULT hr;
		hr = Keybord->Acquire();
		while (hr == DIERR_INPUTLOST) { hr = Keybord->Acquire(); }
		if (FAILED(hr)) { return E_FAIL; }
	}

	return S_OK;

}

bool KeyBord::Press(int keycode) {

	if (keycode < 0 || keycode >= KeyMax) {
		return false;
	}

	return diks[keycode] & 0x80;
}


char GetNumber() {
	if (controller->Press(DIK_0)) {
		return '0';
	}
	if (controller->Press(DIK_1)) {
		return '1';
	}
	if (controller->Press(DIK_2)) {
		return '2';
	}
	if (controller->Press(DIK_3)) {
		return '3';
	}
	if (controller->Press(DIK_4)) {
		return '4';
	}
	if (controller->Press(DIK_5)) {
		return '5';
	}
	if (controller->Press(DIK_6)) {
		return '6';
	}
	if (controller->Press(DIK_7)) {
		return '7';
	}
	if (controller->Press(DIK_8)) {
		return '8';
	}
	if (controller->Press(DIK_9)) {
		return '9';
	}
	if (controller->Press(DIK_PERIOD)) {
		return '.';
	}
	

	return '\0';
	
}