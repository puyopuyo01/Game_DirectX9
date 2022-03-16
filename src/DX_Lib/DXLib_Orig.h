#pragma once
#define _WINSOCKAPI_ 
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include<vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <d3d9types.h>
#include<memory>
#include"../Font/Font.h"
#include"./Device/KeyBord/KeyBord.h"
#include<dsound.h>

using namespace std;

class Font;

#define MOUSELEFT 0
#define MOUSERIGHT 1
#define MOUSECENTER 2


extern LPDIRECT3D9 pD3D;
extern LPDIRECT3DDEVICE9 pD3DDevice;
extern D3DPRESENT_PARAMETERS D3DPP;

extern LPDIRECTINPUTDEVICE8 Mouse;
extern LPDIRECTINPUTDEVICE8 Keybord;


/*----------------------サウンド-------------------------*/

extern LPDIRECTSOUND8 pSound;
extern LPDIRECTSOUNDBUFFER PrBuf;

	/*-----------------------------------入力関係-----------------------------------*/
	//extern LPDIRECTINPUT8 dinput;
	//extern LPDIRECTINPUTDEVICE8 Mouse;


	HRESULT DX_INIT(HWND hWnd, bool fullscreen, int width_a, int height);
	void Finalize();

	/*-----------------------------------マウス座標---------------*/
	struct Mouse_VERTEX {
		D3DXVECTOR3 pos;
		DWORD color;
	};

#define M_VERTEX_FVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE)

	/*ゲーム内カーソルの更新、描画を行うクラス。*/
	typedef struct m_loc {
	public:
		m_loc(HWND hWnd, LPDIRECTINPUTDEVICE8 mouse);
		void notification(HWND hWnd, float speed);
		void Update();
		void Draw();
		FLOAT x, y;
		bool ClickLeft();
	private:
		LPDIRECT3DVERTEXBUFFER9	pVB;
		Mouse_VERTEX* vertex;
		LPDIRECTINPUTDEVICE8 mouse;
		D3DXMATRIX pos;

		float aspect;

		RECT field;
		float cursor_width;
		float cursor_height;
		float move_speed;
		LPDIRECT3DTEXTURE9 image;
		DIMOUSESTATE m_state;
	}M_Cursor;

	extern M_Cursor* cursor;
	extern KeyBord* controller;

	class Camera {
	public:
		Camera();
		~Camera();
		void Update();

	private:
		D3DXMATRIX m_proj;		// 射影行列
		D3DXMATRIX m_view;		// ビューイング行列
		D3DXVECTOR3 location;
		D3DXVECTOR3 vector;
		D3DXVECTOR3 tilt;

	};


	/*ゲームのオブジェクトの基底クラス 更新、描画を行うためのDirectX系の変数を持つ。*/
	class Field_Object {
	public:
		Field_Object(float x, float y, float depth);
		virtual ~Field_Object();
	public:
		virtual void Update();
		virtual void Draw();
		void Move(float x, float y);
		void Rot(float a);
		D3DXMATRIX GetMatrix();
		D3DXVECTOR3 GetLocation();
		/*背景透過させる設定を行う関数*/
		void BackGroundTransparent();
	private:
		D3DXVECTOR3 move_vector;
		D3DXVECTOR3 pos;
		D3DXMATRIX loc;
		D3DXMATRIX rot;
		D3DXMATRIX output;
	};

	/*画像を管理するクラス。SingleTon*/
	class Images {
	public:
		static Images* GetInstance();
		Images();
		static void Release();
		void Init();
		int SaveImage(const char* file_name);
		void LoadImage(int Identifier,int Stage);
		void Reset();
	private:
		static Images* SingleTon;
		int ImageIdentifier;
		vector<LPDIRECT3DTEXTURE9*> images;
	};

	/*-------------------------イメージボードの作成クラス------------------------

	イメージボード
	画像データを持つオブジェクトに継承(2D)
	*/
	struct ImageVertex {
		D3DXVECTOR3 pos;
		DWORD color;
		D3DXVECTOR2 uv;
	};

#define IMG_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


	void Update_Draw(vector<Field_Object*> obj);


