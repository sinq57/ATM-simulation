#pragma once
#include "stdafx.h"
using namespace std;


class Account
{
public:
	Account();
	void setBlockedAmount(int);
	int getBlockedAmount();

	void setCardId(string);
	string getCardId();

	void setPin(string);
	string getPin();

	void setBalance(int);
	double getBalance();
private:
	int blockedAmount;
	string cardId;
	string pin;
	double balance;
};

class example;