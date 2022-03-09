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


/*複数の桁を持つ数字をテクスチャで表す場合、このクラスの機能を使用する。*/
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

	Number_Symbol(float x, float y, float Width,float Heigth,int digit,float Symbol); /*桁数を指定,Symbol引数は数字の前に何か符号(+や-等)を付けるか指定するのに使用。*/
	Number_Symbol(float x, float y, float Width, float Heigth, int digit); /*桁数を指定*/

	void Update(int Number);
	void Update(float Symbol);

	void Draw();

private:
	static int ImageNumber;

	std::vector<unique_ptr<PrimitiveUp>> numberList;
	std::vector<int> digitNumber_mement;
	int digit; /*桁数*/
	unique_ptr<PrimitiveUp> Symbol;
	float SymbolNum;

	void initialize(float x, float y, float Width, float Heigth, int digit, float Symbol);

};
