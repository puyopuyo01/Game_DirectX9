#pragma once
#include"DXLib_Orig.h"


LPDIRECT3D9 pD3D;
LPDIRECT3DDEVICE9 pD3DDevice;
D3DPRESENT_PARAMETERS D3DPP;
HINSTANCE hins;
/*-----------------���͊֌W-----------*/
LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 Keybord;
LPDIRECTINPUTDEVICE8 Mouse;

/*---------------------�T�E���h�n------------------*/
LPDIRECTSOUND8 pSound;
LPDIRECTSOUNDBUFFER PrBuf;


/*
----------------------�}�E�X�̏��--------------------
*/
M_Cursor*  cursor;
KeyBord* controller;

HRESULT Get_Keybord(LPDIRECTINPUT8 key, HWND hWnd) {
	if (FAILED(key->CreateDevice(GUID_SysKeyboard, &Keybord, NULL))) {
		return E_FAIL;
	}
	if (Keybord == NULL) {
		MessageBox(NULL,
			"�L�[�{�[�h�̊m�ۂɎ��s", "���s", MB_OK);
	}

	if (FAILED(Keybord->SetDataFormat(&c_dfDIKeyboard))) {
		MessageBox(NULL,
			"�L�[�{�[�h�̊m�ۂɎ��s(SetDataFormat)", "���s", MB_OK);
		return E_FAIL;
	}

	if (FAILED(Keybord->SetCooperativeLevel(
		hWnd,
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		MessageBox(NULL,
			"�L�[�{�[�h�̊m�ۂɎ��s(SetCooprativelevel)", "���s", MB_OK);
			return E_FAIL;
	}

	Keybord->Acquire();
	controller = new KeyBord();

		return S_OK;
	}

HRESULT Get_Mouse(LPDIRECTINPUT8 mouse, HWND hWnd) {
		if (FAILED(mouse->CreateDevice(GUID_SysMouse, &Mouse, NULL))) {
			return E_FAIL;
		}
		if (Mouse == NULL) {
			MessageBox(NULL,
				"�}�E�X�̊m�ۂɎ��s", "���s", MB_OK);
		}

		if (FAILED(Mouse->SetDataFormat(&c_dfDIMouse))) {
			MessageBox(NULL,
				"�}�E�X�̊m�ۂɎ��s(SetDataFormat)", "���s", MB_OK);
			return E_FAIL;
		}
		/*
		---------------------------------------------------------
		�A�v���N�����̂݃f�o�C�X�����擾(DISCL_FOREGROUND)
		��r���I�ő��̃A�v���P�[�V�����ł����̂܂ܓ��̓f�o�C�X���擾(DISCL_NONEXCLUSIVE)
		*/
		if (FAILED(Mouse->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {  /*DISCL_FOREGROUND | DISCL_EXCLUSIVE �{�Ԃ͂��̂����Ă�*/
			MessageBox(NULL,
				"�}�E�X�̊m�ۂɎ��s(SetCooperativeLevel)", "���s", MB_OK);
			return E_FAIL;
		}

		Mouse->Acquire();
		cursor = new M_Cursor(hWnd, Mouse);
		return S_OK;
	}

HRESULT Sound_Init(HWND hWnd) {
	if (DirectSoundCreate8(
		NULL,
		&pSound,
		NULL)){
		MessageBox(NULL,
			"�T�E���h�m�ۂɎ��s(SetCooperativeLevel)", "���s", MB_OK);
		return E_FAIL;
	}

	if (FAILED(pSound->SetCooperativeLevel(
				hWnd,
		DSSCL_PRIORITY))){  /*DISCL_FOREGROUND | DISCL_EXCLUSIVE �{�Ԃ͂��̐ݒ�*/
		MessageBox(NULL,
			"SoundSet�̊m�ۂɎ��s(SetCooperativeLevel)", "���s", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}







	HRESULT DX_INIT(HWND hWnd, bool fullscreen, int width_a, int height) {
		D3DDISPLAYMODE d3ddm;
		// Direct3D9�I�u�W�F�N�g�̍쐬
		if ((pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0) {
			return E_FAIL;	// �擾���s
		}

		// ���݂̃f�B�X�v���C���[�h���擾
		if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
			return E_FAIL;
		}

		// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��������
		ZeroMemory(&D3DPP, sizeof(D3DPRESENT_PARAMETERS));
		D3DPP.BackBufferCount = 1;
		if (fullscreen) { // �t���X�N���[���̏ꍇ
			D3DPP.Windowed = fullscreen;			// �t���X�N���[���\���̎w��
			D3DPP.BackBufferWidth = 1000;		// (width)�t���X�N���[�����̉���
			D3DPP.BackBufferHeight = 1000;		// (height)�t���X�N���[�����̏c��
		}
		else {
			D3DPP.Windowed = TRUE;				// �E�C���h�E���\���̎w��
		}
		D3DPP.BackBufferFormat = d3ddm.Format;			// �J���[���[�h�̎w��
		D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 
		D3DPP.EnableAutoDepthStencil = TRUE;						// �G���[�΍�
		D3DPP.AutoDepthStencilFormat = D3DFMT_D16;				// �G���[�΍�

		// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
		// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&D3DPP, &pD3DDevice))) {
			// ��L�̐ݒ肪���s������
			// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
			if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&D3DPP, &pD3DDevice))) {
				// ��L�̐ݒ肪���s������
				// �`��ƒ��_������CPU�ōs�Ȃ�
				if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&D3DPP, &pD3DDevice))) {
					// ���������s
					return E_FAIL;
				}
			}

		}


		/*
		-----------------------------
		DirectInput8�̊m��
		-----------------------------
		*/


		if (FAILED(DirectInput8Create((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL))) {
			return E_FAIL;
		}

		if (FAILED(Get_Mouse(dinput, hWnd))) {
			return E_FAIL;
		}

		if (FAILED(Get_Keybord(dinput, hWnd))) {
			return E_FAIL;
		}


		/*�摜�֘A�̊m��*/

		//Images::CreateInstance();

		Sound_Init(hWnd);



		return S_OK;
	}

	void Finalize() {
		pD3D->Release();
		pD3DDevice->Release();
		dinput->Release();
		if (Keybord) { Keybord->Unacquire(); }
		Keybord->Release();
		if (Mouse) { Mouse->Unacquire(); }
		Mouse->Release();
		Images::Release();
		delete cursor;
		delete controller;
		pSound->Release();
	}



	void Update_Draw(vector<Field_Object*> obj) {
		if (pD3DDevice == 0) {
			cout << "�`�掸�s";
			return;
		}

		vector<Field_Object*>::iterator itr = obj.begin();
		if (FAILED(pD3DDevice->Clear(0, NULL,
			D3DCLEAR_TARGET |			// �o�b�N�o�b�t�@���w��
			D3DCLEAR_ZBUFFER, 			// �[�x�o�b�t�@�iZ�o�b�t�@�j���w��
			D3DCOLOR_XRGB(0, 0, 0), 		// �N���A����F
			1.0f,
			0))) {
		}
		if (SUCCEEDED(pD3DDevice->BeginScene())) {	//�`��J�n�B�o�b�N�o�b�t�@�ɏ�������
			while (itr != obj.end()) {
				(*itr)->Draw();
				itr++;
			}
			cursor->Draw();
			pD3DDevice->EndScene();
			if (FAILED(pD3DDevice->Present(0, 0, 0, 0))) {	// �`�挋��(�o�b�N�o�b�t�@)�̓]��
				pD3DDevice->Reset(&D3DPP);		// �f�o�C�X�������畜�A
			}
		}
	}


