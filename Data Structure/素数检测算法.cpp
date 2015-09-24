#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int TRIALS=5;
long int witness(long int a,long int i,long int p);//计算a^i mod p
bool isPrime(long int p){//检测p是否为素数
	srand(time(0));
	//随机选择TRIALS个大于1且小于p的随机数a，计算a^i mod p
	for (int counter=0;counter<TRIALS;counter++)
		if (witness(rand()*(p-2)/RAND_MAX+2,p-1,p)!=1)
			return false;
	return true;
}
long int witness(long int a,long int i,long int p){
	if (i==0) return 1;
	long int x=witness(a,i/2,p);
	if (x==0) return 0;
	long int y=(x*x)%p;
	if (y==1&&x!=1&&x!=p-1) return 0;
	if (i%2!=0) y=(a*y)%p;
	return y;
}
int main(){
	long int x;
	cout<<"请输入要检验的数"<<endl;
	cin>>x;
	cout<<(isPrime(x)?"true":"false")<<endl;
	return 0;
}