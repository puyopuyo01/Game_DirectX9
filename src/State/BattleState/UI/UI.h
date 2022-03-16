#pragma once
#include<memory.h>
#include"./../../../DX_Lib/Imageboard/ImageBoard.h"
#include"./../../../Font/Font.h"
#include"Screen.h"
#include"DXLib_Orig.h"
#include"FPS/FPS.h"
#include"SingleTonImage/NumberIMG.h"

#define PLAYERBAR 1
#define ENEMYBAR -1

class Bullet;
class Counter;
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
		unique_ptr<Primitive> Cover;
		unique_ptr<Primitive> Overall;
		unique_ptr<PrimitiveUp> Remain;
	};

	class BackGround :UI_Base {
	public:
		BackGround(float x, float y);
		void Draw() override;
		static void LoadIMG();

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

		static void LoadIMG();
	private:
		int LorR;

		float OriginX; /*HPボードの左端のスクリーン座標。*/
		float HPwidth;
		
		static int GaugeTexture;
		static int GaugeCoverTexture;
		static int GaugeBaseTexture;
	};

	class PredominantPointer :public Field_Object {
	public:
		PredominantPointer(float x, float y);
		unique_ptr<Primitive> CurrentPoint;
		void Draw() override;
	};

	class PredominantBar :public Field_Object {
	public:
		PredominantBar(float x, float y,int Max);

		unique_ptr<PrimitiveUp> PlayerSide;
		unique_ptr<PrimitiveUp> EnemySide;

		unique_ptr <Primitive> lv1;
		unique_ptr <Primitive> lv2;
		unique_ptr <Primitive> lv3;

		unique_ptr <Number_Symbol> lv1Num;
		unique_ptr <Number_Symbol> lv2Num;
		unique_ptr <Number_Symbol> lv3Num;

		unique_ptr<PredominantPointer> CurrentPoint;

		void Draw() override;
		void UpdateGauge(int gauge,int increase);
	private:
		int PredominantTemp;
		float offsetY;
		float offsetX;

		float Height;

		int PredTemp;

		int Max;
	};

	class ChargingBar :public Field_Object,Gauge {
	public:
		ChargingBar(float x, float y,float Width);
		ChargingBar(float x, float y, float Width, float r, float g, float b,float a,
					float fr,float fg,float fb,float fa);

		void UpdateGauge(float Rate);
		void Draw() override;

	private:
		float Origin; //原点
		float Width;

		void init(float x, float y, float Width,float r,float g,float b, float a,float fr, float fg, float fb,float ra);

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

		Number_Symbol* SNumber;
		Number_Symbol* MNumber;
		Number_Symbol* BNumber;
	};

	class MoraleUI :public Field_Object {
	public:
		MoraleUI(float x, float y,int MoraleNum);
		~MoraleUI();

		void Draw() override;

		void UpdateGauge(float MoraleRate,int Mol);

	private:
		vector<Primitive*> Frame;
		ChargingBar* MoraleBar;

		Number_Symbol* Number;
	};



	class CharacterPanelUI :public Field_Object {
		/*カットイン用のパネル。
		右は必要な情報を表示しているので左から入り左から出る。*/
	public:
		CharacterPanelUI(float x, float y, int TextureNumber);
		~CharacterPanelUI();

		void Draw() override;
		void Update() override;

		void Dmg(int texture);

		float Width;
		float Height;

		int TextureNumber;

	private:
		Counter* counter;
		bool DMG;

		unique_ptr<ImageBoard> img;
		int TextureMem;
	};



	/*UIを管理するクラス*/
	/*パラメータが不必要なUIはCreateUI関数で作成*/
	class UIMNG {
	public:
		UIMNG();

		static void SaveImage();

		void CreateUI(int PredMax);
		void SetMorale(int MaxMorale);
		void CreatePanel(int Hero, int Enemy);


		void Release();

		static UIMNG* GetInstance();

		unique_ptr<BackGround> backGround;
		unique_ptr<TextBoard> textBoard;
		unique_ptr<HitPointBar> PlayerHP;
		unique_ptr<HitPointBar> EnemyHP;

		/*unique_ptrが使えない(C2280発生)*/
		ChargingUI* Charging;
		MoraleUI* Morale;

		/*unique_ptrが使えない(C2280発生)*/
		CharacterPanelUI* PlayerPanel;
		CharacterPanelUI* EnemyPanel;



		unique_ptr<PredominantBar> Predominant;

	private:
		static unique_ptr<UIMNG> SingleTon;
	};
};