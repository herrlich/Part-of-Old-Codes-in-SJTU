#include "honey.h"

static int win_cnt=0,lose_cnt=0,tie_cnt=0;

void prn_game_status()
{
	cout<<endl;
	cout<<"win:"<<win_cnt<<endl;
	cout<<"lose:"<<lose_cnt<<endl;
	cout<<"tie:"<<tie_cnt<<endl;
	cout<<"Total:"<<win_cnt+lose_cnt+tie_cnt<<endl;
}
void prn_help()
{
	cout<<endl
		<<"The following characters can be used:\n"
		<<"p for paper\n"
		<<"r for rock\n"
		<<"s for scissor\n"
		<<"g print the game status\n"
		<<"h help,print this list\n"
		<<"q quit the game\n";
}
void report(outcome result)
{
	switch(result){
	case win:++win_cnt;cout<<"you win.\n";break;
	case tie:++tie_cnt;cout<<"A tie.\n";break;
	case lose:++lose_cnt;cout<<"you lose.\n";break;
	}
}