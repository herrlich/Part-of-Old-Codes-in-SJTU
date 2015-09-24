#include <iostream>
using namespace std;

void queen_all(int k);
int col[9]={0};
int row=0;
bool digleft[17],digright[17];

int main()
{
	int j;
	for (j=1;j<17;++j) digleft[j]=digright[j]=false;
	queen_all(1);
	return 0;
}

void queen_all(int k)
{
	int i,j,a,tmp;
	char choice;
	for (i=1;i<9;++i){
		a=(row>>(i-1))&0x01;
		if (!a&&!digleft[k+i-1]&&!digright[8+k-i]){
			col[k]=i;
			digleft[k+i-1]=digright[8+k-i]=true;
			tmp=1<<(i-1);
			row=row|tmp;
			if (k==8){
				for (j=1;j<9;++j)
					cout<<j<<'\t'<<col[j]<<'\n';
				cout<<"是否继续(Q——退出，其他继续)"<<endl;
				cin>>choice;
				if (choice=='Q' || choice=='q') exit(0);
			}
			else queen_all(k+1);
			digleft[k+i-1]=digright[8+k-i]=false;
			tmp=1<<(i-1);
			row=row&(~tmp);
		}
	}
}