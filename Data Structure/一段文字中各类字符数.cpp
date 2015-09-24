#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char article[10][80];
	int i,j,k,num=0,character=0,space=0,other=0,all=0;
	for (i=0;i<10;++i){
		cin.getline(article[i],80);
	}
	for (i=0;i<10;++i){
		k=strlen(article[i]);
		for (j=0;j<k;++j){
			if (article[i][j]=='\0') break;
			if (article[i][j]==' ') ++space;
			if (article[i][j]<='9'&&article[i][j]>='0') ++num;
			if (article[i][j]>='a' && article[i][j]<='z' || article[i][j]>='A' && article[i][j]<='Z') ++character;
			++all;
		}
	}
	other=all-num-space-character;
	cout<<"字符数为"<<character<<"\n数字数为"<<num<<"\n空格数为"<<space<<"\n其他字符为"<<other<<endl;
	return 0;
}