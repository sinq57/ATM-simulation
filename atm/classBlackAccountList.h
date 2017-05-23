#pragma once
//#include "stdafx.h"
using namespace std;

class BlackAccountObserver;
//class BlackAccountList
class BlackAccountList
{
public:
	BlackAccountList();
	void attachAccount(BlackAccountObserver* blackAccountObserver);
	void detachAccount(BlackAccountObserver* blackAccountObserver);
	void detachAllAccount();
	void notify();
	void printf();
	int getBlockState();
	void setBlockStateAll(int);
	void removeAccount(string id);
	bool check(string id);
	void setBlockStateOfAccount(string id, int blockState);
	vector<BlackAccountObserver*> getObservers();
	~BlackAccountList();
private:
	vector<BlackAccountObserver*> observers;
	int blockState;  // '1': blocked

};