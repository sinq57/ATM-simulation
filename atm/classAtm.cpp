#include "stdafx.h"
using namespace std;

Atm::Atm()
{

}

Atm::Atm(FILE* fDiary, FILE* fReceipt) : transactionHistory(fDiary, fReceipt), transaction(fDiary, fReceipt), bankDatabase(fDiary, fReceipt) //, keyboard(), screen(), cardReader(),
{
}

BankDatabase* Atm::getBankDatabase()
{
	return &bankDatabase;
}

CashBox* Atm::getCashBox()
{
	return &cashBox;
}

void Atm::run()
{
	screen.makeBackgroundColor();
	bankDatabase.createAccountArray();
	cashBox.makeMoneyArray();
	screen.dataOut("\n\n\n\n\n\n\n");
	char introduction[100] = "\n\n                     WELCOM TO ATM SYSTEM OF WBK S.A. BANK ";
	for (int i = 0; i < strlen(introduction); i++) {
		screen.dataOut(introduction[i]);
		Sleep(30);
	}
	Sleep(1500);
	screen.clearScreen();
	
	while (1)
	{
		Keyboard keyboard;
		screen.initialdisplay();
		screen.makeBackgroundColor();
	INITIAL:
		screen.printInsideFrame("    WBK BANK - WHERE YOUR TRUST IS HOLD   ", 6);
		screen.printInsideFrame("               PLEASE CHOOSE: ", 8);
		screen.printInsideFrame("        1: BANK EMPLOYEE   2: CLIENT ", 10);
		int m = keyboard.getChar();
		if (m == '1')
		{
			int tryNo = 3; string pwd;

			screen.deleteInsideFrame();
			screen.printInsideFrame("     PLEASE ENTER PASSWORD: ", 8);
		PASSWORDAGAIN:
			/*
			for (int j = 1; j <= 6; j++) {
				char i = keyboard.getChar();
				screen.dataOut("*");
				pwd += i;
			}
			keyboard.getInt(); //press Enter after pwd
			*/
			pwd = keyboard.enterPassword();
			if (pwd != "wbkwro")
			{
				tryNo--;
				if (tryNo == 0)
				{
					//No more try
					screen.deleteInsideFrame();
					screen.printInsideFrame("\a       TRY LIMIT REACHED, NO MORE !   ", 6);
					screen.printInsideFrame("     REMEMBER PWD IF WANT TO KEEP WORK !", 8);
					screen.printInsideFrame("                 GOODBYE :)", 10);
					Sleep(2000);
					return;
				}
				else
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("\a            WRONG PASSWORD !!!         ", 6);
					screen.printInsideFrame("  	         TRYTIME LEFT: ", 8);
					screen.dataOut(tryNo);
					screen.printInsideFrame("         CONTINUE OR CANCEL (Y/N) ? ", 10);
					int g = keyboard.getInt();
					if (g == 'N' || g == 'n')
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("                 GOODBYE :)", 10);
						Sleep(2000);
						return;
					}
					else {
						screen.deleteInsideFrame();
						screen.printInsideFrame("  PLEASE ENTER PASSWORD AGAIN: ", 8);
						goto PASSWORDAGAIN;
					}
				}

			}

		INITIAL1:
			screen.deleteInsideFrame();
			screen.printInsideFrame("               PLEASE CHOOSE: ", 8);
			screen.printInsideFrame("   1: UNBLOCK ALL   2: CONCRETE UNBLOCK", 10);
			int r = keyboard.getChar();
			if (r == '1')
			{
				screen.loading();
				// file handling *******
				blackAccountList.setBlockStateAll(0);
				
				bankDatabase.actualizeBlackAccount(blackAccountList.getObservers());
				blackAccountList.printf();
				//***************************
				screen.deleteInsideFrame();
				screen.printInsideFrame("         UNBLOCK SUCCESSFULLY !", 8);
				screen.printInsideFrame("                THANK YOU     ", 10);
				Sleep(1500);
				return;
			}
			else if (r == '2')
			{
				string id;
			ENTERBLOCKEDID:
				screen.deleteInsideFrame();
				screen.printInsideFrame("     ENTER 12-DIGIT BLOCKED CARD ID :", 8);
				screen.printInsideFrame("              ", 10);
				keyboard.dataIn(id);
				if (blackAccountList.check(id) == true)
				{
					//blackAccountList.removeAccount(id);
					//bankDatabase.unblockAccount(id);
					blackAccountList.setBlockStateOfAccount(id,0);
					bankDatabase.unblockAccount(id);
					bankDatabase.actualizeBlackAccount(blackAccountList.getObservers());
					blackAccountList.printf();
					screen.loading();
					screen.deleteInsideFrame();
					screen.printInsideFrame("          UNBLOCK SUCCESSFULLY !", 8);
					screen.printInsideFrame("        CONTINUE OR EXIT ? (Y/N) ", 10);
					int v = keyboard.getInt();
					if (v == 'Y' || v == 'y') {
						goto INITIAL1;
					}
					else {
						screen.deleteInsideFrame();
						screen.printInsideFrame("           THANK YOU AND GOODBYE !     ", 8);
						Sleep(2000);
						return;
					}

				}
				else // false
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("          NO BLOCKED CARD FOUND !!!\a\a\a", 8);
					screen.printInsideFrame("        ENTER AGIAN OR EXIT ? (Y/N) ", 10);
					int q = keyboard.getInt();
					if (q == 'Y' || q == 'y') {
						goto ENTERBLOCKEDID;
					}
					else {
						screen.deleteInsideFrame();
						screen.printInsideFrame("           THANK YOU AND GOODBYE !     ", 8);
						Sleep(2000);
						return;
					}
				}
			}
			else // m != 1, 2
			{
				screen.deleteInsideFrame();
				screen.printInsideFrame("           WRONG! PLEASE CHOOSE AGAIN ", 8);
				Sleep(1500);
				goto INITIAL1;
			}
			return;
		}
		else if (m == '2')
		{
			int tryTime = 3;
			//screen.display("                                          ", "                                          ");  // 42 space
			
			screen.deleteInsideFrame();
			screen.printInsideFrame("    WBK BANK - WHERE YOUR TRUST IS HOLD   ", 6);
			screen.printInsideFrame("                 ... insert card to start", 14);
			 m = keyboard.getChar();
			//keyboard.dataIn(m);
			//Sleep(100);
			cardReader.display("|    CARD IN     |\n");  //18 CHARACTERS
			screen.deleteInsideFrame();
			screen.printInsideFrame("	 PLEASE LOG IN TO SYSTEM        ", 6);
			string id;
			do
			{
				//login and check pin
				screen.printInsideFrame("  ENTER 12-DIGIT CARD ID: ", 8);
				keyboard.dataIn(id);
				if (bankDatabase.ifAccountCreated(id) == false)
				{
					screen.printInsideFrame("\a           ACCOUNT NOT FOUND       ", 10);
					screen.printInsideFrame("      ENTER AGAIN OR CANCEL (Y/N) ? ", 12);
					int f = keyboard.getInt();
					if (f == 'Y' || f == 'y') {
						screen.deleteInsideFrame();
						screen.printInsideFrame("	PLEASE LOG IN TO SYSTEM   ", 6);
					}
					else {
						screen.deleteInsideFrame();
						screen.printInsideFrame("     THANK YOU FOR USING OUR SEVICES    ", 8);
						screen.printInsideFrame("        GOODBYE AND SEE YOU AGAIN       ", 10);
						cardReader.display("|    CARD OUT    |\n");  //18 CHARACTERS
						//bill.print();
						//f_hoadon.close();
						Sleep(2000);
						return;
					}
				}
				else break;
			} while (bankDatabase.ifAccountCreated(id) == false);

			//f_diary << "\n\n" << ten << endl;
			//f_hoadon << ten << endl;

		STARTAGAIN:
			string pin = "";
			screen.printInsideFrame("     ENTER 6-DIGIT PIN: ", 10);
			/*
			for (int j = 1; j <= 6; j++) {
				char i = keyboard.getChar();
				screen.dataOut("*");
				pin += i;
			}
			keyboard.getInt(); //press Enter after pin

			*/
			pin = keyboard.enterPassword();
			screen.loading();
			if (bankDatabase.checkPin(id, pin))
			{
				for (int i = 1; i <= bankDatabase.getAccountQuantity(); i++)
				{
					if ((bankDatabase.getAccountArray() + i)->getCardId() == id)
					{
						if ((bankDatabase.getAccountArray() + i)->getBlockState() == 1)
						{
							screen.deleteInsideFrame();
							screen.printInsideFrame("\a	  YOUR ACCOUNT WAS BLOCKED !   ", 6);
							screen.printInsideFrame("   CONTACT WBK BANK FOR INFORMATION   ", 8);
							screen.printInsideFrame("                THANK YOU !            ", 10);
							cardReader.display("| CARD SWALLOWED |\n");
							//f_hoadon.close();
							//bill.print();
							return;
						}
					}
				}
				screen.deleteInsideFrame();
				screen.printInsideFrame("           LOG IN SUCCEEDED !      ", 8);
				screen.printInsideFrame("          WELCOM TO WBK BANK !  ", 10);
				cardReader.display("| CARD ACCEPTED  |\n");
				//Sleep(1500);


				screen.deleteInsideFrame();
			LABEL:
				screen.printInsideFrame("      PLEASE CHOOSE TRANSACTION:  ", 9);
				int n = keyboard.getInt();
				switch (n)
				{
				case '1':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             WITHDRAW TRANSACTION ", 6);
					//bankDatabase.withdraw(id, cashBox);
					Sleep(1000);
					transaction.withdraw(id, getBankDatabase(), getCashBox());
					break;
				}
				case '2':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             MONEY TRANSFER          ", 6);
					//bankDatabase.transfer(id);
					Sleep(1000);
					transaction.transfer(id, getBankDatabase());
					break;
				}
				case '3':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             PAYMENT TOOLS          ", 6);
					Sleep(1000);
					transaction.payTool(id, getBankDatabase());
					break;
				}
				case '4':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             MOBILE POPUP          ", 6);
					Sleep(1000);
					transaction.mobilePopup(id, getBankDatabase());
					break;
				}
				case '5':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             CHECK BALANCE          ", 6);
					Sleep(1000);
					bankDatabase.checkBalance(id);
					break;
				}
				case '6':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             CHANGE PIN             ", 6);
					Sleep(1000);
					bankDatabase.changePin(id);
					break;
				}
				case '7':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("             FAST CASH              ", 6);
					Sleep(1000);
					transaction.fastCash(id, getBankDatabase(), getCashBox());
					break;
				}
				case '0':
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("     THANK YOU FOR USING OUR SEVICES    ", 8);
					screen.printInsideFrame("        GOODBYE AND SEE YOU AGAIN       ", 10);
					cardReader.display("|    CARD OUT    |\n");  //18 CHARACTERS
					//f_hoadon.close();
					//hoaDon.inHoaDon();
					return;
				}
				default:
				{
					screen.printInsideFrame("\a  WRONG! CHOOSE AGAIN OR CANCEL (Y/N) ? ", 12);
					int zz = keyboard.getInt();
					if (zz == 'Y' || zz == 'y') {
						screen.deleteInsideFrame();
						Sleep(200);
						goto LABEL;
					}
					else {
						screen.deleteInsideFrame();
						screen.printInsideFrame("     THANK YOU FOR USING OUR SEVICES    ", 8);
						screen.printInsideFrame("        GOODBYE AND SEE YOU AGAIN       ", 10);
						cardReader.display("|    CARD OUT    |\n");  //17 CHARACTERS
						//bill.print();
						//f_hoadon.close();

						Sleep(2000);
						return;
					}

				}

				}

				// here we must check the key (y/n) entered from keyboard 
				//because every transaction just finishes with the question "continue transaction or cancel (y/n) ?" 
				int c = keyboard.getInt();
				if (c == 'Y' || c == 'y') {
					screen.deleteInsideFrame();
					//Sleep(200);
					goto LABEL;
				}
				else {
					screen.deleteInsideFrame();
					screen.printInsideFrame("     DO YOU WANT TO PRINT BILL ??? : ", 8);
					c = keyboard.getInt();
					if (c == 'Y' || c == 'y') {
						//screen.deleteInsideFrame();
						//***************************************************
						// print bill
						//**************************************************
					}
					else
					{

					}
					screen.deleteInsideFrame();
					screen.printInsideFrame("     THANK YOU FOR USING OUR SEVICES    ", 8);
					screen.printInsideFrame("        GOODBYE AND SEE YOU AGAIN       ", 10);
					cardReader.display("|    CARD OUT    |\n"); //17 CHARACTERS
					//bill.print();
					//f_hoadon.close();

					Sleep(2000);
					break;
				}


			}
			else // bankDatabase.checkPin(id, pin) = false
			{
				tryTime--;
				if (tryTime == 0)
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("\a TRY LIMIT REACHED, YOUR CARD IS BLOCKED!", 6);
					screen.printInsideFrame("   CONTACT WBK BANK FOR INFORMATION   ", 8);
					screen.printInsideFrame("                THANK YOU !            ", 10);
					cardReader.display("| CARD SWALLOWED |\n");
					for (int i = 1; i <= bankDatabase.getAccountQuantity(); i++)
					{
						if ((bankDatabase.getAccountArray() + i)->getCardId() == id)
						{
							(bankDatabase.getAccountArray() + i)->setBlockState(1);
							//*******************************************
							blackAccountList.attachAccount(new BlackAccountObserver(*(bankDatabase.getAccountArray() + i)));
							//*******************************************
							bankDatabase.updateAccount();
							break;
						}
					}
					screen.dataOut("\n\n\n");
					break;
				}
				else //tryTime != 0 and bankDatabase.checkPin(id, pin) = false
				{
					screen.deleteInsideFrame();
					screen.printInsideFrame("\a               WRONG PIN !!!        ", 6);
					screen.printInsideFrame("  	           TRYTIME LEFT: ", 8);
					screen.dataOut(tryTime);
					screen.printInsideFrame("         CONTINUE OR CANCEL (Y/N) ? ", 10);
					int g = keyboard.getInt();
					if (g == 'N' || g == 'n')
					{
						screen.deleteInsideFrame();
						screen.printInsideFrame("     THANK YOU FOR USING OUR SEVICES    ", 8);
						screen.printInsideFrame("        GOODBYE AND SEE YOU AGAIN       ", 10);
						cardReader.display("|    CARD OUT    |\n"); //17 CHARACTERS

						//f_hoadon.close();
						//hoaDon.inHoaDon();
						return;
					}
					else {

						screen.deleteInsideFrame();
						screen.printInsideFrame("       PLEASE ENTER PIN AGAIN :)    ", 8);
						goto STARTAGAIN;
					}
				}
			}
		}
		else
		{
			screen.deleteInsideFrame();
			screen.printInsideFrame("           WRONG! PLEASE CHOOSE AGAIN",8);
			Sleep(1500);
			goto INITIAL;
		}
	}
	//f_hoadon.close();
	//hoaDon.inHoaDon();

}

BlackAccountList* Atm::getBlackAccountList()
{
	return &blackAccountList;
}