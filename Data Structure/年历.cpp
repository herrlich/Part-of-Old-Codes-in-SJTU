#include <iostream>
using namespace std;
//�˳����������2010���Ժ���һ���������
void WEEK(int delta);
int main()
{
	int year,runnian=0,month,day,i,newdelta;
	bool RUN=false;
	//��֪2010��1��1���������塣
	cout<<"������Ҫ��ѯ����ݣ�������2010��)"<<endl;
	cin>>year;
	for (i=2010;i<=year;++i){
		if (((i-2000)%4==0&&(i-2000)%100!=0)||(i-2000)%400==0) ++runnian;
	}
	if (((year-2000)%4==0&&(year-2000)%100!=0)||(year-2000)%400==0) RUN=true;
	cout<<year<<"������:"<<endl;
	for (month=1;month<=12;++month){
		if (month==1){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN)*365+(runnian-RUN)*366+day-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==2){
				for (day=1;day<=28+RUN;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
				}
			}
		if (month==3){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==4){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==5){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==6){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==7){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==8){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==9){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==10){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==11){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30+31-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==12){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30+31+30-1)%7;
				cout<<month<<"��"<<'\t'<<day<<"��"<<'\t';
				WEEK(newdelta);
			}
		}
	}
	return 0;
}
void WEEK(int delta)
{
	char weekday[10]={'0'};
	switch (delta){
	case 0:cout<<"������"<<endl;break;
	case 1:cout<<"������"<<endl;break;
	case 2:cout<<"������"<<endl;break;
	case 3:cout<<"����һ"<<endl;break;
	case 4:cout<<"���ڶ�"<<endl;break;
	case 5:cout<<"������"<<endl;break;
	case 6:cout<<"������"<<endl;break;
	}
}