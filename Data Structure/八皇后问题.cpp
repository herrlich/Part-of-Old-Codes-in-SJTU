#include <iostream>
using namespace std;

void queen_all(int k);
int col[9]={0};
bool row[9],digleft[17],digright[17];

int main()
{
	int j;
	for (j=1;j<17;++j) digleft[j]=digright[j]=true;
	for (j=1;j<9;++j) row[j]=true;
	queen_all(1);
	return 0;
}

void queen_all(int k)
{
	int i,j;
	char choice;
	for (i=1;i<9;++i){
		if (row[i]&&digleft[k+i-1]&&digright[8+k-i]){
			col[k]=i;
			row[i]=digleft[k+i-1]=digright[8+k-i]=false;
			if (k==8){
				for (j=1;j<9;++j)
					cout<<j<<'\t'<<col[j]<<'\n';
				cout<<"是否继续(Q——退出，其他继续)"<<endl;
				cin>>choice;
				if (choice=='Q' || choice=='q') exit(0);
			}
			else queen_all(k+1);
			row[i]=digleft[k+i-1]=digright[8+k-i]=true;
		}
	}
}