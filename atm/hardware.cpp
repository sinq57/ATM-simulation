#include "stdafx.h"

using namespace std;

Keyboard::Keyboard()
{
}

int Keyboard::getInt()
{
	int k = _getch();
	return k;
}

int Keyboard::getChar()
{
	//char k= _getch();
	char k = _getch();
	return k;
}

void Keyboard::dataIn(string &a)
{
	//cin.sync();
	//cin.ignore();
	cin >> a;
	
}

void Keyboard::dataIn(double &a)
{
	//cin.ignore();
	cin >> a;

}

void Keyboard::dataIn(char &a)
{
	//cin.ignore();
	cin >> a;
}

void Keyboard::dataIn(int &a)
{
	//cin.ignore();
	cin >> a;
}

string Keyboard::enterPassword()
{
	string pwd = "";
	char c;
	do 
	{
			c = _getch();
			switch (c)
			{
			case 0://special keys. like: arrows, f1-12 etc.
				_getch();//just ignore also the next character.
				break;
			case 13://enter
				break;
			case 8://backspace
				if (pwd.length() > 0) {
					pwd.erase(pwd.end() - 1); //remove last character from string
					cout << c << ' ' << c;//go back, write space over the character and back again.
				}
				break;
			default://regular ascii
				pwd += c;//add to string
				cout << "*";//print '*'
				break;
			}
	} while (c != 13); //enter
	return pwd;
}


Screen::Screen()
{

}

void Screen::dataOut(string a)
{
	cout << a;
}

void Screen::dataOut(double a)
{
	cout << a;
}


void Screen::dataOut(int a)
{
	cout << a;
}

void Screen::dataOut(char a)
{
	cout << a;
}

void Screen::initialdisplay()
{
	//system("color 17");
	dataOut( "\n");
	decorate();
	dataOut( "|                           WELCOME TO WBK BANK                           | \n");
	decorate();
	dataOut( "|");
	for (int i=1; i<=13; i++) dataOut( "-");
	dataOut( "  ");
	for (int i=1; i<=42; i++) dataOut( "-");
	dataOut( "  ");
	for (int i=1; i<=14; i++) dataOut( "-");
	dataOut("|");
	dataOut( "\n| WITHDRAW - 1 |");
	for (int i=1; i<=42; i++) dataOut( " ");
	dataOut( "| 2 - TRANSFER  |\n");
	printDash();
	//dataOut( " ");
	printDash();
	dataOut( "| PAY TOOL - 3 |");
	//dataOut( a );
	dataOut("                                          ");
	dataOut( "| 4 -  POPUP    |\n");
	printDash();
	//dataOut( " ");
	printDash();
	dataOut( "| BALANCE  - 5 |");
	//dataOut( b );
	dataOut("                                          ");
	dataOut( "| 6 -CHANGE PIN |\n");
	printDash();
	//dataOut( " ");
	printDash();
	dataOut( "|  FAST $  - 7 |");
	for (int i=1; i<=42; i++) dataOut( " ");
	dataOut( "| 0 -  EXIT !   |");
	dataOut( "\n|");
	for (int i=1; i<=13; i++) dataOut( "-");
	dataOut( "  ");
	for (int i=1; i<=42; i++) dataOut( "-");
	dataOut( "  ");
	for (int i=1; i<=14; i++) dataOut( "-");
	//dataOut( " ");
	dataOut("|\n\n");
	dataOut( " ----------------------------  ----------------  ------------------------- \n");
	dataOut( "|                            |  | 1 | 2 | 3 |  |                          |\n");
	dataOut( "|                            |  -------------  |         RECEIPT          |\n");
	dataOut( "|     |----------------|     |  | 4 | 5 | 6 |  |    |----------------|    |\n");
	dataOut( "|     |  INSERT CARD   |     |  -------------  |    |----------------|    |\n");
	dataOut( "|     |  -----------   |     |  | 7 | 8 | 9 |  |                          |\n");
	dataOut( "|     |     HELLO      |     |  -------------  |                          |\n");
	dataOut( "|     |----------------|     |  | Y | 0 | N |  |                          |\n");
	dataOut( "|                            |  -------------  |                          |\n");
	dataOut( " ----------------------------  ---------------  --------------------------\n");
	decorate();
	dataOut( "|                        THANK FOR USING OUR SERVICES                     |\n");
	decorate();  
	for (int i=1; i<=40; i++) dataOut( " ");
}

void Screen::decorate()
{
	dataOut("|");
	for(int i = 1; i <= 73; i++)
		dataOut("-");
	dataOut("|\n");
}

void Screen::makeBackgroundColor()
{
	system("color 17"); //system("color 07"); // default
}

void Screen::printDash()
{
	dataOut("|");
	for (int i = 1; i <= 14; i++)
		dataOut("-");
	dataOut("|");
	for (int i = 1; i <= 42; i++)
		dataOut(" ");
	dataOut("|");
	for (int i = 1; i <= 15; i++)
		dataOut("-");
	dataOut("|\n");
}

void Screen::clearScreen()
{
	system("cls");
}

void Screen::goToXY(int x, int y) {
	static HANDLE hStdout = NULL;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x,y };
	SetConsoleCursorPosition(hStdout, position);
}

void Screen::printInsideFrame(string a, int line)
{
	goToXY(16, line);
	dataOut(a);
}

void Screen::deleteInsideFrame()
{
	for (int i = 6; i <= 14; i++)
		printInsideFrame("                                          ", i);
}

void Screen::loading()  // time emulator for reading card and executing transaction 
{
	printInsideFrame("            ", 12);
	Sleep(300);
	for (int i = 1; i < 10; i++) {
		dataOut(". ");
		Sleep(200);
	}

}

CashBox::CashBox()
{

}

void CashBox::makeMoneyArray()
{
	ifstream f_money("MoneyInBank.txt");
	int count = 0, denomination, number;
	if (f_money.is_open())
	{
		while (!f_money.eof())
		{
			++count;
			f_money >> denomination >> number;
			moneyArray[count].setDenomination(denomination);
			moneyArray[count].setNumber(number);
			
		}
		denominationNumber = count;
		f_money.close();
	}
}

long CashBox::totalMoney()
{
	long sum = 0;
	for (int i = 0; i <= denominationNumber; i++)
		sum += moneyArray[i].getDenomination()*moneyArray[i].getNumber();
	return sum;
}

void CashBox::updateMoney()
{
	ofstream f_money("MoneyInBank.txt");
	for (int i = 1; i <= denominationNumber; i++)
	{
		if (i != denominationNumber)
			f_money << moneyArray[i].getDenomination() << " " << moneyArray[i].getNumber() << endl;
		else
			f_money << moneyArray[i].getDenomination() << " " << moneyArray[i].getNumber();
	}
	f_money.close();
}

Money* CashBox::getMoneyArray()
{
	return moneyArray;
}

int CashBox::getDenominationNumber()
{
	return denominationNumber;
}

CardReader::CardReader()
{

}

void CardReader::display(string a)
{
	Screen screen;
	for (int i = 1; i <= 5; i++) {
		screen.goToXY(6, 23);
		screen.dataOut(a);
		Sleep(200);
		screen.goToXY(6, 23);
		screen.dataOut("|                |");
		Sleep(200);
		screen.goToXY(6, 23);
		screen.dataOut(a);
		Sleep(200);
		screen.goToXY(6, 23);
		screen.dataOut("|                |");
	}
}
