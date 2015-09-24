#include "ice.h"
SavingAccount::SavingAccount(double interestPerYear){
	Account();
	interestperyear=interestPerYear;
}
double SavingAccount::calInterest(int year){
	interest=total*interestperyear*year;
	return interest;
}
int SavingAccount::addInterest(int year){
	total+=interest;
	return 0;
}