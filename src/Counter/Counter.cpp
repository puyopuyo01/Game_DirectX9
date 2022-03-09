#include"Counter/Counter.h"

Counter::Counter(int counter) {
	this->counter = counter;
	this->CounterMement = counter;
}


/*�J�E���g�����Z�b�g����BReset�֐��͈������w�肵�Ȃ��ꍇ�ACounterMem���g�p�B*/
void Counter::Reset(int counter) {
	Counter::Counter(counter);
}

void Counter::Reset() {
	this->counter = this->CounterMement;
}

/*�J�E���g�ʂ����Z����֐��B*/
void Counter::AddCount(int count) {
	this->CounterMement += count;
	int Count = this->counter + count;
	if (Count > this->CounterMement) { this->counter = this->CounterMement; }
	else { this->counter = Count; }
}

/*�J�E���g�ʂ�ύX����֐��B*/
void Counter::ChangeCounter(int counter) {
	this->CounterMement = counter;
	if (this->counter > counter) { this->counter = counter; }
}

/*�c��̃J�E���g�ʂ�Ԃ��B*/
int Counter::GetRemainCounter(){
	return CounterMement - counter;
}

/*�J�E���g�ʂ�Ԃ��B*/
int Counter::GetMaxCounter() {
	return CounterMement;
}


/*�J�E���g���������i�߂�B*/
int Counter::ProcessCounter(int Counter) {
	int Remain = counter - Counter;
	if (Remain > 0) {
		counter -= Counter;
		return 0;
	}
	else if (Remain <= 0) {
		int res = Counter - counter;
		counter = 0;
		return res;
	}
}

/*�J�E���g��1�i�߂�B*/
bool Counter::Update() {
	if (this->counter == 0) {
		return true;
	}
	this->counter--;
	return false;
}