#pragma once
#include<memory.h>
#include"./../../../DX_Lib/Imageboard/ImageBoard.h"
#include"./../../../Font/Font.h"
#include"Screen.h"
#include"DXLib_Orig.h"
#include"FPS/FPS.h"

#define PLAYERBAR 1
#define ENEMYBAR -1

class Bullet;
namespace UI {

	class UI_Base :public Field_Object {
	public:
		UI_Base(float x, float y, float z);
		void Draw() override;
	protected:
		unique_ptr<ImageBoard> img;
	};

	/*
	Overallを1として考える。
	Remain = Remainの実際の値/Overallの実際の値
	Decrease = 1-(Remain/Overall)
	*/


	class Gauge {		/*ボード二枚で表現する*/
	protected:
		unique_ptr<Primitive> Overall;
		unique_ptr<PrimitiveUp> Remain;
	};

	class BackGround :UI_Base {
	public:
		BackGround(float x, float y);
		void Draw() override;

	private:
		static int TextureNumber;
	};

#define LEFTHP 1
#define RIGHTHP -1

	class HitPointBar :Gauge, public Field_Object {
	public:
		HitPointBar(const int LR, float x, float y);

		void UpdateGauge(float MAXHP, float HP);

		void Update() override;
		void Draw() override;
	private:
		int LorR;

		float OriginX; /*HPボードの左端のスクリーン座標。*/
		float HPwidth;
	};

	class PredominantPointer :public Field_Object {
	public:
		PredominantPointer(float x, float y);
		unique_ptr<Primitive> CurrentPoint;
		void Draw() override;
	};
	class PredominantBar :public Field_Object {
	public:
		PredominantBar(float x, float y);

		unique_ptr<PrimitiveUp> PlayerSide;
		unique_ptr<PrimitiveUp> EnemySide;

		unique_ptr<PredominantPointer> CurrentPoint;

		void Draw() override;
		void UpdateGauge(int gauge);
	private:
		int PredominantTemp;
		float offsetY;
		float offsetX;

		float Height;

		int PredTemp;
	};

	class ChargingBar :public Field_Object,Gauge {
	public:
		ChargingBar(float x, float y,float Width);

		void UpdateGauge(float Rate);
		void Draw() override;

	private:
		float Origin; //原点
		float Width;

	};

	class BulletBuilder:public Field_Object{
	public:
		void Draw() override;
	};


#define SBULLETSTR 0
#define MBULLETSTR 1
#define BBULLETSTR 2
#define LVSTR 3
#define MORALESTR 4

	class TextBoard :public Field_Object {
	public:
		TextBoard(float x, float y);
		void Draw() override;
		void StringUpdate(const int index, string newstr);
		void SetDelayFrame(const int delay);

	private:
		Font* Text;
		string STR[5];
		float interval;
		int delayFrame;
	};


	class ChargingUI:public Field_Object{
	public:
		ChargingUI(float x,float y);
		~ChargingUI();
		void Draw() override;

		void UpdateGauge(float S_Rate,float M_Rate,float B_Rate,float MoraleRate);
		void UpdateBullet(int S, int M, int B,int Morale);

	private:
		Font* Text;

		Bullet* S;
		Bullet* M;
		Bullet* B;

		ChargingBar* SBar;
		ChargingBar* MBar;
		ChargingBar* BBar;
		ChargingBar* Morale;
		char SB[10];
		char MB[10];
		char BB[10];
		char Mo[10];	
	};

	class MoraleUI :public Field_Object {
	public:
		MoraleUI(float x, float y,int MoraleNum);
		~MoraleUI();

		void Draw() override;

		void UpdateGauge(float MoraleRate);

	private:
		vector<Primitive*> Frame;
		ChargingBar* MoraleBar;
	};



	/*UIを管理するクラス*/
	/*パラメータが不必要なUIはCreateUI関数で作成*/
	class UIMNG {
	public:
		UIMNG();
		void CreateUI();
		void SetMorale(int MaxMorale);


		void Release();

		static UIMNG* GetInstance();

		unique_ptr<BackGround> backGround;
		unique_ptr<TextBoard> textBoard;
		unique_ptr<HitPointBar> PlayerHP;
		unique_ptr<HitPointBar> EnemyHP;


		ChargingUI* Charging;
		MoraleUI* Morale;


		unique_ptr<PredominantBar> Predominant;

	private:
		static unique_ptr<UIMNG> SingleTon;
	};
};