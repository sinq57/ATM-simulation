#pragma once
#include "stdafx.h"
using namespace std;


class Account
{
public:
	Account();
	void setBlockState(int);
	int getBlockState() const;

	void setCardId(string);
	string getCardId() const;

	void setPin(string);
	string getPin() const;

	void setBalance(int);
	double getBalance() const;
protected:
	int blockState;  // '1': blocked
	string cardId;
	string pin;
	double balance;
};
