/*********************************
*	Problem	: Windning�����
*	Author	: tempbuffer
*	Date	: 2012-6-26
*	Description : �ö�ʵ�ֶ�·�鲢
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
//Block, ά��ÿ��������Ϣ
//------------------------
class Block
{
public:
	int love; //ϲ����
	int id; //��ID
	int group; //�������
	int groupID; //����ID
	friend bool operator<(const Block &a, const Block &b)
	{
		//����ѡ��ϲ���ȵ͵ģ�����ͬ���������
		if(a.love!=b.love)
			return a.love<b.love;
		return a.group<b.group;
	}
};

//�ṩ����ıȽϺ���
bool cmp(const Block &a, const Block &b)
{
	if(a.group!=b.group)
		return a.group<b.group;
	return a.groupID<b.groupID;
}

//���ȶ���
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
	//��ʼ��
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
	//����ÿ���׸�Ԫ�ص�λ�ò���ѣ�����ĳ����Ԫ�ص����
	//------------------------
	memset(group,-1,sizeof(group));
	for(int i = n-1; i >= 0; i--)
		group[block[i].group] = i;
	for(int i = 0; i < m; i++)
		if(group[i] >= 0)
			queue.push(block[group[i]++]);

	//------------------------
	//���γ��ѣ����Ѹ���������ƽ�
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
