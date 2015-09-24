#include <iostream>
#include  <ctime>
#include <cstdlib>
using namespace std;
int main()
{
	int num,guess,times=1;
	
	srand(time(NULL));

	num=rand()*100/(RAND_MAX+1);

	do{
		cout<<"猜数游戏开始：\n请给出你猜的第"<<times<<"个数（0~100）："<<endl;
		++times;
		cin>>guess;
		if (guess==num){
			cout<<"恭喜你猜对了!"<<endl;
			break;
		}
		else {
			if (guess>num) cout<<"猜大了,你还有"<<11-times<<"次机会"<<endl;
			else cout<<"猜小了,你还有"<<11-times<<"次机会"<<endl;
		}
		if (times==11) cout<<"游戏失败"<<endl;
	}while (times<=10);
	return 0;
}