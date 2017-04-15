#include "stdafx.h"
using namespace std;

Bill::Bill()
{
	

}

void Bill::print()
{
	Screen screen;
	int count = 0;
	char a[1000];
	screen.loading();
	screen.clearScreen();
	ifstream f_in("BillBuffer.txt");   // 
	while (!f_in.eof()) {
		f_in.getline(a, 1000);
		count++;
	}
	f_in.close();
	if (count == 2) screen.dataOut("\n\n                                No transaction\n\n");
	else {
		screen.dataOut("\n\n                                 Transation Bill\n\n");
		screen.dataOut("\n");
		ifstream f_in("BillBuffer.txt");
		f_in.getline(a, 10000);
		while (!f_in.eof()) {
			f_in.getline(a, 10000);
			screen.dataOut("     ");
			screen.dataOut(a);
			screen.dataOut("\n");
		}
		f_in.close();
	}
}