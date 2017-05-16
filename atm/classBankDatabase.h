#pragma once



class BlackAccountObserver;
class Account;

class BankDatabase
{
public:
	BankDatabase();
	BankDatabase(FILE*, FILE*);
	bool checkPin(string id, string pin);
	void checkBalance(string id);
	//void withdraw(string id, CashBox cashBox); //Ruts tien 
	bool ifAccountCreated(string id);
	void createAccountArray();
	void updateAccount();
	int getAccountQuantity();
	void substractMoney(string id, double moneyAmount);
	void changePin(string pin);
	void saveHistory();
	Account* getAccountArray();
	void BankDatabase::unblockAccount(string id);
	void actualizeBlackAccount(vector<BlackAccountObserver*> &);
private:
	Account accountArray[20];
	int accountQuantity;
	FILE *fileDiary;
	FILE *fileReceipt;
};
