// atm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//ofstream f_acc("ClientAccount.txt");
using namespace std;
int main()
{
	//fstream f_diary;   //("NhatKiGiaoDich.txt", ios::out | ios::in | ios::app);
	//ofstream f_hoadon; //("LuuTamHoaDon.txt");
	FILE *fileDiary;
	FILE *fileReceipt;
	fopen_s(&fileDiary,"TransactionDiary.txt", "a+"); //a+
	fopen_s(&fileReceipt,"ReceiptBudffer.txt", "w+");

	Atm atm(fileDiary, fileReceipt);
	atm.run();
	fclose(fileDiary);
	fclose(fileReceipt);
	atm.getBlackAccountList()->printf();
	Sleep(1000);
	//f_acc.close();
	return 0;
}

