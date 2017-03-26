#pragma once

class BankDatabase
{
public:
	BankDatabase();
	bool checkPin(string id, string pin);
	void checkBalance(string id);
	void withdraw(); //Ruts tien 
	bool haveAccount(string id);
	void createAccountArray();
	void updateAccount();
	int getAccountQuantity();
	void substractMoney(string id, double moneyAmount);
	void changePin(string pin);
	void transfer();
	Account accountArray[1000];
private:
	int accountQuantity;
};
