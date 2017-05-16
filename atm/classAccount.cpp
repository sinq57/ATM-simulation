#include "stdafx.h"
using namespace std;

Account::Account()
{
	blockState = 0;
	cardId = "";
	pin = "0";
	balance = 0;
}

void Account::setBlockState(int a)
{
	blockState = a;
}

int Account::getBlockState() const
{
	return blockState;
}
void Account::setBalance(int a)
{
	balance = a;
}

double Account::getBalance() const
{
	return balance;
}

void Account::setCardId(string a)
{
	cardId = a;
}

string Account::getCardId() const
{
	return cardId;
}

void Account::setPin(string a) 
{
	pin = a;
}

string Account::getPin() const
{
	return pin;
}