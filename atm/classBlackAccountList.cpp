#include "stdafx.h"
using namespace std;

typedef std::vector<BlackAccountObserver*>::iterator BAObserverI;

BlackAccountList::BlackAccountList()
{
	//shared_ptr<BlackAccountObserver> blackAccountObserver(new BlackAccountObserver()) ;
	BlackAccountObserver* blackAccountObserver = new BlackAccountObserver();
	blockState = 0;
	ifstream fBlkAcc("ClientAccount.txt");  //read from file
	//int i = 0;
	string id, pin;
	double balance;
	int blockState;
	if (fBlkAcc.is_open())
	{
		while (!fBlkAcc.eof())
		{
			//i++;
			fBlkAcc >> blockState >> id >> pin >> balance;
			if (blockState == 1)
			{
				blackAccountObserver->setPin(pin);
				blackAccountObserver->setCardId(id);
				blackAccountObserver->setBalance(balance);
				blackAccountObserver->setBlockState(blockState);
				observers.push_back(new BlackAccountObserver(*blackAccountObserver)); // array of pointer
			}
			
		}
		fBlkAcc.close();
		delete blackAccountObserver;
	}
	/*
	else
	{
		screen.printInsideFrame("      DATABASE NOT FOUND !\a\a\a\a\a", 8);
		Sleep(3000);
		screen.printInsideFrame("         SEE YOU AGAIN :)   ", 12);
		Sleep(2000);
		//system("pause");
		exit(0); //break the whole program
	}
	*/

}

void BlackAccountList::attachAccount(BlackAccountObserver* blackAccountObserver)
{
	observers.push_back(blackAccountObserver);
}

void BlackAccountList::detachAccount(BlackAccountObserver* blackAccountObserver)
{
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		if ((*it) = blackAccountObserver)
		{
			swap(*it, observers.back());
			observers.pop_back();
			break;
		}
	}
	//
	//observers.erase(remove( observers.begin(), observers.end(), blackAccountObserver), observers.end() );
}

void BlackAccountList::detachAllAccount()
{
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		delete *it;
	}
	observers.clear();
}

void BlackAccountList::notify()
{
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		(*it)->update(this); // pointer it point to a pointer of BlackAccountObserver
	}
}


int BlackAccountList::getBlockState()
{
	return blockState;
}

void BlackAccountList::setBlockStateAll(int _blockState)
{
	blockState = _blockState;
	notify();
}

void BlackAccountList::printf()
{
	ofstream fBlkAcc("BlackAccount.txt", ios::out);  //write to file
	if (!observers.empty() )
	{
		for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
		{
			fBlkAcc << (*it)->getBlockState() << " " << (*it)->getCardId() << " " << (*it)->getPin() << " " << fixed << setprecision(2) << (*it)->getBalance() << endl;
		}
	}

	fBlkAcc.close();
}

vector<BlackAccountObserver*> BlackAccountList::getObservers()
{
	return observers;
}

bool BlackAccountList::check(string id)
{
	//bool inside = false;
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		if ((*it)->getCardId() == id)
		{
			//inside = true;
			if ((*it)->getBlockState() == 1)
				return true;
		}
	}
	return false;
}

void BlackAccountList::removeAccount(string id)
{
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		if ((*it)->getCardId() == id)
		{
			detachAccount(*it);
			break;
		}
	}

}

void BlackAccountList::setBlockStateOfAccount(string id, int blockState)
{
	for (BAObserverI it = observers.begin(); it != observers.end(); ++it)
	{
		if ((*it)->getCardId() == id)
		{
			(*it)->setBlockState(blockState);
			break;
		}
	}
}