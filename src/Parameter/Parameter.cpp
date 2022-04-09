#include"./Parameter.h"

std::unique_ptr<Parameter> Parameter::SingleTon;

Parameter* Parameter::Get(){
	if (SingleTon.get() == nullptr) {
		SingleTon = std::make_unique<Parameter>();
	}
	return SingleTon.get();
}


Parameter::Parameter() {
	/*èâä˙íl*/
	HP = 1000.f;

	SBulletReloadSpeed = 70;
	SBulletNum = 5;
	SBulletSpeed = 10.f;
	SBulletPower = 3;

	MBulletReloadSpeed = 120;
	MBulletNum = 4;
	MBulletSpeed = 30.f;
	MBulletPower = 5;
	
	BBulletReloadSpeed = 180;
	BBulletNum = 2;
	BBulletSpeed = 90.f;
	BBulletPower = 10;
}