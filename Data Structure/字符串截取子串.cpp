#include <iostream>
#include <cstring>
using namespace std;
char *Substr(char *a,int start,int end);
char *Substr(char *a,int start,int end)
{
	int len=strlen(a);
	if (start<0 || start>=len || end<start || end<0 || end>=len){
		cout<<"wrong input"<<endl;
		return NULL;
	}
	char *sub=new char [end-start+2];
	strncpy(sub,a+start,end-start+1);
	sub[end-start+1]='\0';
	return sub;
}
int main()
{
	cout<<Substr("hellosfdfhkdjhaskjf",2,13)<<endl;
	delete [] Substr("hellosfdfhkdjhaskjf",2,13);
	return 0;
}