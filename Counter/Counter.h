#pragma once

/*�J�E���g�_�E�������̊��N���X*/
class Counter {
public:
	Counter(int counter);
	bool Update();
	void Reset(int counter);
	void Reset();

	void AddCount(int count);
	void ChangeCounter(int counter);

	//�J�E���g��i�߂�B���ߕ���߂�l�ɂ���B
	int ProcessCounter(int Process);

	int GetRemainCounter();
	int GetMaxCounter();
private:
	int counter;
	int CounterMement;
};