#include"./NumberIMG.h"


unique_ptr<NumberIMG> NumberIMG::SingleTon;
int NumberIMG::ImageNumber;

int Number_Symbol::ImageNumber;


void NumberIMG::Init(){
	ImageNumber = Images::GetInstance()->SaveImage("Message.png");
}

NumberIMG* NumberIMG::GetInstance() {
	if (NumberIMG::SingleTon.get() == nullptr) {
		SingleTon = std::make_unique<NumberIMG>(NumberIMG());
	}
	return NumberIMG::SingleTon.get();
}




void Number_Symbol::Init() {
	ImageNumber = Images::GetInstance()->SaveImage("Message.png");
}


void Number_Symbol::initialize(float x, float y, float Width, float Heigth, int digit, float Symbol){
	this->digit = digit;
	float displacement = -(float)digit / 2.f;

	SymbolNum = Symbol;

	if (0.f <= SymbolNum && SymbolNum < NONSYMBOL) {	/*引数を定数指定しているか?*/
		this->Symbol = make_unique<PrimitiveUp>(PrimitiveUp(SQUARE, x + displacement, y, 0.f,
			Width, Heigth/2.f,
			1.f, 1.f, 1.f, 1.f
			, 10.f, 2.f));
		displacement += Width;
		this->Symbol.get()->SetUV(Symbol, 1);

	}
	for (int i = 0; i < digit; i++, displacement += Width) {
		numberList.push_back(make_unique<PrimitiveUp>(PrimitiveUp(SQUARE, x + displacement, y, 0.f,
			Width, Heigth,
			1.f, 1.f, 1.f, 1.f
			, 10.f, 2.f)));
	}
}

Number_Symbol::Number_Symbol(float x, float y, float Width, float Heigth, int digit) :Field_Object(x, y, 0.f) {
	initialize(x, y, Width, Heigth, digit,NONSYMBOL);

}


Number_Symbol::Number_Symbol(float x, float y, float Width, float Heigth, int digit,float Symbol):Field_Object(x,y,0.f){
	initialize(x, y, Width, Heigth, digit, Symbol);

}

void Number_Symbol::Update(float Symbol) {
	if (0.f <= SymbolNum && SymbolNum < NONSYMBOL) {
		numberList[0].get()->SetUV(Symbol, 1);
	}
}

void Number_Symbol::Update(int Number) {
	digitNumber_mement.clear();
	int digits = digit;
	Number %= (int)pow(10, digits+1);
	/*各桁の値をリストに入れていく*/
	while (digits != 0) {
		int notice_digit = (int)pow(10,(digits - 1));
		int digitNumber = 0;
		while (Number - notice_digit >= 0) {
			Number -= notice_digit;
			digitNumber++;
		}
		digitNumber_mement.push_back(digitNumber);
		digits--;
	}

	/*各桁の値の画像をUV表示で取り出していく*/
	for (int i = 0; i < (int)numberList.size(); i++) {
		numberList[i].get()->SetUV((float)digitNumber_mement[i],0.f);
	}

}


void Number_Symbol::Draw() {
	BackGroundTransparent();
	Images::GetInstance()->LoadImage(ImageNumber, 0);
	if (0.f <= SymbolNum && SymbolNum < NONSYMBOL) {
		Symbol->Draw(this->GetMatrix());
	}
	for (int i = 0; i < (int)numberList.size(); i++) {
		numberList[i].get()->Draw(this->GetMatrix());
	}
	Images::GetInstance()->Reset();
}


