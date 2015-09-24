#include <iostream>
using namespace std;
int main()
{
	int num,count=0,cube[101][101]={0},i,j;
	int cub[101][101]={0};
	bool turn=true;
	cin>>num;
	for (i=1;i<num+1;++i){
		for (j=1;j<num+1;++j){
			cin>>cube[i][j];
		}
	}
	while (turn){
		turn=false;
		for (i=1;i<num+1;++i){
			for (j=1;j<num+1;++j){
				if (cube[i][j]==0&&(cube[i][j-1]==1&&cub[i][j-1]!=count+2 || cube[i+1][j]==1&&cub[i+1][j]!=count+2||cube[i][j+1]==1&&cub[i][j+1]!=count+2||cube[i-1][j]==1&&cub[i-1][j]!=count+2)){
					turn=true;
					cub[i][j]=count+2;
					cube[i][j]=1;
				}
			}
		}
		++count;
	}
	cout<<count-1<<endl;
	return 0;
}