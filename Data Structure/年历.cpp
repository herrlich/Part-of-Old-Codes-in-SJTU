#include <iostream>
using namespace std;
//此程序用来输出2010年以后任一年的年历。
void WEEK(int delta);
int main()
{
	int year,runnian=0,month,day,i,newdelta;
	bool RUN=false;
	//已知2010年1月1日是星期五。
	cout<<"请输入要查询的年份：（大于2010年)"<<endl;
	cin>>year;
	for (i=2010;i<=year;++i){
		if (((i-2000)%4==0&&(i-2000)%100!=0)||(i-2000)%400==0) ++runnian;
	}
	if (((year-2000)%4==0&&(year-2000)%100!=0)||(year-2000)%400==0) RUN=true;
	cout<<year<<"年年历:"<<endl;
	for (month=1;month<=12;++month){
		if (month==1){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN)*365+(runnian-RUN)*366+day-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==2){
				for (day=1;day<=28+RUN;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
				}
			}
		if (month==3){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==4){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==5){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==6){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==7){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==8){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==9){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==10){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==11){
			for (day=1;day<=30;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30+31-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
				WEEK(newdelta);
			}
		}
		if (month==12){
			for (day=1;day<=31;++day){
				newdelta=((year-2010-runnian+RUN )*365+(runnian-RUN)*366+day+31+28+RUN+31+30+31+30+31+31+30+31+30-1)%7;
				cout<<month<<"月"<<'\t'<<day<<"日"<<'\t';
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
	case 0:cout<<"星期五"<<endl;break;
	case 1:cout<<"星期六"<<endl;break;
	case 2:cout<<"星期日"<<endl;break;
	case 3:cout<<"星期一"<<endl;break;
	case 4:cout<<"星期二"<<endl;break;
	case 5:cout<<"星期三"<<endl;break;
	case 6:cout<<"星期四"<<endl;break;
	}
}