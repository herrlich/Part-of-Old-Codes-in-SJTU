//文件名:hw1.cpp
//进行猜数游戏
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
	srand(time(NULL));
	int right=0,wrong=0;//初始化正确和错误次数
	char play='y';

	while (play=='y'){
		cout<<"想玩游戏吗？(y/n)"<<endl;
		cin>>play;
		if (play=='n') break;//判断是否继续进行游戏

		int times,result[3]={0},num[3]={0},i=0,right_num=0,right_pos=0,j=0;//times为次数，result为输入数据，num为随机数，right_pos表示数字和位置完全正确，right_num表示数字正确位置错误。
		bool correct=false;

		num[0]=rand()%10;
		do{
			num[1]=rand()%10;
		}while(num[1]==num[0]);
		do{
			num[2]=rand()%10;
		}while(num[0]==num[2] || num[1]==num[2]);//产生三个不同的随机数

		for (times=0;times<7;++times){
			cout<<"请输入三个你猜测的数字（不重复）"<<endl;
			cin>>result[0]>>result[1]>>result[2];
			right_pos=0;
			right_num=0;
			for (i=0;i<3;++i){
				for(j=0;j<3;++j){
					if (result[i]==num[j]){
						if (i==j) right_pos+=1;
						else right_num+=1;
					}
				}
			}
			cout<<right_pos<<"A"<<right_num<<"B";
			if (right_pos==3){
					cout<<"恭喜你，猜对了！";
					right+=1;
					correct=true;
					break;
			}
		}
		if(!correct){
			wrong+=1;
			cout<<"很遗憾，猜错了"<<endl;
			cout<<"结果为:"<<num[0]<<'\t'<<num[1]<<'\t'<<num[2]<<'\n';
		}
	}
	cout<<"您共玩了"<<right+wrong<<"局，猜对"<<right<<"次，猜错"<<wrong<<"次"<<endl;//给出正确和错误次数
	return 0;
}