#include <iostream>
using namespace std;
class closeHashTable{//��д�����ɢ�б����á�Ҫ�����������ԭ�����е�λ��/size����������ɢ�б��еĴ洢λ��
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
	//�����ͨ������ԭʼ���飬Ȼ����ԭʼ���鹹��ɢ�б������������򣬷�������ú����insert���������������롭��
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
	//�˺���ʵ�ֵ���Ѱ��ԭ�����е�x��Ԫ�����¹�����ɢ�б��е�λ�ã������ֵ����ͨ���������غ��[]���
	//��Ϊ�Ҿ�����������˼��ҪѰ��ԭ�����е�x��Ԫ�ص�ֵ�������ǽ����ж��Ǹ������Ƿ���ɢ�б���
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
bool closeHashTable::insert(const int &x,int position){//xΪҪ���������,positionΪ��������Ҫ����������е�λ��
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
bool closeHashTable::remove(const int &x){//�����removeҲ�Ǵ�ɢ�б����Ƴ�ԭ������λ��x�ϵ�����
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
	//�������Ҫ�����Ǹ���ԭ�����еĵ�x��Ԫ�ص�ֵ�����Ҫ��ԭ������ĳ������ֵ���ı䣬����remove��insertʵ�ְ�
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