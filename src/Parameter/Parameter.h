#pragma once
#include<memory.h>
#include<iostream>


/*
ゲームに必要なパラメータはここで保持し、編集用ウィンドウから値を変更できるようにする。
*/
class Parameter {
public:
	Parameter();
	static Parameter* Get();

	float HP;

	float SBulletSpeed;
	int SBulletPower;
	int SBulletReloadSpeed;
	int SBulletNum;

	float MBulletSpeed;
	int MBulletPower;
	int MBulletReloadSpeed;
	int MBulletNum;

	float BBulletSpeed;
	int BBulletPower;
	int BBulletReloadSpeed;
	int BBulletNum;

private:
	static std::unique_ptr<Parameter> SingleTon;
};