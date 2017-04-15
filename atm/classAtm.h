#pragma once
#include "stdafx.h"
using namespace std;

//****************************************************
//**  this is the main frame showing how the atm work
//**  
//*****************************************************

class Atm
{
public:
	Atm();
	void run();
	BankDatabase* getBankDatabase();
	CashBox* getCashBox();

private:
	Transaction transaction;
	Keyboard keyboard;
	Screen screen;
	CardReader cardReader;
	Bill bill;
	CashBox cashBox;
	BankDatabase bankDatabase;
};