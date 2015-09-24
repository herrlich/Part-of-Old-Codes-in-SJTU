//�ļ�����21 points.cpp
//�����桰21�㡱��Ϸ��

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//����ȫ�ֱ�����
bool used[4][13]={false};//������һ����ά���飬��true��ʾ�Ѿ�����ȥ���ƣ���֮��false��
int pc_card=0,player_card=0;//pc_cardΪ���Դ�ʱ������playerͬ��
double pc_point=0,player_point=0;//pc_pointΪ���Դ�ʱ������playerͬ��.
bool turn=false,winning=true;//turnΪfalseʱΪ������һغϣ���֮Ϊ���Իغϡ�
double poker[4][13]={0};//����һ���˿������顣
void wash();//����ԭ��������
void give();//����ԭ��������
void win();//����ԭ��������

//������
int main()//�˺�������ʵ��21�㹦�ܡ�
{
	int suit,point;//suitΪ��ɫ��pointΪ������
	char ask='y';//��ʼ��ѯ���Ƿ���Ϸ�ı���ask��
	for (suit=0;suit<4;++suit){
		for (point=0;point<13;++point){
			if (point==10||point==11||point==12) poker[suit][point]=0.5;
			else poker[suit][point]=point+1;//suit=0Ϊ���ң�1Ϊ���ң�2Ϊ���飬3Ϊ÷����
		}
	}//�����˿��ơ�
	wash();//��ÿ������Ϸʱ����ϴ�ơ�
	cout<<"��ҽ׶�"<<endl;
	give();//����ҷ�һ���ơ�
	while(ask=='y'){
		give();
		if (player_point>21){
			cout<<"\n�������"<<endl;
			winning=false;//��winning�ж���Ϸ�Ƿ���;����,falseΪ������
			break;}
		cout<<"\n�Ƿ����Ҫ��(y/n)"<<endl;
		cin>>ask;
	}
	turn=true;//������Իغϡ�
	if (winning){
		cout<<"\n���Խ׶�"<<endl;
		while (pc_point<=player_point){
			give();
		}
	}
	win();//�ж���Ϸ����ʱ��ʤ����
	return 0;
}

//������wash
//�÷���wash������
//���ã���ÿһ����Ϸ��ʼʱϴ�ơ�
void wash()
{
	int i,j;
	for (i=0;i<4;++i)
		for (j=0;j<13;++j)
			used[i][j]=false;//used���ж�ĳһ�����Ƿ�����ı�����used����trueʱ�������˿������ù���
	pc_card=0;
	pc_point=0;
	player_card=0;
	player_point=0;
	turn=false;//��״̬��ԭΪ��ҽ׶Ρ�
}

//��������give
//�÷�:give();
//���ã�Ϊ��Һ͵��Խ��з��ƣ���������һ��Ҫ�Ƴ���21ʱ�ж���Ϸ������
void give()
{
	int i,j;
	srand(time(NULL));//��ʱ����Ϊ��������ӡ�
	do{
		i=rand()%4;//������ɫ�������
		j=rand()%13;//���������������
	}while(used[i][j]);
	if (!turn){
		player_card+=1;
		player_point+=poker[i][j];
		switch(i){
		case 0:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n��һ���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n��һ���� ����A";break;
				case 10:cout<<"\n��һ���� ����J";break;
				case 11:cout<<"\n��һ���� ����Q";break;
				case 12:cout<<"\n��һ���� ����K";break;
				}
			}
			break;
		case 1:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n��һ���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n��һ���� ����A";break;
				case 10:cout<<"\n��һ���� ����J";break;
				case 11:cout<<"\n��һ���� ����Q";break;
				case 12:cout<<"\n��һ���� ����K";break;
				}
			}
			break;
		case 2:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n��һ���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n��һ���� ����A";break;
				case 10:cout<<"\n��һ���� ����J";break;
				case 11:cout<<"\n��һ���� ����Q";break;
				case 12:cout<<"\n��һ���� ����K";break;
				}
			}
			break;
		case 3:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n��һ���� ÷��"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n��һ���� ÷��A";break;
				case 10:cout<<"\n��һ���� ÷��J";break;
				case 11:cout<<"\n��һ���� ÷��Q";break;
				case 12:cout<<"\n��һ���� ÷��K";break;
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
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n���Ի���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n���Ի���� ����A";break;
				case 10:cout<<"\n���Ի���� ����J";break;
				case 11:cout<<"\n���Ի���� ����Q";break;
				case 12:cout<<"\n���Ի���� ����K";break;
				}
			}
			break;
		case 1:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n���Ի���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n���Ի���� ����A";break;
				case 10:cout<<"\n���Ի���� ����J";break;
				case 11:cout<<"\n���Ի���� ����Q";break;
				case 12:cout<<"\n���Ի���� ����K";break;
				}
			}
			break;
		case 2:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n���Ի���� ����"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n���Ի���� ����A";break;
				case 10:cout<<"\n���Ի���� ����J";break;
				case 11:cout<<"\n���Ի���� ����Q";break;
				case 12:cout<<"\n���Ի���� ����K";break;
				}
			}
			break;
		case 3:
			if(j!=0&&j!=10&&j!=11&&j!=12) cout<<"\n���Ի���� ÷��"<<int(poker[i][j]);
			else {
				switch(j){
				case 0: cout<<"\n���Ի���� ÷��A";break;
				case 10:cout<<"\n���Ի���� ÷��J";break;
				case 11:cout<<"\n���Ի���� ÷��Q";break;
				case 12:cout<<"\n���Ի���� ÷��K";break;
				}
			}
			break;
		}
	}
	used[i][j]=true;//���ù����ƽ��б�ע��
	if (pc_point>21){
		cout<<"\n���Ӯ��"<<endl;//��������;����21�㣬�����ʤ��
		winning=false;//��;������
	}
}

//��������win
//�÷���win();
//���ã��ж����׶�ʤ����
void win()
{
	if (winning){
		if (player_point>pc_point) cout<<"\n���Ӯ��"<<endl;
		if (player_point<pc_point) cout<<"\n����Ӯ��"<<endl;
		if (player_point==pc_point){
			if (player_card>pc_card) cout<<"\n���Ӯ��"<<endl;
			if (player_card<pc_card) cout<<"\n����Ӯ��"<<endl;
			if (player_card==pc_card) cout<<"\nƽ��"<<endl;
		}
	}
}