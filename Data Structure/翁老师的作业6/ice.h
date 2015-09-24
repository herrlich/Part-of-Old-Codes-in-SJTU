#ifndef _head_h
#define _head_h
#include <iostream>
using namespace std;
class Account{
protected:
	double total;
public:
	Account() {total=0;}
	int saveMoney(double d);// success:return 0; Fail: return -1;
	int takeMoney(double d);
	double check();
};
class SavingAccount:public Account{
private:
	double interestperyear,interest;
public:
	SavingAccount(double interestPerYear); 
	double calInterest(int year); 
	int addInterest(int year);
};
class CheckingAccount:public Account{
private:
	double Percent;
public:
	CheckingAccount(double percentage);
	int saveMoney(double d); 
	int takeMoney(double d);
};
#endif