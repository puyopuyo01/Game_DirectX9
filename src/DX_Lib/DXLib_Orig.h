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


/*----------------------�T�E���h-------------------------*/

extern LPDIRECTSOUND8 pSound;
extern LPDIRECTSOUNDBUFFER PrBuf;

	/*-----------------------------------���͊֌W-----------------------------------*/
	//extern LPDIRECTINPUT8 dinput;
	//extern LPDIRECTINPUTDEVICE8 Mouse;


	HRESULT DX_INIT(HWND hWnd, bool fullscreen, int width_a, int height);
	void Finalize();

	/*-----------------------------------�}�E�X���W---------------*/
	struct Mouse_VERTEX {
		D3DXVECTOR3 pos;
		DWORD color;
	};

#define M_VERTEX_FVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE)

	/*�Q�[�����J�[�\���̍X�V�A�`����s���N���X�B*/
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
		D3DXMATRIX m_proj;		// �ˉe�s��
		D3DXMATRIX m_view;		// �r���[�C���O�s��
		D3DXVECTOR3 location;
		D3DXVECTOR3 vector;
		D3DXVECTOR3 tilt;

	};


	/*�Q�[���̃I�u�W�F�N�g�̊��N���X �X�V�A�`����s�����߂�DirectX�n�̕ϐ������B*/
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
		/*�w�i���߂�����ݒ���s���֐�*/
		void BackGroundTransparent();
	private:
		D3DXVECTOR3 move_vector;
		D3DXVECTOR3 pos;
		D3DXMATRIX loc;
		D3DXMATRIX rot;
		D3DXMATRIX output;
	};

	/*�摜���Ǘ�����N���X�BSingleTon*/
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

	/*-------------------------�C���[�W�{�[�h�̍쐬�N���X------------------------

	�C���[�W�{�[�h
	�摜�f�[�^�����I�u�W�F�N�g�Ɍp��(2D)
	*/
	struct ImageVertex {
		D3DXVECTOR3 pos;
		DWORD color;
		D3DXVECTOR2 uv;
	};

#define IMG_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


	void Update_Draw(vector<Field_Object*> obj);


