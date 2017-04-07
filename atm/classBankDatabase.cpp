#include "stdafx.h"
using namespace std;

//BankDatabase bankDatabase;


BankDatabase::BankDatabase()
{

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
		if ((getAccountArray() + i)->getPin() == pin && (getAccountArray() + i)->getCardId() == id)
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
			(getAccountArray() + i)->setPin(pin);
			(getAccountArray() + i)->setCardId(id);
			(getAccountArray() + i)->setBalance(balance);
			(getAccountArray() + i)->setBlockState(blockState);
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
		if ((getAccountArray() + i)->getCardId() == id)
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
			if ((getAccountArray() + i)->getPin() == oldPin)
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
					(getAccountArray() + i)->setPin(newPin1);
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
					(getAccountArray() + i)->setBlockState(1);
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
		f_acc << (getAccountArray() + i)->getCardId() << " " << (getAccountArray() + i)->getPin() << " " << (getAccountArray() + i)->getBalance() << " " << (getAccountArray() + i)->getBlockState() << endl;
	}
	f_acc.close();
}

bool BankDatabase::haveAccount(string id)
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
	for (int i = 1; i <= this->getAccountQuantity(); i++)
	{
		if ((getAccountArray() + i)->getCardId() == id)
		{
			(getAccountArray() + i)->setBalance((getAccountArray() + i)->getBalance() - moneyAmount);
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
		if ((getAccountArray() + i)->getCardId() == id)
		{
			screen.printInsideFrame("         YOUR BALANCE:   ", 8);
			cout << fixed << setw(5) << setprecision(2) << (getAccountArray() + i)->getBalance() << " $\n";
			screen.printInsideFrame("         CONTINUE TRANSACTION ? (Y/N) ", 10);
			transactionHistory.saveTransaction();
			// can bo sung phan nhat ki
		}
	}
}


void BankDatabase::transfer(string id)
{
	//.....
	Screen screen;
	Keyboard keyboard;
	CardReader cardReader;
	for (int i = 1; i <= this->getAccountQuantity(); i++)
	{
		if ((getAccountArray() + i)->getCardId() == id)
		{
			string receiver;
			LABEL1:
			screen.deleteInsideFrame();
			screen.printInsideFrame("    GIVE CARD ID OF RECEIVER :", 6);
			keyboard.dataIn(receiver);
			if (receiver == id)
			{
				screen.printInsideFrame("   CANNOT TRANSFER TO YOUR ACCOUNT !", 8);
				screen.printInsideFrame("     CONTINUE OR CANCEL TRANSACTION? (Y/N)", 10);
				int z = keyboard.getInt();
				if (z == 'Y' || z == 'y') {
					goto LABEL1;
				}
				for (int j = 1; j <= this->getAccountQuantity(); j++)
				{
					if ((getAccountArray() + j)->getCardId() == receiver)
					{
					LABEL2:
						screen.deleteInsideFrame();
						Sleep(300);
						screen.printInsideFrame("     ENTER AMOUNT YOU WANT TO TRANSFER" ,8);
						double amount;
						keyboard.dataIn(amount);
						if (amount > (getAccountArray() + i)->getBalance())
						{
							screen.printInsideFrame("     YOU DON NOT HAVE ENOUGH MONEY !!!", 10);
							screen.printInsideFrame("     CONTINUE OR CANCEL TRANSACTION? (Y/N)", 12);
							z = keyboard.getInt();
							if (z == 'Y' || z == 'y') goto LABEL2;
							else
							{
								screen.deleteInsideFrame();
								screen.printInsideFrame("	  YOU CANCELED TRANSFER !", 10);
								screen.printInsideFrame("         CONTINUE ? (Y/N) ", 12);
								return;
							}
							
						}
						else
						{
							screen.loading();
							screen.deleteInsideFrame();
							screen.printInsideFrame("     TRANSACTION SUCCEEDED !!!", 10);
							screen.printInsideFrame("     CONTINUE ? (Y/N)", 12);
							(getAccountArray() + i)->setBalance((getAccountArray() + i)->getBalance() - amount);
							(getAccountArray() + j)->setBalance((getAccountArray() + j)->getBalance() + amount);
							updateAccount();

							// tramsaction history ????? 
							return;
						}
					}
					
				}

				screen.loading();
				screen.printInsideFrame("    NO SUCH ACCOUNT FOUND !!! ",8);
				screen.printInsideFrame("    CONTINUE OR CANCEL ? (Y/N) ",10);
				int s = keyboard.getInt();
				if (s == 'Y' || s == 'y') {
					goto LABEL1;
				}
				else
				{
					screen.printInsideFrame("	  YOU CANCELED TRANSFER !", 8);
					screen.printInsideFrame("    CONTINUE OR CANCEL ? (Y/N) ", 10);
					return;
				}
			}
		}
	}
}

void BankDatabase::withdraw(string id, CashBox cashBox)
{
	Screen screen;
	Keyboard keyboard;
	Bill bill;
	double withdrawAmount;
	int withdrawnMoneyArray[10];
	Money* moneyArrayPtr = cashBox.getMoneyArray();
	//Account* accountArrayPtr = getAccountArray();


	for (int i = 1; i <= accountQuantity; i++)
	{
		if ((getAccountArray() + i)->getCardId() == id)
		{
			//
			int moneyLeft = (getAccountArray() + i)->getBalance();
		LABEL1:
			screen.deleteInsideFrame();
			screen.printInsideFrame("    WITHDRAW TRAMSACTION:", 6);
			screen.printInsideFrame("     ENTER MONEY AMOUNT", 8);
			keyboard.dataIn(withdrawAmount);
			double intPart;  // must use 'modf' because "%" (mod) is olny for int
			double fractPart = modf(withdrawAmount, &intPart);
			if (fractPart != 0)
			{
				goto LABEL1;

			}
			screen.loading();
			if (withdrawAmount > cashBox.totalMoney())
			{

			}
			else
			{
				if (withdrawAmount > moneyLeft)
				{

				}
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("    WITHDRAW SUCCESS :)", 6);
					screen.printInsideFrame("         ", 8);
					moneyLeft -= withdrawAmount;
					for (int j = 0; j < cashBox.getDenominationNumber(); j++) withdrawnMoneyArray[j] = 0;
					for (int j = 0; j < cashBox.getDenominationNumber(); j++)
					{
						while ((moneyArrayPtr + j)->getDenomination() <= withdrawAmount && (moneyArrayPtr + j)->getNumber() > 0 && withdrawAmount > 0)
						{
							withdrawAmount -= (moneyArrayPtr + j)->getDenomination();
							withdrawnMoneyArray[j]++;
						}
					}
					for (int j = 0; j < cashBox.getDenominationNumber(); j++)
					{
						screen.dataOut((moneyArrayPtr + j)->getDenomination());
						screen.dataOut("$: ");
						screen.dataOut(withdrawnMoneyArray[j]);
						screen.dataOut("   ");

					}
					(getAccountArray() + i)->setBalance(moneyLeft);
					screen.printInsideFrame("    CONTINUE TRANSACTION ? (Y/N)",10);
					//LUU NHAT KI GIAO DICH

				}
			}
		}
		
	}

}

