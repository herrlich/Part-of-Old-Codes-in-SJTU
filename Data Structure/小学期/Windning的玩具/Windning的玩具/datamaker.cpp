#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;
#define MAXN 50001

class Block
{
public:
	int id;
	int group;
}data[MAXN];

bool cmp(const Block &a, const Block &b)
{
	return a.group<b.group;
}

int main()
{
	int n,m;
	srand(time(NULL));
	ofstream fout("data.out");
	cin >> n >> m;
	cout << n << ' ' << m << endl;
	for(int i = 0; i < n; i++)
	{
		cout << rand() << ' ';
		data[i].id = i+1;
	}
	cout << endl;
	for(int i = 0; i < 10000; i++)
	{
		int a = rand()%n, b = rand()%n;
		swap(data[a],data[b]);
	}
	for(int i = 0; i < n; i++)
		data[i].group = rand()%m;
	sort(data,data+n,cmp);
	int group = m-1;
	int cnt = 0;
	for(int i = n-1; i >= 0; i--)
	{
		++cnt;
		if(i==0||data[i-1].group!=data[i].group)
		{
			while(data[i].group<group)
			{
				cout << "0" << endl;
				group--;
			}
			cout << cnt << ' ';
			for(int j = 0; j < cnt; j++)
				cout << data[i+j].id << ' ';
			cout << endl;
			cnt = 0;
			group--;
		}
	}
	while(group>=0)
	{
		cout << "0" << endl;
		group--;
	}
	return 0;
}
