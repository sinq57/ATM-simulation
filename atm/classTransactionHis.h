#pragma once


class TransactionHistory
{
public:
	TransactionHistory();
	TransactionHistory(FILE* , FILE* );
	void saveTransaction();
private:
	FILE *fileDiary;
	FILE *fileReceipt;
};