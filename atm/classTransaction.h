#pragma once
#include "stdafx.h"
using namespace std;

class BankDatabase;

class Transaction
{
public:
	Transaction();
	void checkBalance();
	void payTool(string id, BankDatabase * bankDatabase);
	void mobilePopup(string id, BankDatabase* bankDatabase);
	void printStatement(); //in sao kê
	void withdraw(string id, BankDatabase* bankDatabase, CashBox *cashBox);
	void transfer(string id, BankDatabase* bankDatabase);

private:

};