#include "stdafx.h"
using namespace std;

Transaction::Transaction()
{

}

Transaction::Transaction(FILE* fDiary, FILE* fReceipt)
{
	fileDiary = fDiary;
	fileReceipt = fReceipt;
}

//void Transaction::checkBalance()
//{
//}

void Transaction::mobilePopup(string id, BankDatabase* bankDatabase)
{
	Screen screen;
	Keyboard keyboard;
	Sleep(100);
LABEL1:
	screen.deleteInsideFrame();
	screen.printInsideFrame("            CHOSE OPERATOR    ", 6);
	screen.printInsideFrame("       1.T-MOBILE      2.HEYAH    ", 8);
	screen.printInsideFrame("       3.LYCAMOBILE    4.ORANGE   ", 10);
	int k = keyboard.getInt();

	switch (k)
	{
		case '1':
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("       T-MOBILE CHOSEN         ", 10);
			break;
		}
		case '2':
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("       HEYAH CHOSEN            ", 10);
			break;
		}
		case '3':
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("       LYCAMOBILE CHOSEN       ", 10);
			break;
		}
		case '4':
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("       ORANGE                 ", 10);
			break;   
		}
		default:
		{
			screen.printInsideFrame("\a WRONG! CHOOSE AGAIN OR CANCEL (Y/N) ? ", 12);
			int h = keyboard.getInt();
			if (h == 'Y' || h == 'y') {
				screen.deleteInsideFrame();
				goto LABEL1;
			}
			else {
				screen.deleteInsideFrame();
				screen.printInsideFrame("     POPUP CANCELED, THANK YOU       ", 10);
				screen.printInsideFrame("    CONTINUE TRANSACTION (Y/N) ? ", 12);
				return;
			}
		}

	}
	string code[] = { "3425 4563 6435", "6547 4356 3456", "5467 3463 2467", "3545 9999 5680", "3456 6733 3556","1234 5435 2352","2353 3532 1364" };
LABEL2:
	Sleep(100);
	screen.deleteInsideFrame();
	screen.printInsideFrame("            CHOOSE THE FOLLOWING" , 6);
	screen.printInsideFrame("      1: 50 $     2: 20 $    3: 10 $    ", 8);
	screen.printInsideFrame("      4:  5 $     5:  2 $    6:  1 $    ", 10);
	int h = keyboard.getInt();
	
	double mny;
	switch (h)
	{
		case '1':
		{
			mny = 50;
			break;
		}
		case '2':
		{
			mny = 20;
			break;
		}
		case '3':
		{
			mny = 10;
			break;
		}
		case '4':
		{
			mny = 5;
			break;
		}
		case '5':
		{
			mny = 2;
			break;
		}
		case '6':
		{
			mny = 1;
			break;
		}
		default:
		{
			screen.printInsideFrame("\a WRONG! CHOOSE AGAIN OR CANCEL (Y/N) ? ", 12);
			int s = keyboard.getInt();
			if (s == 'Y' || s == 'y') {
				screen.deleteInsideFrame();
				goto LABEL2;
			}
			else {
				screen.deleteInsideFrame();
				screen.printInsideFrame("     POPUP CANCELED, THANK YOU      ", 10);
				screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 12);
				return;
			}
		}

	}

	for (int i = 1; i <= bankDatabase->getAccountQuantity(); i++)
	{
		if ((bankDatabase->getAccountArray() + i)->getCardId() == id)
		{
			if (mny > (bankDatabase->getAccountArray() + i)->getBalance())
			{
				screen.loading();
				screen.deleteInsideFrame();
				screen.printInsideFrame("      YOU DO NOT HAVE ENOUGH MONEY!    ", 8);
				screen.printInsideFrame("  ENTER AMOUNT AGAIN OR CANCEL (Y/N) ? ", 10);
				int g = keyboard.getInt();
				if (g == 'Y' || g == 'y') goto LABEL2;
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("         POPUP CANCELED !         ", 8);
					screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 10);
					return;
				}
			}
			else
			{
				//hatKyGiaoDichMRT.luuGiaoDich();
				saveHistory();
				switch (k) {
					case '1': {
						fprintf(fileDiary, ": T-MOBILE TOPUP: ");
						fprintf(fileReceipt, ": T-MOBILE TOPUP: ");
						break;
					}
					case '2': {
						fprintf(fileDiary, ": HEYAH TOPUP: ");
						fprintf(fileReceipt, ": HEYAH TOPUP: ");
						break;
					}
					case '3': {
						fprintf(fileDiary, ": LYCAMOBILEE TOPUP: ");
						fprintf(fileReceipt, ": LYCAMOBILE TOPUP: ");
						break;
					}
					case '4': {
						fprintf(fileDiary, ": ORANGE TOPUP: ");
						fprintf(fileReceipt, ": ORANGE TOPUP: ");
						break;
					}
				}
				fprintf(fileDiary, "%.2f | ", mny);
				fprintf(fileReceipt, "%.2f | ", mny);
				
				screen.loading();
				screen.deleteInsideFrame();
				bankDatabase->substractMoney(id, mny);
				screen.deleteInsideFrame();
				screen.printInsideFrame("   YOUR CODE IS: ", 8);
				srand(time(0));
				h = rand() % 6 + 1;
				screen.dataOut(code[h]);
				screen.printInsideFrame("          POPUP SUCCEEDED :)        ", 10);
				screen.printInsideFrame("       CONTINUE OR NOT (Y/N) ? ", 12);

				fprintf(fileDiary, "code: %s", code[h].c_str());
				fprintf(fileReceipt, "code: %s", code[h].c_str());
				break;
			}
		}
	}

}

void Transaction::payTool(string id, BankDatabase* bankDatabase)
{
	Screen screen;
	Keyboard keyboard;
	double mny;
	screen.deleteInsideFrame();
LABEL0:
	screen.printInsideFrame("            CHOOSE THE FOLLOWING  ", 6);
	screen.printInsideFrame("         1.INSUARANCE    2.TELEPHONE ", 8);
	screen.printInsideFrame("         3.INTERNET      4.GAS      ", 10);
LABEL1:
	int c = keyboard.getInt();
	switch (c)
	{
		case '1':
		case '2':
		case '3':
		case '4':
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("      PLEASE ENTER MONEY AMOUNT: ",6);
			keyboard.dataIn(mny);
			break;
		}
		default:
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("       WRONG !!! PLEASE TRY AGAIN    ",6);
			Sleep(200);
			goto LABEL0;
			break;
		}
	}

	for (int i = 1; i <= bankDatabase->getAccountQuantity(); i++)
	{
		if ((bankDatabase->getAccountArray() + i)->getCardId() == id)
		{
			if (mny > (bankDatabase->getAccountArray() + i)->getBalance())
			{
				screen.printInsideFrame("      YOU DO NOT HAVE ENOUGH MONEY! ", 8);
				screen.printInsideFrame("  ENTER AGAIN OR CANCEL TRANSACTION (Y/N) ? ", 10);
				int k = keyboard.getInt();
				if (k == 'Y' || k == 'y') goto LABEL1;
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("        WITHDRAW TRANSACTION CANCELED !    ", 8);
					screen.printInsideFrame("        CONTINUE TRANSACTION? (Y/N) ? ", 10);
					return;
				}
			}
			else //(mny <= (bankDatabase->getAccountArray() + i)->getBalance())
			{
				//  save history here
				saveHistory();
				switch (c)
				{
					case '1':
					{
						fprintf(fileDiary, ": %s\n", id.c_str());
						fprintf(fileDiary, ": Insuarace Payment: ");
						fprintf(fileReceipt, ": Insuarace Payment: ");
						break;
					}
					case '2':
					{
						fprintf(fileDiary, ": %s\n", id.c_str());
						fprintf(fileDiary, ": Telephone Payment: ");
						fprintf(fileReceipt, ": Telephone Payment: ");
						break;
					}
					case '3':
					{
						fprintf(fileDiary, ": %s\n", id.c_str());
						fprintf(fileDiary, ": Internet Payment: ");
						fprintf(fileReceipt, ": Internet Payment: ");
						break;
					}
					case '4':
					{
						fprintf(fileDiary, ": %s\n", id.c_str());
						fprintf(fileDiary, ": Gas Payment: ");
						fprintf(fileReceipt, ": Gas Payment: ");
						break;
					}
				}

				fprintf(fileDiary, "%.2f", mny);
				fprintf(fileReceipt, "%.2f", mny);
				//**************************************

				screen.loading();
				screen.deleteInsideFrame();
				bankDatabase->substractMoney(id, mny);
				screen.deleteInsideFrame();
				screen.printInsideFrame("          PAYMENT SUCCEEDED !    ", 8);
				screen.printInsideFrame("      CONTINUE TRANSACTION (Y/N) ? ", 10);
			}

		}
	}

}


void Transaction::fastCash(string id, BankDatabase* bankDatabase, CashBox *cashBox)
{
	Screen screen;
	Keyboard keyboard;
	
	int withdrawnMoneyArray[10]; // array consits of  withdrawn money number;

	Money* moneyArrayPtr = cashBox->getMoneyArray();
	Account* accountArrayPtr = bankDatabase->getAccountArray();
LABEL0:
	screen.deleteInsideFrame();

	screen.printInsideFrame("            CHOOSE THE FOLLOWING  ", 6);
	screen.printInsideFrame("      1: 50 $     2: 100 $   3: 150 $   ", 8);
	screen.printInsideFrame("      4: 200 $    5: 400 $   6: 500 $   ", 10);

	int h = keyboard.getInt();

	double withdrawnAmount;
	switch (h)
	{
		case '1':
		{
			withdrawnAmount = 50;
			break;
		}
		case '2':
		{
			withdrawnAmount = 100;
			break;
		}
		case '3':
		{
			withdrawnAmount = 150;
			break;
		}
		case '4':
		{
			withdrawnAmount = 200;
			break;
		}
		case '5':
		{
			withdrawnAmount = 400;
			break;
		}
		case '6':
		{
			withdrawnAmount = 500;
			break;
		}
		default:
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("\a WRONG! CHOOSE AGAIN OR CANCEL (Y/N) ? ", 12);
			int s = keyboard.getInt();
			if (s == 'Y' || s == 'y') {
				//screen.deleteInsideFrame();
				goto LABEL0;
			}
			else {
				screen.deleteInsideFrame();
				screen.printInsideFrame("         FAST CASH CANCELED !     ", 10);
				screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 12);
				return;
			}
		}
	}


	for (int i = 1; i <= bankDatabase->getAccountQuantity(); i++)
	{
		if ((accountArrayPtr + i)->getCardId() == id)
		{
			//
			double moneyLeft = (accountArrayPtr + i)->getBalance();
		//LABEL1:
			screen.loading();
			screen.deleteInsideFrame();
			if (withdrawnAmount > cashBox->totalMoney())
			{
				screen.deleteInsideFrame();
				screen.printInsideFrame("   SORRY, NOT ENOUGH MONEY IN ATM!!\a", 10);
				screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 12);
				h = keyboard.getInt();
				if (h == 'Y' || h == 'y') goto LABEL0;
				else 
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("     FAST CASH TRANSACTION CANCELED ! ", 8);
					screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 10);
					return;
				}
			}
			else // (withdrawnAmount <= cashBox->totalMoney()) 
			{
				if (withdrawnAmount > moneyLeft)
				{
					screen.printInsideFrame("   NOT ENOUGH MONEY IN YOUR ACCOUNT!!\a", 10);
					screen.printInsideFrame("    DO YOU WANT TO CHOOSE AGAIN (Y/N) ?  ", 12);
					int k = keyboard.getInt();
					if (k == 'Y' || k == 'y') goto LABEL0;
					else
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("     FAST CASH TRANSACTION CANCELED ! ", 8);
						screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 10);
						return;
					}
				}
				else  //(withdrawnAmount <= moneyLeft)
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("        FAST CASH SUCCEEDED :)   ", 6);
					screen.printInsideFrame("  ", 8);
					moneyLeft -= withdrawnAmount;

					//LUU NHAT KI GIAO DICH
					saveHistory();
					fprintf(fileDiary, ": %s\n", id.c_str());
					fprintf(fileDiary, ": fast cash: %.2f | ", withdrawnAmount);
					fprintf(fileReceipt, ": fast cash: %.2f | ", withdrawnAmount);
					//*********************

					for (int j = 1; j <= cashBox->getDenominationNumber(); j++) withdrawnMoneyArray[j] = 0;
					for (int j = 1; j <= cashBox->getDenominationNumber(); j++)
					{
						while ((moneyArrayPtr + j)->getDenomination() <= withdrawnAmount && (moneyArrayPtr + j)->getNumber() > 0 && withdrawnAmount > 0)
						{
							withdrawnAmount -= (moneyArrayPtr + j)->getDenomination();
							withdrawnMoneyArray[j]++;
						}
					}

					for (int j = 1; j <= cashBox->getDenominationNumber(); j++)
					{
						screen.dataOut((moneyArrayPtr + j)->getDenomination());
						screen.dataOut("$: ");
						screen.dataOut(withdrawnMoneyArray[j]);
						screen.dataOut("  ");
						if (withdrawnMoneyArray[j] != 0)
						{
							fprintf(fileDiary, "%d x %d $ | ", withdrawnMoneyArray[j], (moneyArrayPtr + j)->getDenomination());
							fprintf(fileReceipt, "%d x %d $ | ", withdrawnMoneyArray[j], (moneyArrayPtr + j)->getDenomination());
						}
					}
					(accountArrayPtr + i)->setBalance(moneyLeft);
					screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 10);

				}
			}
		}
	}
}


void Transaction::withdraw(string id, BankDatabase* bankDatabase, CashBox *cashBox)
{
	Screen screen;
	Keyboard keyboard;
	//Receipt receipt;
	double withdrawnAmount;

	int withdrawnMoneyArray[10]; // array consits of  withdrawn money number;
	
	Money* moneyArrayPtr = cashBox->getMoneyArray();
	Account* accountArrayPtr = bankDatabase->getAccountArray();

	for (int i = 1; i <= bankDatabase->getAccountQuantity(); i++)
	{
		if ((accountArrayPtr + i)->getCardId() == id)
		{
			//
			double moneyLeft = (accountArrayPtr + i)->getBalance();
		LABEL1:
			screen.deleteInsideFrame();
			screen.printInsideFrame("         WITHDRAW TRAMSACTION:", 6);
			screen.printInsideFrame("         ENTER MONEY AMOUNT: ", 8);
			keyboard.dataIn(withdrawnAmount);
			double intPart;  // must use 'modf' because "%" (mod) is olny for int
			double fractPart = modf(withdrawnAmount / 5, &intPart);
			if (fractPart != 0)
			{
				screen.printInsideFrame("    WITHDRAW MUST BE MULTIPLE OF 5 !", 10);
				screen.printInsideFrame("   DO YOU WANT TO ENTER AGAIN (Y/N) ? ", 12);
				int s = keyboard.getInt();
				if (s == 'Y' || s == 'y') {
					screen.deleteInsideFrame();
					//Sleep(200);
					goto LABEL1;
				}
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("       WITHDRAW TRANSACTION CANCELED !", 8);
					screen.printInsideFrame("                 THANK YOU           ", 10);
					screen.printInsideFrame("        CONTINUE TRANSACTION (Y/N) ?  ", 12);
					return;
				}
				//goto LABEL1;

			}
			screen.loading();
			screen.deleteInsideFrame();
			if (withdrawnAmount > cashBox->totalMoney())
			{
				screen.deleteInsideFrame();
				screen.printInsideFrame("   SORRY, NOT ENOUGH MONEY IN ATM!!\a", 10);
				screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 12);
				int h = keyboard.getInt();
				if (h == 'Y' || h == 'y') goto LABEL1;
				else {
					screen.deleteInsideFrame();
					screen.printInsideFrame("     WITHDRAW TRANSACTION CANCELED ! ", 8);
					screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 10);
					return;
				}
			}
			else
			{
				if (withdrawnAmount > moneyLeft)
				{
					screen.printInsideFrame("   NOT ENOUGH MONEY IN YOUR ACCOUNT!!\a", 10);
					screen.printInsideFrame("    DO YOU WANT TO ENTER AGAIN (Y/N) ?  ", 12);
					int k = keyboard.getInt();
					if (k == 'Y' || k == 'y') goto LABEL1;
					else
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("     WITHDRAW TRANSACTION CANCELED !  ", 8);
						screen.printInsideFrame("       CONTINUE TRANSACTION (Y/N) ? ", 10);
						return;
					}
				}
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("       WITHDRAWAL SUCCEEDED :)   ", 6);
					screen.printInsideFrame("  ", 8);
					moneyLeft -= withdrawnAmount;
					
					//LUU NHAT KI GIAO DICH
					saveHistory();
					fprintf(fileDiary, ": %s\n", id.c_str());
					fprintf(fileDiary, ": Witdraw: %.2f | ", withdrawnAmount);
					fprintf(fileReceipt, ": Witdraw: %.2f | ", withdrawnAmount);
					//*********************

					for (int j = 1; j <= cashBox->getDenominationNumber(); j++) withdrawnMoneyArray[j] = 0;
					for (int j = 1; j <= cashBox->getDenominationNumber(); j++)
					{
						while ((moneyArrayPtr + j)->getDenomination() <= withdrawnAmount && (moneyArrayPtr + j)->getNumber() > 0 && withdrawnAmount > 0)
						{
							withdrawnAmount -= (moneyArrayPtr + j)->getDenomination();
							withdrawnMoneyArray[j]++;
						}
					}

					for (int j = 1; j <= cashBox->getDenominationNumber(); j++)
					{
						screen.dataOut((moneyArrayPtr + j)->getDenomination());
						screen.dataOut("$: ");
						screen.dataOut(withdrawnMoneyArray[j]);
						screen.dataOut("  ");
						if (withdrawnMoneyArray[j] != 0)
						{
							fprintf(fileDiary, "%d x %d $ | ",  withdrawnMoneyArray[j], (moneyArrayPtr + j)->getDenomination() );
							fprintf(fileReceipt, "%d x %d $ | ", withdrawnMoneyArray[j], (moneyArrayPtr + j)->getDenomination());
						}
					}
					(accountArrayPtr + i)->setBalance(moneyLeft);
					screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 10);
					
				}
			}
		}

	}

}

void Transaction::transfer(string id, BankDatabase* bankDatabase)
{
	//.....
	Screen screen;
	Keyboard keyboard;
	CardReader cardReader;
	
	Account* accountArrayPtr = bankDatabase->getAccountArray();

	for (int i = 1; i <= bankDatabase->getAccountQuantity(); i++)
	{
		if ((accountArrayPtr + i)->getCardId() == id)
		{
			string receiver;
		LABEL1:
			screen.deleteInsideFrame();
			screen.printInsideFrame("  GIVE CARD ID OF RECEIVER: ", 6);
			keyboard.dataIn(receiver);
			if (receiver == id)
			{
				screen.printInsideFrame("   CANNOT TRANSFER TO YOUR ACCOUNT !", 8);
				screen.printInsideFrame("  CONTINUE OR CANCEL TRANSACTION (Y/N) ? ", 10);
				int z = keyboard.getInt();
				if (z == 'Y' || z == 'y') {
					goto LABEL1;
				}
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("	    YOU CANCELED TRANSFER !     ", 10);
					screen.printInsideFrame("       CONTINUE OR NOT (Y/N) ? ", 12);
					return;
				}
				
			}
			for (int j = 1; j <= bankDatabase->getAccountQuantity(); j++)
			{
				if ((accountArrayPtr + j)->getCardId() == receiver)
				{
				LABEL2:
					screen.deleteInsideFrame();
					//Sleep(50);
					screen.printInsideFrame("    ENTER TRANSFER AMOUNT: ", 8);
					double transferAmount;
					keyboard.dataIn(transferAmount);
					if (transferAmount > (accountArrayPtr + i)->getBalance())
					{
						screen.printInsideFrame("    YOU DON NOT HAVE ENOUGH MONEY !!!", 10);
						screen.printInsideFrame("     CONTINUE TRANSACTION (Y/N) ? ", 12);
						int z = keyboard.getInt();
						if (z == 'Y' || z == 'y') goto LABEL2;
						else
						{
							screen.deleteInsideFrame();
							screen.printInsideFrame("	  YOU CANCELED TRANSFER !", 10);
							screen.printInsideFrame("      CONTINUE OR NOT (Y/N) ? ", 12);
							return;
						}

					}
					else  //(transferAmount <= (accountArrayPtr + i)->getBalance())
					{
						screen.loading();
						screen.deleteInsideFrame();
						screen.printInsideFrame("     TRANSACTION SUCCEEDED !!!", 10);
						screen.printInsideFrame("     CONTINUE OR NOT (Y/N)) ? ", 12);
						(accountArrayPtr + i)->setBalance((accountArrayPtr + i)->getBalance() - transferAmount);
						(accountArrayPtr + j)->setBalance((accountArrayPtr + j)->getBalance() + transferAmount);
						bankDatabase->updateAccount();

						// tramsaction history ????? 
						saveHistory();
						fprintf(fileDiary, ": %s\n", id.c_str());
						fprintf(fileDiary, ": Transfer to %s : %.2f $", receiver.c_str(), transferAmount);
						fprintf(fileReceipt, ": Transfer to %s : %.2f $", receiver.c_str(), transferAmount);
						return;
					}
				}

			}

			screen.loading();
			screen.deleteInsideFrame();
			screen.printInsideFrame("    NO SUCH ACCOUNT FOUND !!!", 8);
			screen.printInsideFrame("    CONTINUE OR CANCEL (Y/N) ? ", 10);
			int s = keyboard.getInt();
			if (s == 'Y' || s == 'y') {
				goto LABEL1;
			}
			else
			{
				screen.printInsideFrame("	  YOU CANCELED TRANSFER !", 8);
				screen.printInsideFrame("    CONTINUE OR CANCEL (Y/N) ? ", 10);
				return;
			}

		}
	}
}

void Transaction::saveHistory()
{
	time_t rawtime;
	time(&rawtime);
	char str[26];
	ctime_s(str, sizeof(str), &rawtime);
	fprintf(fileDiary, "\n\nTime %s", str);
	fprintf(fileReceipt, "\n\nTime %s", str);
}