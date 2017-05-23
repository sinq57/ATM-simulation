#include "stdafx.h"
using namespace std;

Receipt::Receipt()
{

}

Receipt::Receipt(FILE* fReceipt)
{
	fileReceipt = fReceipt;
}

void Receipt::print()
{
	Screen screen;
	int count = 0;
	char a[100];
	//screen.loading();
	//screen.clearScreen();
	screen.goToXY( 54, 22); // 68
	screen.dataOut("|____________|");
	Sleep(500);
	screen.goToXY(54, 22);// 68
	screen.dataOut("|  - bill - |");
	screen.goToXY(54, 23); // 68
	screen.dataOut("|____________|");
	Sleep(500);
	screen.goToXY(54, 22); // 68
	screen.dataOut("|  - your -  |");
	screen.goToXY(54, 23); // 68
	screen.dataOut("|  - bill -  |");
	screen.goToXY(54, 24); // 68
	screen.dataOut("|____________|");

	screen.goToXY(1,30);
	fseek(fileReceipt, 0, SEEK_SET); // seek to beginning of file
	while (fgets(a, 100, fileReceipt) != NULL)
	{
		count++;
	}
	if (count == 0) screen.dataOut("\n\n                                No transaction\n\n");
	else {
		screen.dataOut("\n\n                                 Transation Receipt\n\n");
		screen.dataOut("\n");
		fseek(fileReceipt, 0, SEEK_SET); // seek to beginning of file
		if (fileReceipt)
		{
			while  (fgets(a, 100, fileReceipt) != NULL )
			{
				screen.dataOut("                         ");
				screen.dataOut(a);
				screen.dataOut("\n");
			}
		}
	}
	return;
}