#include "stdafx.h"
using namespace std;

//BankDatabase bankDatabase;


BankDatabase::BankDatabase()
{

}

int BankDatabase::getAccountQuantity()
{
	return accountQuantity;
}

bool BankDatabase::checkPin(string id, string pin )
{
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (accountArray[i].getPin() == pin && accountArray[i].getCardId() == id)
			return true;
	}
	return false;
}
void BankDatabase::changePin()
{
	

}

void BankDatabase::substractMoney(string id, double moneyAmount)
{
	for (int i = 1; i <= this->getAccountQuantity(); i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			accountArray[i].setBalance(accountArray[i].getBalance() - moneyAmount);
			//updateAccount();
			return;
		}
	}
}