#include"./FPS.h"

FPS* FPS::SingleTon;

FPS* FPS::GetInstance() {
	if (SingleTon == nullptr) {
		SingleTon = new FPS();
	}
	return SingleTon;
}

float fps=60.f; /*同期するときにfpsも統一されるから、60fpsと過程しながら
				ゲーム進行する。できるだけ60fps維持する。*/

bool Available;

void FPS::InitFPS() {
	if (!QueryPerformanceFrequency(&Freq)) {
		Available = false;
		return;
	}
	averageFPS = new Array(50);
	averageFPS->Queue(60.);
	Available = true;
	Text = Font::GetInstance();
}

void FPS::ReleaseFPS() {
	delete averageFPS;
	delete SingleTon;
}

void FPS::SMesure() {
	if (!QueryPerformanceCounter(&startTime)) {
		printf("start失敗\n");
	}
}

/*FPSの計測*/
void FPS::Measure() { /*56,7程度で安定した(精度の問題?)*/
	QueryPerformanceFrequency(&Freq);
	LARGE_INTEGER endTime;
	if (!QueryPerformanceCounter(&endTime)) {
		printf("end失敗\n");
	}

	/*フレーム間のクロック数から周波数で割って計測する。*/
	double result = static_cast<double>(endTime.QuadPart-startTime.QuadPart)/static_cast<double>(Freq.QuadPart);


	if (1./result > 60.) {
		DWORD waittime = static_cast<DWORD>(((1./60.)-result)*1000); 

		timeBeginPeriod(1);
		Sleep(waittime);
		timeEndPeriod(1);
		if (!QueryPerformanceCounter(&endTime)) {
			printf("end失敗\n");
		}
		result = static_cast<double>(endTime.QuadPart-startTime.QuadPart)/static_cast<double>(Freq.QuadPart);
		averageFPS->Queue(1./result);

		return;
	}
}

/*FPSは常に表示させる*/
void FPS::Draw(){
	int imgx = (int)(ScreenLX() + (ScreenWidth() / 4.f));
	int imgy = (int)ScreenUpperY();
	char f[20] = {};
	snprintf(f, 15, "FPS = %lf", averageFPS->Average());
	Text->Draw(150, 250,1500,1500,(const char*)f);
}