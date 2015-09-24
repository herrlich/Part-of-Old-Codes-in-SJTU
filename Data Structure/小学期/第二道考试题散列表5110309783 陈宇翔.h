#include <iostream>
using namespace std;
class closeHashTable{//我写的这个散列表是用“要插入的数字在原数组中的位置/size”来决定在散列表中的存储位置
private:
	struct node{
		int data;
		int originPos;
		int state;//0--empty;1--active;2--deleted
		node() {state=0;}
	};
	node array[10001];
	int size,ori_size;
public:
	closeHashTable(int length,int oriArr[]);
	~closeHashTable() {}
	int find(const int &x) const;
	bool remove(const int &x);
	bool insert(const int &x,int position);
	int &operator[](const int &x);
	void rehash();
};
closeHashTable::closeHashTable(int length,int oriArr[]){
	//如果是通过给出原始数组，然后按照原始数组构建散列表，则采用这个程序，否则可以用后面的insert（）函数慢慢插入……
	size=length/100;
	ori_size=length;
	int initPos,pos,i;
	for (i=0;i<length;++i){
		initPos=pos=i%size;
		do{
			if (array[pos].data==0&&oriArr[i]!=0){
				array[pos].data=oriArr[i];
				array[pos].originPos=i;
				break;
			}
			pos=(pos+1)%size;
		}while(pos!=initPos);
	}
}
int closeHashTable::find(const int &x) const{
	//此函数实现的是寻找原数组中第x个元素在新构建的散列表中的位置，具体的值可以通过调用重载后的[]获得
	//因为我觉得这道题的意思是要寻找原数组中第x个元素的值，而不是仅仅判断那个数字是否在散列表中
	int initPos,pos;
	initPos=pos=x%size;
	do{
		if (array[pos].originPos==x){
			return pos;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return -1;
}
bool closeHashTable::insert(const int &x,int position){//x为要插入的数字,position为此数字在要保存的数组中的位置
	if (x==0) return true;
	int initPos,pos;
	initPos=pos=position%size;
	do{
		if (array[pos].state!=1){
			array[pos].data=x;
			array[pos].state=1;
			array[pos].originPos=position;
			return true;
		}
		if (array[pos].state==1&&array[pos].data==x){
			return true;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;
}
bool closeHashTable::remove(const int &x){//这里的remove也是从散列表中移除原数组中位置x上的数字
	int initPos,pos;
	initPos=pos=x%size;
	do{
		if (array[pos].state==0) return false;
		if (array[pos].state==1&&array[pos].originPos==x){
			array[pos].data=0;
			array[pos].state=2;
			return true;
		}
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;
}
int &closeHashTable::operator[](const int &x){
	//这里的主要功能是给出原数组中的第x个元素的值，如果要对原数组中某个数的值做改变，则用remove和insert实现吧
	if (x<0&&x>=ori_size) exit(1);
	if (find(x)!=-1){
		array[find(x)].state=1;
		return array[find(x)].data;
	}
	else return 0;
}
void closeHashTable::rehash(){
	node tmp[10001];
	for (int i=0;i<size;++i){
		if (tmp[i].state==1) insert(tmp[i].data,tmp[i].originPos);
	}
	for (int i=0;i<size;++i){
		array[i].data=tmp[i].data;
		array[i].originPos=tmp[i].originPos;
		array[i].state=tmp[i].state;
	}
}