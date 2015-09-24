#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
	int num1,num2,result1,result2,op,min,max,answer;
	bool correct=false;
	char go_on='y';

	while (go_on=='y'){

		srand(time(NULL));

		num1=rand()%100+1;
		num2=rand()%100+1;
		op=rand()%4;
		answer=rand()%3;

		switch(op){
		case 0: cout<<num1<<"+"<<num2<<"=?";
			cin>>result1;
			do{
				if (result1==num1+num2)
					correct=true;
				else{
					correct=false;
					switch(answer){
					case 0: cout<<"\nYou are wrong!"<<endl;break;
					case 1: cout<<"\nIt's a mistake!"<<endl;break;
					case 2: cout<<"\nTry again!"<<endl;break;
					}
					answer=rand()%3;
					cout<<"���ٴ������"<<endl;
					cin>>result1;
				}
			}
			while (correct==false);
			break;

		case 1: cout<<num1<<"*"<<num2<<"=?";
			cin>>result1;
			do{
				if (result1==num1*num2)
					correct=true;
				else{
					correct=false;
					switch(answer){
					case 0: cout<<"\nYou are wrong!"<<endl;break;
					case 1: cout<<"\nIt's a mistake!"<<endl;break;
					case 2: cout<<"\nTry again!"<<endl;break;
					}
					answer=rand()%3;
					cout<<"���ٴ������"<<endl;
					cin>>result1;
				}
			}
			while (correct==false);
			break;

		case 2: cout<<num1<<"/"<<num2<<"=?";
			cin>>result1;
			cout<<"\n����Ϊ?";
			cin>>result2;
			do{
				if (result1==num1/num2 && result2==num1%num2)
					correct=true;
				else{
					correct=false;
					switch(answer){
					case 0: cout<<"\nYou are wrong!"<<endl;break;
					case 1: cout<<"\nIt's a mistake!"<<endl;break;
					case 2: cout<<"\nTry again!"<<endl;break;
					}
					answer=rand()%3;
					cout<<"���ٴ�������"<<endl;
					cin>>result1;
					cout<<"���ٴ���������"<<endl;
					cin>>result2;
				}
			}
			while (correct==false);
			break;

		case 3: max=(num1>num2)?num1:num2;
			min=(num1<num2)?num1:num2;
			cout<<max<<"-"<<min<<"=?";
			cin>>result1;
			do{
				if (result1==max-min)
					correct=true;
				else{
					correct=false;
					switch(answer){
					case 0: cout<<"\nYou are wrong!"<<endl;break;
					case 1: cout<<"\nIt's a mistake!"<<endl;break;
					case 2: cout<<"\nTry again!"<<endl;break;
					}
					answer=rand()%3;
					cout<<"���ٴ������"<<endl;
					cin>>result1;
				}
			}
			while (correct==false);
			break;
		}

		if (correct==true){
			switch(answer){
			case 0: cout<<"\nYou are right!"<<endl;break;
			case 1: cout<<"\nIt's OK!"<<endl;break;
			case 2: cout<<"\nVery good!"<<endl;break;
			}
		}
		cout<<"��Ҫ������y/n"<<endl;
		cin>>go_on;
	}
	return 0;
	}