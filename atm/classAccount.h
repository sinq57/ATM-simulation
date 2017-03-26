#pragma once
#include "stdafx.h"
using namespace std;


class Account
{
public:
	Account();
	void setBlockState(int);
	int getBlockState();

	void setCardId(string);
	string getCardId();

	void setPin(string);
	string getPin();

	void setBalance(int);
	double getBalance();
private:
	int blockState;  // '1': blocked
	string cardId;
	string pin;
	double balance;
};
