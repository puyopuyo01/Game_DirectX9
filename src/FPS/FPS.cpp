#include"./FPS.h"

FPS* FPS::SingleTon;

FPS* FPS::GetInstance() {
	if (SingleTon == nullptr) {
		SingleTon = new FPS();
	}
	return SingleTon;
}

float fps=60.f; /*��������Ƃ���fps�����ꂳ��邩��A60fps�Ɖߒ����Ȃ���
				�Q�[���i�s����B�ł��邾��60fps�ێ�����B*/

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
		printf("start���s\n");
	}
}

/*FPS�̌v��*/
void FPS::Measure() { /*56,7���x�ň��肵��(���x�̖��?)*/
	QueryPerformanceFrequency(&Freq);
	LARGE_INTEGER endTime;
	if (!QueryPerformanceCounter(&endTime)) {
		printf("end���s\n");
	}

	/*�t���[���Ԃ̃N���b�N��������g���Ŋ����Čv������B*/
	double result = static_cast<double>(endTime.QuadPart-startTime.QuadPart)/static_cast<double>(Freq.QuadPart);


	if (1./result > 60.) {
		DWORD waittime = static_cast<DWORD>(((1./60.)-result)*1000); 

		timeBeginPeriod(1);
		Sleep(waittime);
		timeEndPeriod(1);
		if (!QueryPerformanceCounter(&endTime)) {
			printf("end���s\n");
		}
		result = static_cast<double>(endTime.QuadPart-startTime.QuadPart)/static_cast<double>(Freq.QuadPart);
		averageFPS->Queue(1./result);

		return;
	}
}

/*FPS�͏�ɕ\��������*/
void FPS::Draw(){
	int imgx = (int)(ScreenLX() + (ScreenWidth() / 4.f));
	int imgy = (int)ScreenUpperY();
	char f[20] = {};
	snprintf(f, 15, "FPS = %lf", averageFPS->Average());
	Text->Draw(150, 250,1500,1500,(const char*)f);
}