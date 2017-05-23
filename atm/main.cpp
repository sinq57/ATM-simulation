// atm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
int main()
{
	FILE *fileDiary;
	FILE *fileReceipt;
	fopen_s(&fileDiary,"TransactionDiary.txt", "a+"); //a+
	fopen_s(&fileReceipt,"ReceiptBuffer.txt", "w+");

	Atm atm(fileDiary, fileReceipt);
	atm.run();
	fclose(fileDiary);
	fclose(fileReceipt);

	atm.getBlackAccountList()->printf();
	Sleep(1000);
	
	return 0;
}

