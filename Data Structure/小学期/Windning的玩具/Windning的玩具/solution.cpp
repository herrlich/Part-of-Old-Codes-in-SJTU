/*********************************
*	Problem	: Windning的玩具
*	Author	: tempbuffer
*	Date	: 2012-6-26
*	Description : 用堆实现多路归并
*********************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 50001
#define MAXM 50001

//------------------------
//Block, 维护每个方块信息
//------------------------
class Block
{
public:
	int love; //喜爱度
	int id; //总ID
	int group; //属于组别
	int groupID; //组内ID
	friend bool operator<(const Block &a, const Block &b)
	{
		//优先选择喜爱度低的，若相同考虑组别编号
		if(a.love!=b.love)
			return a.love<b.love;
		return a.group<b.group;
	}
};

//提供排序的比较函数
bool cmp(const Block &a, const Block &b)
{
	if(a.group!=b.group)
		return a.group<b.group;
	return a.groupID<b.groupID;
}

//优先队列
template<class T>
class Queue
{
	int cnt;
	T data[MAXN];
private:
	void up(int p)
	{
		T item = data[p];
		while(p>1&&tmp<data[p>>1]) data[p] = data[p>>1], p >>= 1;
		data[p] = item;
	}
	void down(int p)
	{
		T item = data[p];
		int q = p<<1;
		while(q<=cnt)
		{
			if(q+1<=cnt&&data[q+1]<data[q]) q++;
			if(item<data[q]) break;
			data[p] = data[q], p = q, q = p<<1;
		}
		data[p] = item;
	}
public:
	Queue():cnt(0) {}
	void push(T data)
	{
		this->data[++cnt] = data;
		up(cnt);
	}
	T top()
	{
		if(empty())
			throw "EMPTY";
		return data[1];
	}
	void pop()
	{
		if(empty())
			throw "EMPTY";
		data[1] = data[cnt--];
		down(1);
	}
	bool empty() {return cnt==0;}
	void clear() {cnt = 0;}
};

int group[MAXM];
Block block[MAXN];
Queue<Block> queue;

int main()
{
	int n,m;
	//------------------------
	//初始化
	//------------------------
	cin >> n >> m;
	for(int i = 0; i < n; i++)
	{
		block[i].id = i+1;
		cin >> block[i].love;
	}
	for(int i = 0; i < m; i++)
	{
		int groupNum,tmp;
		cin >> groupNum;
		for(int j = 0; j < groupNum; j++)
		{
			cin >> tmp;
			block[tmp-1].group = i;
			block[tmp-1].groupID = j;
		}
	}
	sort(block,block+n,cmp);

	//------------------------
	//计算每组首个元素的位置并入堆，考虑某组无元素的情况
	//------------------------
	memset(group,-1,sizeof(group));
	for(int i = n-1; i >= 0; i--)
		group[block[i].group] = i;
	for(int i = 0; i < m; i++)
		if(group[i] >= 0)
			queue.push(block[group[i]++]);

	//------------------------
	//依次出堆，并把该组编号向后推进
	//------------------------
	for(int i = 0; i < n; i++)
	{
		Block tmp = queue.top();
		cout << tmp.id << endl;
		queue.pop();
		if(group[tmp.group]<n&&block[group[tmp.group]].group==tmp.group)
			queue.push(block[group[tmp.group]++]);
	}

	return 0;
}
