#include <iostream>
using namespace std;
int main(){
	char array[102][102];
	int p[102][102],q[102][102];
	int i,j,m,n,x1,x2,y1,y2,times=0;
	cin>>n>>m>>x1>>y1>>x2>>y2;
	for (i=0;i<=n+1;++i){
		for (j=0;j<=m+1;++j){
			array[i][j]='*';
			p[i][j]=10000;
			q[i][j]=10000;
		}
	}
	for (i=1;i<=n;++i){
		for (j=1;j<=m;++j){
			cin>>array[i][j];
		}
	}
	p[x1][y1]=0;
	q[x1][y1]=0;
	while (p[x2][y2]==10000){
		if (++times>10000){
			cout<<-1<<endl;
			return 0;
		}
		for (i=1;i<=n;++i){
			for (j=1;j<=m;++j){
				if ((p[i][j]<10000)&&(array[i][j]!='*')){
					if (array[i][j]=='.'){
						if ((array[i-1][j]!='*')&&(array[i-1][j]!='-')&&(p[i][j]+1<q[i-1][j])) q[i-1][j]=p[i][j]+1;
						if ((array[i+1][j]!='*')&&(array[i+1][j]!='-')&&(p[i][j]+1<q[i+1][j])) q[i+1][j]=p[i][j]+1;
						if ((array[i][j-1]!='*')&&(array[i][j-1]!='|')&&(p[i][j]+1<q[i][j-1])) q[i][j-1]=p[i][j]+1;
						if ((array[i][j+1]!='*')&&(array[i][j+1]!='|')&&(p[i][j]+1<q[i][j+1])) q[i][j+1]=p[i][j]+1;
					}
					if (array[i][j]=='|'){
						if ((array[i-1][j]!='*')&&(array[i-1][j]!='-')&&(p[i][j]+1<q[i-1][j])) q[i-1][j]=p[i][j]+1;
						if ((array[i-1][j]!='*')&&(array[i+1][j]!='-')&&(p[i][j]+1<q[i+1][j])) q[i+1][j]=p[i][j]+1;
					}
					if (array[i][j]=='-'){
						if ((array[i][j-1]!='*')&&(array[i][j-1]!='|')&&(p[i][j]+1<q[i][j-1])) q[i][j-1]=p[i][j]+1;
						if ((array[i][j+1]!='*')&&(array[i][j+1]!='|')&&(p[i][j]+1<q[i][j+1])) q[i][j+1]=p[i][j]+1;
					}
				}
			}
		}
		for (i=0;i<=n;++i){
			for (j=0;j<=m;++j){
				p[i][j]=q[i][j];
			}
		}
	}
	cout<<p[x2][y2]<<endl;
	return 0;
}