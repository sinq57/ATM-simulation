#include "stdafx.h"
using namespace std;

//extern ofstream f_history;
//extern ofstream f_bill;
TransactionHistory::TransactionHistory()
{
}

TransactionHistory::TransactionHistory(FILE* diary, FILE* receipt)
{
	fileDiary = diary;
	fileReceipt = receipt;
}

void TransactionHistory::saveTransaction()
{
	time_t rawtime;
	time(&rawtime);
	char str[26];
	ctime_s(str, sizeof(str), &rawtime);
	fprintf(fileDiary, "\n\nTime %s ", str);
	fprintf(fileReceipt, "\n\nTime %s ", str);
	//cout << "Time " << str << ": ";
	//cout << "Time " << str << ": ";
}