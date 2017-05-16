#include "stdafx.h"
//using namespace std;

BlackAccountObserver::BlackAccountObserver()
{

}

BlackAccountObserver::BlackAccountObserver(const BlackAccountObserver& blackAccountObserver)
{
	blockState = blackAccountObserver.blockState;
	cardId = blackAccountObserver.cardId;
	pin = blackAccountObserver.pin;
	balance = blackAccountObserver.balance;
}

BlackAccountObserver::BlackAccountObserver(const Account& account)
{
	blockState = account.getBlockState();
	cardId = account.getCardId();
	pin = account.getPin();
	balance = account.getBalance();
}

void BlackAccountObserver::update(BlackAccountList * blackAccountList) 
{
	blockState = blackAccountList->getBlockState();
}
