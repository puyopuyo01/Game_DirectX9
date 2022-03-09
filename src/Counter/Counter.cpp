#include"Counter/Counter.h"

Counter::Counter(int counter) {
	this->counter = counter;
	this->CounterMement = counter;
}


/*カウントをリセットする。Reset関数は引数を指定しない場合、CounterMemを使用。*/
void Counter::Reset(int counter) {
	Counter::Counter(counter);
}

void Counter::Reset() {
	this->counter = this->CounterMement;
}

/*カウント量を加算する関数。*/
void Counter::AddCount(int count) {
	this->CounterMement += count;
	int Count = this->counter + count;
	if (Count > this->CounterMement) { this->counter = this->CounterMement; }
	else { this->counter = Count; }
}

/*カウント量を変更する関数。*/
void Counter::ChangeCounter(int counter) {
	this->CounterMement = counter;
	if (this->counter > counter) { this->counter = counter; }
}

/*残りのカウント量を返す。*/
int Counter::GetRemainCounter(){
	return CounterMement - counter;
}

/*カウント量を返す。*/
int Counter::GetMaxCounter() {
	return CounterMement;
}


/*カウントを引数分進める。*/
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

/*カウントを1進める。*/
bool Counter::Update() {
	if (this->counter == 0) {
		return true;
	}
	this->counter--;
	return false;
}