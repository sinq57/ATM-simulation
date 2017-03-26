#include "stdafx.h"
using namespace std;

Account::Account()
{
	blockedAmount = 0;
	cardId = "";
	pin = "0";
	balance = 0;
}

void Account::setBlockedAmount(int a)
{
	blockedAmount = a;
}

int Account::getBlockedAmount()
{
	return blockedAmount;
}
void Account::setBalance(int a)
{
	balance = a;
}

double Account::getBalance()
{
	return balance;
}

void Account::setCardId(string a)
{
	cardId = a;
}

string Account::getCardId()
{
	return cardId;
}

void Account::setPin(string a)
{
	pin = a;
}

string Account::getPin()
{
	return pin;
}