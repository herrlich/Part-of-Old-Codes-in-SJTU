#include <iostream>
using namespace std;
int main()
{
	char sentence[80];
	int i=0,space=0,num=0,yuan=0,fu=0,other=0,ch=0;
	cout<<"���������"<<endl;
	cin.getline(sentence,80,'.');
	for (i=0;sentence[i]!='\0';++i){
		if ((sentence[i]>='a'&&sentence[i]<='z')||(sentence[i]>='A'&&sentence[i]<='Z')) ch+=1;
		if (sentence[i]=='a'||sentence[i]=='e'||sentence[i]=='i'||sentence[i]=='o'||sentence[i]=='u'||sentence[i]=='A'||sentence[i]=='E'||sentence[i]=='I'||sentence[i]=='O'||sentence[i]=='U') yuan+=1;
		if (sentence[i]==' ') space+=1;
		if (sentence[i]<='9'&&sentence[i]>='0') num+=1;
	}
	fu=ch-yuan;
	other=i-ch-space-num;
	cout<<"Ԫ��"<<yuan<<endl;
	cout<<"����"<<fu<<endl;
	cout<<"����"<<num<<endl;
	cout<<"�ո�"<<space<<endl;
	cout<<"�����ַ�"<<other<<endl;
	return 0;
}