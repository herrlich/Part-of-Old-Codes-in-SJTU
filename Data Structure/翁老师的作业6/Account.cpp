#include "ice.h"
int Account::saveMoney(double d){
	if (d>0){
		total+=d;
		return 0;
	}
	else return -1;
}
int Account::takeMoney(double d){
	if (d>0&&d<total){
		total-=d;
		return 0;
	}
	else return -1;
}
double Account::check(){
	return total;
}