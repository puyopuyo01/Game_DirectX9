#pragma once
#include"Charging/Charging.h"

/*自機、敵機が幽霊を撃てる数、撃てる幽霊が+1されるまでのチャージ量を管理する。*/
class Reload:public Charging{
public:
	Reload(int Remain,int MaxBullet,int count);
	~Reload();

	void AddBullet(int bullet);
	void ChangeMaxBullet(int MaxBullet); /*撃てる幽霊の最大値を変更する。*/
	void AddMaxBullet(int AddBullet);/*撃てる幽霊の最大値を加算する。*/

	void AddCount(int Count); /*撃てる幽霊が + 1されるまでのチャージ量を変更する*/
	void ChangeCount(int Count);/*撃てる幽霊が + 1されるまでのチャージ量を加算する*/

};