#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"Imageboard/ImageBoard.h"

#define QUES 0.f
#define ADD 1.f
#define SUBT 2.f
#define MULTI 3.f
#define SLASH 4.f
#define EQUAL 5.f
#define SHARP 6.f
#define LAMBDA 7.f
#define GREATER 8.f
#define LESSER 9.f
#define NONSYMBOL 10.f


/*�����̌������������e�N�X�`���ŕ\���ꍇ�A���̃N���X�̋@�\���g�p����B*/
class NumberIMG {
public:
	static NumberIMG* GetInstance();

	void Init();

private:
	static int ImageNumber;
	static unique_ptr<NumberIMG> SingleTon;
	

};


class Number_Symbol:public Field_Object{
public:
	static void Init();

	Number_Symbol(float x, float y, float Width,float Heigth,int digit,float Symbol); /*�������w��,Symbol�����͐����̑O�ɉ�������(+��-��)��t���邩�w�肷��̂Ɏg�p�B*/
	Number_Symbol(float x, float y, float Width, float Heigth, int digit); /*�������w��*/

	void Update(int Number);
	void Update(float Symbol);

	void Draw();

private:
	static int ImageNumber;

	std::vector<unique_ptr<PrimitiveUp>> numberList;
	std::vector<int> digitNumber_mement;
	int digit; /*����*/
	unique_ptr<PrimitiveUp> Symbol;
	float SymbolNum;

	void initialize(float x, float y, float Width, float Heigth, int digit, float Symbol);

};
