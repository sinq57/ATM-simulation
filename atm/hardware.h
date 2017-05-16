//*************************************************************
//************ SET OF: keyboard, screen, cardreader and moneybox
//*************************************************************

#pragma once
//#include "stdafx.h"
#include "classMoney.h"


using namespace std;
class Money;

class Keyboard
{
public:
	Keyboard();
	void dataIn(string&);
	void dataIn(double&);
	void dataIn(char &);
	void dataIn(int &);
	int getInt();
	int getChar();
	string enterPassword();
private:
};

class Screen
{
public:
	Screen();
	void dataOut(string);
	void dataOut(int);
	void dataOut(double);
	void dataOut(char);
	void initialdisplay();
	void makeBackgroundColor();
	void printDash();
	void decorate();
	void clearScreen();
	void loading();
	void goToXY(int x, int y);

	void printInsideFrame(string, int);
	void deleteInsideFrame();

private:
};

class CashBox
{
public:
	
	CashBox();
	void makeMoneyArray();
	int getDenominationNumber();
	long totalMoney();
	void updateMoney();
	Money* getMoneyArray();
	~CashBox();
private:
	int denominationNumber;
	Money moneyArray[10];
};

class CardReader
{
public:
	CardReader();
	int getCardAccountNumber();
	void display(string a);
private:
};