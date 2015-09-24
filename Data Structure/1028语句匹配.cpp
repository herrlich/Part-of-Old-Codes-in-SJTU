//最要命的地方：此函数不允许这个输入（找了好久。。。）：if then begin if then end else else
//好像也不能用cin.ignore()......不记得了
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	int n,i,ifn=0,elsen=0,beginn=0,thenn=0,endn=0,IF[100],ELSE[100],BEGIN[100],THEN[100],END[100],j;
	cin>>n;
	char **sentence;
	bool result=true;
	sentence=new char*[n];
	for (i=0;i<n;++i) sentence[i]=new char[6];
	for (i=0;i<n;++i) cin>>sentence[i];
	for (i=0;i<n;++i){
		if (strcmp(sentence[i],"if")==0){
			IF[ifn]=i;
			++ifn;
		}
		if (strcmp(sentence[i],"then")==0){
			THEN[thenn]=i;
			++thenn;
		}
		if (strcmp(sentence[i],"end")==0){
			END[endn]=i;
			++endn;
		}
		if (strcmp(sentence[i],"begin")==0){
			BEGIN[beginn]=i;
			++beginn;
		}
		if (strcmp(sentence[i],"else")==0){
			ELSE[elsen]=i;
			++elsen;
		}
	}
	if (ifn!=thenn) result=false;
	if (result&&beginn!=endn){
		result=false;
	}
	if (result){
		for (j=0;j<thenn;++j){
			if (THEN[j]!=IF[j]+1){
				result=false;
				break;
			}
		}
	}
	if (result){
		for (j=0;j<beginn;++j){
			if (BEGIN[j]>END[j]){
				result=false;
				break;
			}
		}
	}
	if (result){
		for (j=0;j<elsen;++j){
			if (THEN[j]>ELSE[j]){
				result=false;
				break;
			}
		}
	}
	if (result){
		for (j=0;j<beginn;++j){
			if (strcmp(sentence[BEGIN[j]+1],"else")==0){
				result=false;
				break;
			}
		}
	}
	if (result){
		for (j=0;j<elsen-1;++j){
			if ((strcmp(sentence[ELSE[j]+1],"else")==0)&&(strcmp(sentence[ELSE[j]-1],"end")==0)){
				result=false;
				break;
			}
		}
	}
	if (result) cout<<"YES"<<endl;
	else cout<<"NO\n";
	for (i=0;i<n;++i) delete [] sentence[i];
	delete [] sentence;
	return 0;
}