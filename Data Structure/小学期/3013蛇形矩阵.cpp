#include <iostream>
using namespace std;
#define Max 100
int main(){
	int r[]={0,1,0,-1};
	int c[]={1,0,-1,0};
	int disp[Max][Max]={0};
	int row=0,col=0,trow,tcol,pos=1,height,width,dir=0;
	cin>>height>>width;
	for (;pos<=height*width;++pos){
		disp[row][col]=pos;
		trow=row+r[dir];
		tcol=col+c[dir];
		if (trow<0||trow>=height||tcol<0||tcol>=width||disp[trow][tcol]!=0) dir=(dir+1)%4;
		col+=c[dir];
		row+=r[dir];
	}
	for (int i=0;i<height;++i){
		cout<<disp[i][0];
		for (int j=1;j<width;++j) cout<<'\t'<<disp[i][j];
		cout<<'\n';
	}
	return 0;
}