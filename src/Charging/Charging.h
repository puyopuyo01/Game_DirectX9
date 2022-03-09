#pragma once
#include"Counter/Counter.h"


/*チャージ系処理(リロード等)の基底クラス 値(必殺技ポイントや幽霊の残数)もこのクラスで管理*/
class Charging {
public:
	Charging(int Remain,int Max, int count);
	~Charging();

	void Update();
	bool Available(int Consum); /* 消費する分の値(Remain)が引数(Consum)より大きいか確認する関数 */
	bool Consumption(int Consum); /* 消費する分の値（Remain)から引数(Consum)分引く関数。もしRemain < Consumなら引かずにfalseを返す。*/

	int GetRemain();
	int GetMax();

	int GetRemainCounter();
	int GetMaxCounter();

protected:
	int Remain;
	int Max;
	Counter* counter; /*チャージ量を示す。*/
};