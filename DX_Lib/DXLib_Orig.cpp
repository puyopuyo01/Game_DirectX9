#pragma once
#include"DXLib_Orig.h"


LPDIRECT3D9 pD3D;
LPDIRECT3DDEVICE9 pD3DDevice;
D3DPRESENT_PARAMETERS D3DPP;
HINSTANCE hins;
/*-----------------入力関係-----------*/
LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 Keybord;
LPDIRECTINPUTDEVICE8 Mouse;

/*---------------------サウンド系------------------*/
LPDIRECTSOUND8 pSound;
LPDIRECTSOUNDBUFFER PrBuf;


/*
----------------------マウスの状態--------------------
*/
M_Cursor*  cursor;
KeyBord* controller;

HRESULT Get_Keybord(LPDIRECTINPUT8 key, HWND hWnd) {
	if (FAILED(key->CreateDevice(GUID_SysKeyboard, &Keybord, NULL))) {
		return E_FAIL;
	}
	if (Keybord == NULL) {
		MessageBox(NULL,
			"キーボードの確保に失敗", "失敗", MB_OK);
	}

	if (FAILED(Keybord->SetDataFormat(&c_dfDIKeyboard))) {
		MessageBox(NULL,
			"キーボードの確保に失敗(SetDataFormat)", "失敗", MB_OK);
		return E_FAIL;
	}

	if (FAILED(Keybord->SetCooperativeLevel(
		hWnd,
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		MessageBox(NULL,
			"キーボードの確保に失敗(SetCooprativelevel)", "失敗", MB_OK);
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
				"マウスの確保に失敗", "失敗", MB_OK);
		}

		if (FAILED(Mouse->SetDataFormat(&c_dfDIMouse))) {
			MessageBox(NULL,
				"マウスの確保に失敗(SetDataFormat)", "失敗", MB_OK);
			return E_FAIL;
		}
		/*
		---------------------------------------------------------
		アプリ起動中のみデバイス情報を取得(DISCL_FOREGROUND)
		非排他的で他のアプリケーションでもそのまま入力デバイスを取得(DISCL_NONEXCLUSIVE)
		*/
		if (FAILED(Mouse->SetCooperativeLevel(hWnd,
			DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {  /*DISCL_FOREGROUND | DISCL_EXCLUSIVE 本番はこのせってい*/
			MessageBox(NULL,
				"マウスの確保に失敗(SetCooperativeLevel)", "失敗", MB_OK);
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
			"サウンド確保に失敗(SetCooperativeLevel)", "失敗", MB_OK);
		return E_FAIL;
	}

	if (FAILED(pSound->SetCooperativeLevel(
				hWnd,
		DSSCL_PRIORITY))){  /*DISCL_FOREGROUND | DISCL_EXCLUSIVE 本番はこの設定*/
		MessageBox(NULL,
			"SoundSetの確保に失敗(SetCooperativeLevel)", "失敗", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}







	HRESULT DX_INIT(HWND hWnd, bool fullscreen, int width_a, int height) {
		D3DDISPLAYMODE d3ddm;
		// Direct3D9オブジェクトの作成
		if ((pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0) {
			return E_FAIL;	// 取得失敗
		}

		// 現在のディスプレイモードを取得
		if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
			return E_FAIL;
		}

		// デバイスのプレゼンテーションパラメータを初期化
		ZeroMemory(&D3DPP, sizeof(D3DPRESENT_PARAMETERS));
		D3DPP.BackBufferCount = 1;
		if (fullscreen) { // フルスクリーンの場合
			D3DPP.Windowed = fullscreen;			// フルスクリーン表示の指定
			D3DPP.BackBufferWidth = 1000;		// (width)フルスクリーン時の横幅
			D3DPP.BackBufferHeight = 1000;		// (height)フルスクリーン時の縦幅
		}
		else {
			D3DPP.Windowed = TRUE;				// ウインドウ内表示の指定
		}
		D3DPP.BackBufferFormat = d3ddm.Format;			// カラーモードの指定
		D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 
		D3DPP.EnableAutoDepthStencil = TRUE;						// エラー対策
		D3DPP.AutoDepthStencilFormat = D3DFMT_D16;				// エラー対策

		// ディスプレイアダプタを表すためのデバイスを作成
		// 描画と頂点処理をハードウェアで行なう
		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&D3DPP, &pD3DDevice))) {
			// 上記の設定が失敗したら
			// 描画をハードウェアで行い、頂点処理はCPUで行なう
			if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&D3DPP, &pD3DDevice))) {
				// 上記の設定が失敗したら
				// 描画と頂点処理をCPUで行なう
				if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&D3DPP, &pD3DDevice))) {
					// 初期化失敗
					return E_FAIL;
				}
			}

		}


		/*
		-----------------------------
		DirectInput8の確保
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


		/*画像関連の確保*/

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
			cout << "描画失敗";
			return;
		}

		vector<Field_Object*>::iterator itr = obj.begin();
		if (FAILED(pD3DDevice->Clear(0, NULL,
			D3DCLEAR_TARGET |			// バックバッファを指定
			D3DCLEAR_ZBUFFER, 			// 深度バッファ（Zバッファ）を指定
			D3DCOLOR_XRGB(0, 0, 0), 		// クリアする色
			1.0f,
			0))) {
		}
		if (SUCCEEDED(pD3DDevice->BeginScene())) {	//描画開始。バックバッファに書き込み
			while (itr != obj.end()) {
				(*itr)->Draw();
				itr++;
			}
			cursor->Draw();
			pD3DDevice->EndScene();
			if (FAILED(pD3DDevice->Present(0, 0, 0, 0))) {	// 描画結果(バックバッファ)の転送
				pD3DDevice->Reset(&D3DPP);		// デバイス消失から復帰
			}
		}
	}


