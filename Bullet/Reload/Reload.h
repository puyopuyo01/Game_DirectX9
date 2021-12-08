#pragma once
#include"Charging/Charging.h"

/*—H—ì‚ÌƒŠƒ[ƒh‚ğÀ‘•*/

class Reload:public Charging{
public:
	Reload(int Remain,int MaxBullet,int count);
	~Reload();

	void AddBullet(int bullet);
	void ChangeMaxBullet(int MaxBullet);
	void AddMaxBullet(int AddBullet);

	void AddCount(int Count);
	void ChangeCount(int Count);

};