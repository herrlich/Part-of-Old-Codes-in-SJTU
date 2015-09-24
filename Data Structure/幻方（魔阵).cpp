#include <iostream>
using namespace std;
int main()
{
	int n,**magic,row,col,i,j,count;
	cout<<"ÊäÈë½×Êý£¨ÆæÊý£©"<<endl;
	cin>>n;
	magic=new int *[n];
	for (i=0;i<n;++i){
		magic[i]=new int [n];
		for (j=0;j<n;++j){
			magic[i][j]=0;
		}
	}
	row=0;
	col=(n-1)/2;
	magic[row][col]=1;
	for (count=2;count<=n*n;++count){
		if (magic[(row+n-1)%n][(col+1)%n]==0){
			row=(row+n-1)%n;
			col=(col+1)%n;
		}
		else row=(row+1)%n;
		magic[row][col]=count;
	}
	for (i=0;i<n;++i){
		for (j=0;j<n;++j){
			cout<<magic[i][j]<<'\t';
		}
		cout<<endl;
	}
	return 0;
}