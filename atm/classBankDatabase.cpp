#include "stdafx.h"
using namespace std;

//BankDatabase bankDatabase;


BankDatabase::BankDatabase()
{

}

BankDatabase::BankDatabase(FILE* fDiary, FILE* fReceipt)
{
	accountQuantity = 0;
	fileDiary = fDiary;
	fileReceipt = fReceipt;
}


Account* BankDatabase::getAccountArray()
{
	return accountArray;
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

void BankDatabase::createAccountArray()
{
	Screen screen;
	ifstream f_acc("ClientAccount.txt");  //read from file
	int i = 0;
	string id, pin;
	double balance;
	int blockState;
	if (f_acc.is_open())
	{
		while (!f_acc.eof())
		{
			i++;
			f_acc >> blockState >> id >> pin >> balance;
			accountArray[i].setPin(pin);
			accountArray[i].setCardId(id);
			accountArray[i].setBalance(balance);
			accountArray[i].setBlockState(blockState);
		}
		accountQuantity = i; 
		f_acc.close();
	}
	else
	{
		screen.printInsideFrame("      DATABASE NOT FOUND !\a\a\a\a\a",8);
		Sleep(3000);
		screen.printInsideFrame("         SEE YOU AGAIN :)   ", 12);
		Sleep(2000);
		//system("pause");
		exit(0); //break the whole program
	}
	
}

// // XEM LAI "SAU KHI DA NHAP y/n ??"
void BankDatabase::changePin(string id)   
{
	CardReader cardReader;
	Screen screen;
	Keyboard keyboard;
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			int tryLimit(3);
		LABEL1:
			screen.deleteInsideFrame();
			string oldPin = "";
			screen.printInsideFrame("     PLEASE ENTER OLD PIN: ",8);
			for (int i = 1; i <= 6; i++)
			{
				char x = keyboard.getInt();
				screen.dataOut("*");
				oldPin += x;
			}
			keyboard.getInt();
			screen.loading();
			screen.printInsideFrame("                                 ", 12);
			if (accountArray[i].getPin() == oldPin)
			{  
				screen.printInsideFrame("          ACCEPTED  !          ", 10);
				Sleep(1500);
			LABEl2:
				string newPin1, newPin2;
				screen.deleteInsideFrame();
				screen.printInsideFrame("        ENTER NEW 6-DIGIT PIN:  ", 6);
				for (int i = 1; i <= 6; i++) {
					char x = keyboard.getChar();
					screen.dataOut("*");
					newPin1 += x;
				}
				keyboard.getInt();
				screen.printInsideFrame("          CONFIRM NEW PIN:  ", 8);
				for (int i = 1; i <= 6; i++) {
					char x = keyboard.getChar();
					screen.dataOut("*");
					newPin2 += x;
				}
				keyboard.getInt();
				screen.loading();
				screen.deleteInsideFrame();
				if (newPin1 == newPin2)
				{
					screen.printInsideFrame("         CHANGE PIN SUCCESSFULLY !  ", 10);
					screen.printInsideFrame("       CONTINUE OR CANCEL ? (Y/N)  ", 12);
					accountArray[i].setPin(newPin1);
					updateAccount();
					//save history
					saveHistory();
					fprintf(fileDiary, ": %s\n", id.c_str());
					fprintf(fileDiary, ": PIN changed successfully\n");
					fprintf(fileReceipt, ": PIN changed successfully\n");
					return;
				}
				else
				{
					screen.printInsideFrame("\a             WRONG CONFIRMATION     ", 10);
					screen.printInsideFrame("\a         TRY AGAIN OR CANCEL (Y/N)  ", 12);
					int decision = keyboard.getInt();
					if (decision == 'Y' || decision == 'y') {
						goto LABEl2;
					}
					else 
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("         CANCEL CHANGING PIN !   ", 10);
						screen.printInsideFrame("             CONTINUE ? (Y/N)  ", 12);
						return;
					}
				}
			}
			else
			{
				if (tryLimit != 0)
				{
					screen.printInsideFrame("  ERROR, PLEASE AGAIN, TRY TIME LEFT :\a", 6);
					screen.dataOut(tryLimit);
					screen.printInsideFrame("         CONTINUE OR CANCEL ? (Y/N) ", 8);
					int decision = keyboard.getInt();
					if (decision == 'Y' || decision == 'y')
					{
						tryLimit--;
						goto LABEL1;
					}
					else
					{
						screen.printInsideFrame("       CANCEL CHANGING PIN !: ", 10);
						screen.printInsideFrame("         CONTINUE TRANSACTION ? (Y/N)  ", 12);
						return;
					}
				}
				else
				{
					screen.printInsideFrame("	EXCEED TRY LIMIT, ACCOUNT BLOCKED ! \a", 10);
					accountArray[i].setBlockState(1);
					updateAccount();
					screen.printInsideFrame("   CONTACK BANK TO RECEIVE CARD ! \a", 12);
					cardReader.display("| CARD SWALLOWED |\n");
					exit(0);  // finish program
				}
			}
		}
	}

}  

void BankDatabase::updateAccount()
{
	ofstream f_acc("ClientAccount.txt"); // write to file
	for (int i = 1; i <= accountQuantity; i++)
	{	
		if (i != accountQuantity)
			f_acc << accountArray[i].getBlockState() << " " << accountArray[i].getCardId() << " " << accountArray[i].getPin() << " " << fixed << setprecision(2) << accountArray[i].getBalance() << endl;
		else
			f_acc << accountArray[i].getBlockState() << " " << accountArray[i].getCardId() << " " << accountArray[i].getPin() << " " << fixed << setprecision(2) << accountArray[i].getBalance();
	}
	f_acc.close();
}

bool BankDatabase::ifAccountCreated(string id)
{
	for (int i = 1; i <= accountQuantity; i++)
	{
		if ((getAccountArray() + i)->getCardId() == id)
			return true;
	}
	return false;
}

void BankDatabase::substractMoney(string id, double moneyAmount)
{
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			accountArray[i].setBalance(accountArray[i].getBalance() - moneyAmount);
			updateAccount();
			return;
		}
	}
}

void BankDatabase::checkBalance(string id)
{
	Screen screen;
	TransactionHistory transactionHistory;
	screen.loading();
	screen.deleteInsideFrame();
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("         YOUR BALANCE: ", 8);
			cout << fixed << setw(5) << setprecision(2) << accountArray[i].getBalance() << " $\n";
			screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 10);
			//save history
			saveHistory();
			fprintf(fileDiary, ": %s\n", id.c_str());
			fprintf(fileDiary, ": Check account balance: %.2f $", accountArray[i].getBalance());
			fprintf(fileReceipt, ": Check account balance: %.2f $", accountArray[i].getBalance());
			return;
		}
	}
}

void BankDatabase::saveHistory()
{
	time_t rawtime;
	time(&rawtime);
	char str[26];
	ctime_s(str, sizeof(str), &rawtime);
	fprintf(fileDiary, "\n\nTime: %s", str);
	fprintf(fileReceipt, "\n\nTime: %s", str);
}

void BankDatabase::actualizeBlackAccount(vector<BlackAccountObserver*> &observers)
{	
	if (!observers.empty())
	{
		for (auto it = observers.begin(); it != observers.end(); ++it)
		{
			for (int i = 1; i <= accountQuantity; i++)
			{
				if ((*it)->getCardId() == (getAccountArray() + i)->getCardId())
				{
					(getAccountArray() + i)->setBlockState((*it)->getBlockState());
					break;
				}
			}
		}
	}
	updateAccount();
}

void BankDatabase::unblockAccount(string id)
{
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			accountArray[i].setBlockState(0);
			updateAccount();
			break;
		}
	}
}