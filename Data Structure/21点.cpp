//文件名：21 points.cpp
//用来玩“21点”游戏。

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//定义全局变量。
bool used[4][13]={false};//定义了一个二维数组，用true表示已经发出去的牌，反之用false。
int pc_card=0,player_card=0;//pc_card为电脑此时牌数，player同理。
double pc_point=0,player_point=0;//pc_point为电脑此时分数，player同理.
bool turn=false,winning=true;//turn为false时为人类玩家回合，反之为电脑回合。
double poker[4][13]={0};//定义一个扑克牌数组。
void wash();//函数原型声明。
void give();//函数原型声明。
void win();//函数原型声明。

//主程序
int main()//此函数用来实现21点功能。
{
	int suit,point;//suit为花色，point为点数。
	char ask='y';//初始化询问是否游戏的变量ask。
	for (suit=0;suit<4;++suit){
		for (point=0;point<13;++point){
			if (point==10||point==11||point==12) poker[suit][point]=0.5;
			else poker[suit][point]=point+1;//suit=0为红桃，1为黑桃，2为方块，3为梅花。
		}
	}//构建扑克牌。
	wash();//在每次玩游戏时进行洗牌。
	cout<<"玩家阶段"<<endl;
	give();//给玩家发一张牌。
	while(ask=='y'){
		give();
		if (player_point>21){
			cout<<"\n玩家输了"<<endl;
			winning=false;//用winning判断游戏是否中途结束,false为结束。
			break;}
		cout<<"\n是否继续要牌(y/n)"<<endl;
		cin>>ask;
	}
	turn=true;//进入电脑回合。
	if (winning){
		cout<<"\n电脑阶段"<<endl;
		while (pc_point<=player_point){
			give();
		}
	}
	win();//判断游戏结束时的胜负。
	return 0;
}

//函数：wash
//用法：wash（）；
//作用：在每一次游戏开始时洗牌。
void wash()
{
	int i,j;
	for (i=0;i<4;++i)
		for (j=0;j<13;++j)
			used[i][j]=false;//used是判断某一张牌是否出过的变量。used等于true时表明该扑克牌已用过。
	pc_card=0;
	pc_point=0;
	player_card=0;
	player_point=0;
	turn=false;//将状态还原为玩家阶段。
}

//函数名：give
//用法:give();
//作用：为玩家和电脑进行发牌，并在其中一方要牌超过21时判断游戏结束。
void give()
{
	int i,j;
	srand(time(NULL));//以时间作为随机数种子。
	do{
		i=rand()%4;//产生花色随机数。
		j=rand()%13;//产生点数随机数。
	}while(used[i][j]);
	if (!turn){
		player_card+=1;
		player_point+=poker[i][j];
		switch(i){
		case 0:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n玩家获得牌 红桃"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n玩家获得牌 红桃A";break;
				case 10:cout<<"\n玩家获得牌 红桃J";break;
				case 11:cout<<"\n玩家获得牌 红桃Q";break;
				case 12:cout<<"\n玩家获得牌 红桃K";break;
				}
			}
			break;
		case 1:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n玩家获得牌 黑桃"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n玩家获得牌 黑桃A";break;
				case 10:cout<<"\n玩家获得牌 黑桃J";break;
				case 11:cout<<"\n玩家获得牌 黑桃Q";break;
				case 12:cout<<"\n玩家获得牌 黑桃K";break;
				}
			}
			break;
		case 2:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n玩家获得牌 方块"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n玩家获得牌 方块A";break;
				case 10:cout<<"\n玩家获得牌 方块J";break;
				case 11:cout<<"\n玩家获得牌 方块Q";break;
				case 12:cout<<"\n玩家获得牌 方块K";break;
				}
			}
			break;
		case 3:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n玩家获得牌 梅花"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n玩家获得牌 梅花A";break;
				case 10:cout<<"\n玩家获得牌 梅花J";break;
				case 11:cout<<"\n玩家获得牌 梅花Q";break;
				case 12:cout<<"\n玩家获得牌 梅花K";break;
				}
			}
			break;
		}
	}
	else{
		pc_card+=1;
		pc_point+=poker[i][j];
		switch(i){
		case 0:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n电脑获得牌 红桃"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n电脑获得牌 红桃A";break;
				case 10:cout<<"\n电脑获得牌 红桃J";break;
				case 11:cout<<"\n电脑获得牌 红桃Q";break;
				case 12:cout<<"\n电脑获得牌 红桃K";break;
				}
			}
			break;
		case 1:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n电脑获得牌 黑桃"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n电脑获得牌 黑桃A";break;
				case 10:cout<<"\n电脑获得牌 黑桃J";break;
				case 11:cout<<"\n电脑获得牌 黑桃Q";break;
				case 12:cout<<"\n电脑获得牌 黑桃K";break;
				}
			}
			break;
		case 2:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n电脑获得牌 方块"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n电脑获得牌 方块A";break;
				case 10:cout<<"\n电脑获得牌 方块J";break;
				case 11:cout<<"\n电脑获得牌 方块Q";break;
				case 12:cout<<"\n电脑获得牌 方块K";break;
				}
			}
			break;
		case 3:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n电脑获得牌 梅花"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n电脑获得牌 梅花A";break;
				case 10:cout<<"\n电脑获得牌 梅花J";break;
				case 11:cout<<"\n电脑获得牌 梅花Q";break;
				case 12:cout<<"\n电脑获得牌 梅花K";break;
				}
			}
			break;
		}
	}
	used[i][j]=true;//将用过的牌进行标注。
	if (pc_point>21){
		cout<<"\n玩家赢了"<<endl;//若电脑中途超过21点，判玩家胜。
		winning=false;//中途结束。
	}
}

//函数名：win
//用法：win();
//作用：判定最后阶段胜负。
void win()
{
	if (winning){
		if (player_point>pc_point) cout<<"\n玩家赢了"<<endl;
		if (player_point<pc_point) cout<<"\n电脑赢了"<<endl;
		if (player_point==pc_point){
			if (player_card>pc_card) cout<<"\n玩家赢了"<<endl;
			if (player_card<pc_card) cout<<"\n电脑赢了"<<endl;
			if (player_card==pc_card) cout<<"\n平局"<<endl;
		}
	}
}