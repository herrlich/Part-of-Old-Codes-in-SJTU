#include <iostream>
using namespace std;
void print(int x,int base);
const char digit[17]="0123456789abcdef";
int main()
{
	int num,base;
	cout<<"������һ��������"<<endl;
	cin>>num;
	cout<<"���������"<<endl;
	cin>>base;
	print(num,base);
	cout<<endl;
	return 0;
}
void print(int num,int base)
{
	if (num<base) cout<<digit[num];
	else{
		print (num/base,base);
		cout<<digit[num%base];
	}
}