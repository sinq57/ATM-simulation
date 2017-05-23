#pragma once

#include "stdafx.h"

//class BlackAccountList;
//class BlackAccountObserver;
//using namespace std;

//****************************************************
//**  this is the main frame showing how the atm work
//**  
//*****************************************************



class Atm
{
public:
	Atm();
	Atm::Atm(FILE* fDiary, FILE* fReceipt);
	bool ifReceiptCreated();
	void run();
	BankDatabase* getBankDatabase();
	CashBox* getCashBox();
	BlackAccountList* getBlackAccountList();

private:
	Transaction transaction;
	//TransactionHistory transactionHistory;
	Keyboard keyboard;
	Screen screen;
	CardReader cardReader;
	Receipt receipt;
	CashBox cashBox;
	BankDatabase bankDatabase;
	BlackAccountList blackAccountList;
	BlackAccountObserver blackAccountObserver;
};