#include <iostream>
void tp() {
		short int nI1 = 1;
		int iI2 = 2;
		long long lI3 = 3;
		char cH = 'F';	
		bool bF = false;
		float Pi = 3.14;
		double dPi = 3.14159;
		std::cout << "nI1 = " << nI1 << std::endl << 
					 "iI2 = " << iI2 << std::endl <<
					 "lI3 = " << lI3 << std::endl <<
					 "cH = "  << cH << std::endl <<
					 "Pi = " << Pi << std::endl <<
					 "dPi = " << dPi << std::endl;
}

void toyXZ() {
	enum {Z, X, blank} tbl[3][3] = { // Z - "O", X - "X", blank - незаполненный квадрат
									blank, blank, blank, 
									blank, blank, blank, 
									blank, blank, blank
									};
	struct { 
		unsigned short play[2] = {1, 0}; // play[0] - играет "X", play[1] - играет "O"/ if play[i]==1 then ход у i-го игрока 
		enum {first, second, draw, none} total = none; // текущий результат игры
	} scoreboard; //Табло
	//Смотрим в scoreboard.play[] чей ход
	//Спрашиваем у соответствующего игрока координату в tbl[], куда он хочет поставить свой символ 
	std::cout << scoreboard.total << std::endl;

}

void isWhat() {
	struct iW {
		union {
			float fl;
			int i;
			char ch;
			} value;
		unsigned short isInt : 1 ;
		unsigned short isFloat : 1;
		unsigned short isChar : 1;
	} vrnt;
	vrnt.value.fl = 3.14;
	vrnt.isFloat = 1;
	std::cout << vrnt.value.fl << " "<< vrnt.isFloat << std::endl;
	vrnt.isFloat = 0;
	vrnt.value.ch = 'A';
	vrnt.isChar = 1;
	std::cout << vrnt.value.ch << " "<< vrnt.isChar << std::endl;
}

int main()
{
	tp();
	toyXZ();
	isWhat();
	return 0;
}