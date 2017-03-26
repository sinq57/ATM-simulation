#pragma once

class BankDatabase
{
public:
	BankDatabase();
	bool checkPin(string id, string pin);
	void checkBalance();
	void withdraw(); //Ruts tien 
	bool haveAccount();
	void createAccountArray();
	void updateAccount();
	int getAccountQuantity();
	void substractMoney(string id, double moneyAmount);
	void changePin();
	void transfer();
	Account accountArray[1000];
private:
	int accountQuantity;
};
