#include "ice.h"
int main(){
	Account r1;
	r1.saveMoney(100);
	cout<<r1.check()<<endl;
	r1.takeMoney(20);
	cout<<r1.check()<<endl;
	SavingAccount r2(0.05);
	r2.saveMoney(1000);
	r2.calInterest(10);
	r2.addInterest(10);
	cout<<r2.check()<<endl;
	r2.takeMoney(3000);
	r2.takeMoney(200);
	cout<<r2.check()<<endl;
	CheckingAccount r3(0.01);
	r3.saveMoney(10000);
	cout<<r3.check()<<endl;
	r3.takeMoney(2000);
	cout<<r3.check()<<endl;
	return 0;
}