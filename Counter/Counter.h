#pragma once

/*カウントダウン処理の基底クラス*/
class Counter {
public:
	Counter(int counter);
	bool Update();
	void Reset(int counter);
	void Reset();

	void AddCount(int count);
	void ChangeCounter(int counter);

	//カウントを進める。超過分を戻り値にする。
	int ProcessCounter(int Process);

	int GetRemainCounter();
	int GetMaxCounter();
private:
	int counter;
	int CounterMement;
};