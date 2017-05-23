#pragma once
#include "stdafx.h"
using namespace std;

class BankDatabase;

class Transaction
{
public:
	Transaction();
	Transaction(FILE*, FILE*);
	void payTool(string id, BankDatabase * bankDatabase);
	void mobilePopup(string id, BankDatabase* bankDatabase);
	void fastCash(string id, BankDatabase* bankDatabase, CashBox *cashBox);
	void withdraw(string id, BankDatabase* bankDatabase, CashBox *cashBox);
	void transfer(string id, BankDatabase* bankDatabase);
	void saveHistory();
	FILE* getFileReceipt();
private:
	FILE *fileDiary;
	FILE *fileReceipt;
};