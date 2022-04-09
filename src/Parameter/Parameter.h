#pragma once
#include<memory.h>
#include<iostream>


/*
�Q�[���ɕK�v�ȃp�����[�^�͂����ŕێ����A�ҏW�p�E�B���h�E����l��ύX�ł���悤�ɂ���B
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