#pragma once
#include"DXLib_Orig.h"


/*値をカプセルかするクラス。C#のプロパティのような機能。*/

template<typename T>
class ValueChange {
public:
	virtual void TimeUp() {};
	virtual bool ChangeState();
	virtual void ChangeValue(T* val,T* change);
	virtual int AddValue();
	virtual bool ChangeValue();
};


template<typename T>
bool ValueChange<T>::ChangeState() {
	return true;
};

template<typename T>
void ValueChange<T>::ChangeValue(T* val,T* change) {
	delete val;
	val = nullptr;
	val = change;
	return ;
};

template<typename T>
bool ValueChange<T>::ChangeValue() { return true; };


template<typename T>
/*
	ここで計算するとコンパイラに怒られる。(クラス型を代入するクラスもこの関数が読み込まれるため)
	戻り値がintなのは、float*int のときintがfloatに変換されるため。(精度の高さによる)
*/
int ValueChange<T>::AddValue() {
	return 1;
}


template<typename T>
class NormalValue :public ValueChange<T> {
};



template<typename T>
class NonChangeValue :public ValueChange<T> {
public:
	NonChangeValue() { time = false; }
	bool ChangeState() override
	{
		return time;
	};

	void ChangeValue(T* val, T* change) override
	{
		delete change;
		return;
	};

	int AddValue() override
	{
		return 0;
	};

	bool ChangeValue() override
	{
		return false;
	}

	void TimeUp() override { time = true; }
private:
	bool time;
};


/*
値の変化状態のクラス。
変化の処理はBridgeパターンを使ってValueChangeクラスで行う。
値がオブジェクトか数値かは、Compositeパターンを用いて判定(オブジェクトの場合、Add関数を使えなくする。)
*/

/*このクラスはunique_ptrを使えない(GetVal()がnullになる)*/

template<typename T>
class ValueState{
public:
	T* GetVal();
	void TimeUp() { StateBridge->TimeUp(); };
	ValueState(T* val,ValueChange<T>* bridge);
	~ValueState();
	virtual void ChangeState(ValueChange<T>* bridge);
	virtual void ChangeValue(T* val) {
		if (this->val == val) { return; }
		else StateBridge->ChangeValue(this->val, val);
	};
	virtual void AddValue(T val) {
		MessageBox(NULL,
			"Objectに値を足しています。", "失敗", MB_OK);
	};
	virtual void ChangeValue(T val) {};
protected:
	ValueChange<T>* StateBridge;
	T* val;
};


template<typename T>
ValueState<T>::ValueState(T* val,ValueChange<T>* bridge) {
	this->StateBridge = bridge;
	this->val = val;
}

template<typename T> 
ValueState<T>::~ValueState() {
	delete val;
	val = nullptr;
	delete StateBridge;
	StateBridge = nullptr;
}

template<typename T>
T* ValueState<T>::GetVal() { return this->val; };


template<typename T> 
void ValueState<T>::ChangeState(ValueChange<T>* bridge){
	if (this->StateBridge->ChangeState()) {
		delete this->StateBridge;
		this->StateBridge = bridge;
	}
	else {
		delete bridge;
	}
	return;
};




template<typename T>
class Numerical:public ValueState<T>{
public:
	Numerical(T* val,ValueChange<T>* bridge,T max,T min);
	void AddValue(T val) override;
	void ChangeValue(T val) override;
private:
	T max, min;
};

template<typename T>
Numerical<T>::Numerical(T* val, ValueChange<T>* bridge, T max, T min) :ValueState<T>(val, bridge) {
	this->max = max;
	this->min = min;
}
template<typename T>
/*部分テンプレートでAddしてもいいけどこの方法だとfloatとintで分ける必要がなくなる。*/
void Numerical<T>::AddValue(T val) {
	*(this->val) += val * this->StateBridge->AddValue();
	if (*(this->val) > max) { *(this->val) = max; }
	else if (*(this->val) < min) { *(this->val) = min; }
}

template<typename T>
void Numerical<T>::ChangeValue(T val){
	if (this->StateBridge->ChangeValue()) {
		*(this->val) = val;
		if (*(this->val) > max) { *(this->val) = max; }
		else if (*(this->val) < min) { *(this->val) = min; }
	}
};




template<typename T>
class Object :public ValueState<T>{
public:
	Object(T* val, ValueChange<T>* bridge);
private:
	void Throw(T* val);

};


template<typename T>
Object<T>::Object(T* val, ValueChange<T>* bridge) :ValueState<T>(val, bridge) {

}






template<typename T>
void Object<T>::Throw(T* val) {
	MessageBox(NULL,
		"Objectに値を足しています。", "失敗", MB_OK);
	return;

}




