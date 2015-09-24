#include <iostream>
using namespace std;
int main()
{
	int num,result,mod,count=1;
	char *ulti;
	cout<<"请输入要转化的数字"<<endl;
	cin>>num;
	result=num;
	while (result/10){
		result/=10;
		++count;
	}
	ulti=new char[count+1];
	for (int i=0;i<count;++i){
		mod=num%10;
		num/=10;
		ulti[count-i-1]=mod+'0';
	}
	ulti[count]='\0';
	cout<<ulti<<endl;
	delete [] ulti;
	return 0;
}