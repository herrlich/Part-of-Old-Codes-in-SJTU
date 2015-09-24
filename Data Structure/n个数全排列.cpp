#include <iostream>
#include <cstring>
using namespace std;
void getarranged(char str[],int k);
void arrange(char str[]);
void swap(char str[],int k,int i);
#define MAX 10
int main()
{
	char str[MAX];
	cout<<"ÇëÊäÈë×Ö·û´®"<<endl;
	cin>>str;
	arrange(str);
	return 0;
}
void getarranged(char str[],int k)
{
	int i;
	if (k==strlen(str)) cout<<str<<endl;
	else{
		for (i=k;i<strlen(str);++i){
			swap(str,k,i);
			getarranged(str,k+1);
			swap(str,i,k);
		}
	}
}
void swap(char str[],int k,int i)
{
	char temp;
	temp=str[i];
	str[i]=str[k];
	str[k]=temp;
}
void arrange(char str[])
{
	getarranged(str,0);
}