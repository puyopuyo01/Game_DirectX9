#pragma once
#include"DXLib_Orig.h"


/*�l���J�v�Z��������N���X�BC#�̃v���p�e�B�̂悤�ȋ@�\�B*/

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
	�����Ōv�Z����ƃR���p�C���ɓ{����B(�N���X�^��������N���X�����̊֐����ǂݍ��܂�邽��)
	�߂�l��int�Ȃ̂́Afloat*int �̂Ƃ�int��float�ɕϊ�����邽�߁B(���x�̍����ɂ��)
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
�l�̕ω���Ԃ̃N���X�B
�ω��̏�����Bridge�p�^�[�����g����ValueChange�N���X�ōs���B
�l���I�u�W�F�N�g�����l���́AComposite�p�^�[����p���Ĕ���(�I�u�W�F�N�g�̏ꍇ�AAdd�֐����g���Ȃ�����B)
*/

/*���̃N���X��unique_ptr���g���Ȃ�(GetVal()��null�ɂȂ�)*/

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
			"Object�ɒl�𑫂��Ă��܂��B", "���s", MB_OK);
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
/*�����e���v���[�g��Add���Ă��������ǂ��̕��@����float��int�ŕ�����K�v���Ȃ��Ȃ�B*/
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
		"Object�ɒl�𑫂��Ă��܂��B", "���s", MB_OK);
	return;

}




