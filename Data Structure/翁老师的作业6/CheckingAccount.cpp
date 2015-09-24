#include "ice.h"
CheckingAccount::CheckingAccount(double percentage){
	Account();
	Percent=percentage;
}
int CheckingAccount::saveMoney(double d){
	if (total+d>=Percent*d){
		total=total+d-Percent*d;
		return 0;
	}
	else return -1;
}
int CheckingAccount::takeMoney(double d){
	if (total>=Percent*d){
		total=total-d-Percent*d;
		return 0;
	}
	else return -1;
}