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
		cout<<"������Ϸ��ʼ��\n�������µĵ�"<<times<<"������0~100����"<<endl;
		++times;
		cin>>guess;
		if (guess==num){
			cout<<"��ϲ��¶���!"<<endl;
			break;
		}
		else {
			if (guess>num) cout<<"�´���,�㻹��"<<11-times<<"�λ���"<<endl;
			else cout<<"��С��,�㻹��"<<11-times<<"�λ���"<<endl;
		}
		if (times==11) cout<<"��Ϸʧ��"<<endl;
	}while (times<=10);
	return 0;
}