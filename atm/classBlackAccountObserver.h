#pragma once
#include "stdafx.h"


class BlackAccountList;

/*
class Observer
{
public:
	virtual void update(BlackAccountList * blackAccountList) = 0;
};
*/

class BlackAccountObserver : public Account
{
public:
	BlackAccountObserver(const BlackAccountObserver& blackAccountObserver);
	BlackAccountObserver(const Account & account);
	BlackAccountObserver();
	void update(BlackAccountList *);
	//int getBlockState();
};