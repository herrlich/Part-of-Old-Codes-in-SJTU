//�ļ���:hw1.cpp
//���в�����Ϸ
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
	srand(time(NULL));
	int right=0,wrong=0;//��ʼ����ȷ�ʹ������
	char play='y';

	while (play=='y'){
		cout<<"������Ϸ��(y/n)"<<endl;
		cin>>play;
		if (play=='n') break;//�ж��Ƿ����������Ϸ

		int times,result[3]={0},num[3]={0},i=0,right_num=0,right_pos=0,j=0;//timesΪ������resultΪ�������ݣ�numΪ�������right_pos��ʾ���ֺ�λ����ȫ��ȷ��right_num��ʾ������ȷλ�ô���
		bool correct=false;

		num[0]=rand()%10;
		do{
			num[1]=rand()%10;
		}while(num[1]==num[0]);
		do{
			num[2]=rand()%10;
		}while(num[0]==num[2] || num[1]==num[2]);//����������ͬ�������

		for (times=0;times<7;++times){
			cout<<"������������²�����֣����ظ���"<<endl;
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
					cout<<"��ϲ�㣬�¶��ˣ�";
					right+=1;
					correct=true;
					break;
			}
		}
		if(!correct){
			wrong+=1;
			cout<<"���ź����´���"<<endl;
			cout<<"���Ϊ:"<<num[0]<<'\t'<<num[1]<<'\t'<<num[2]<<'\n';
		}
	}
	cout<<"��������"<<right+wrong<<"�֣��¶�"<<right<<"�Σ��´�"<<wrong<<"��"<<endl;//������ȷ�ʹ������
	return 0;
}