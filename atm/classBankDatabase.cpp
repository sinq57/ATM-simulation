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
			f_acc >> id >> pin >> balance >> blockState;
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
		screen.printInsideFrame("    TIM KIEM FILE DU LIEU THAT BAI !\n\n\n\n\n\n\n\a",8);
		exit(0); //break the whole program
	}
	
}


// // XEM LAI "SAU KHI DA NHAP y/n ??"
void BankDatabase::changePin(string id)   
{
	CardReader cardReader;
	Screen screen;
	Keyboard keyboard;
	for (int i = 1; i <= getAccountQuantity(); i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			int tryLimit(3);
		LABEL1:
			screen.deleteInsideFrame();
			string oldPin = "";
			for (int i = 1; i <= 6; i++)
			{
				char x = keyboard.getInt();
				screen.dataOut("*");
				oldPin += x;
			}
			keyboard.getInt();
			screen.loading();
			if (accountArray[i].getPin() == oldPin)
			{
				screen.printInsideFrame("          ACCEPTED PIN !  ", 10);
				Sleep(1500);
			LABEl2:
				string newPin1, newPin2;
				screen.deleteInsideFrame();
				screen.printInsideFrame("          ENTER NEW PIN:  ", 6);
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
				if (newPin1 == newPin2)
				{
					screen.printInsideFrame("           DOI MA PIN THANH CONG !  ", 10);
					screen.printInsideFrame("         TIEP TUC GIAO DICH ? (Y/N) ", 12);
					accountArray[i].setPin(newPin1);
					updateAccount();
					TransactionHistory transactionHistory;
					transactionHistory.saveTransaction();
					//f_diary << "DOI MA PIN THANH CONG\n";
					//f_hoadon << "DOI MA PIN THANH CONG\n";
					return;
				}
				else
				{
					screen.printInsideFrame("\a              WRONG CONFIRMATION     ", 10);
					screen.printInsideFrame("\a      TRY AGAIN OR CANCEL (Y/N) ", 12);
					int decision = keyboard.getInt();
					if (decision == 'Y' || decision == 'y') {
						goto LABEl2;
					}
					else 
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("      CANCEL CHANGING PIN !   ", 10);
						screen.printInsideFrame("         CONTINUE ? (Y/N)  ", 12);
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
					screen.printInsideFrame("     CONTINUE OR CANCEL ? (Y/N) ", 8);
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
					//	p.hienThi("|     NUOT THE     |\n");
					exit(0);  // finish program
				}
			}
		}
	}

}  

void BankDatabase::updateAccount()
{
	ofstream f_acc("ClientAccount.txt"); // write to file
	for (int i = 0; i <= accountQuantity; i++)
	{
		f_acc << accountArray[i].getCardId() << " " << accountArray[i].getPin() << " " << accountArray[i].getBalance() << " " << accountArray[i].getBlockState() << endl;
	}
	f_acc.close();
}

bool BankDatabase::haveAccount(string id)
{
	for (int i = 1; i <= accountQuantity; i++)
	{
		if (this->accountArray[i].getCardId() == id)
			return true;
	}
	return false;
}

void BankDatabase::substractMoney(string id, double moneyAmount)
{
	for (int i = 1; i <= this->getAccountQuantity(); i++)
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
	for (int i = 1; i <= getAccountQuantity(); i++)
	{
		if (accountArray[i].getCardId() == id)
		{
			screen.printInsideFrame("         YOUR BALANCE:   ", 8);
			cout << fixed << setw(5) << setprecision(2) << accountArray[i].getBalance() << " $\n";
			screen.printInsideFrame("         CONTINUE TRANSACTION ? (Y/N) ", 10);
			transactionHistory.saveTransaction();
			// can bo sung phan nhat ki
		}
	}
}

void BankDatabase::transfer()
{
	//.....
}