#pragma once

class BankDatabase
{
public:
	BankDatabase();
	bool checkPin(string id, string pin);
	void checkBalance(string id);
	//void withdraw(string id, CashBox cashBox); //Ruts tien 
	bool ifAccountCreated(string id);
	void createAccountArray();
	void updateAccount();
	int getAccountQuantity();
	void substractMoney(string id, double moneyAmount);
	void changePin(string pin);
	//void transfer(string id);
	Account* getAccountArray();
private:
	Account accountArray[1000];
	int accountQuantity;
};
