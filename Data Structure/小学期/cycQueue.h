#include <iostream>
using namespace std;
class cycQueue {
	struct Node {
		int data;    // 队列元素
		Node *next;
	};
	Node  *tail;    // 指向队尾元素的指针
public:
	cycQueue();
	~cycQueue();
	void enQueue(int x);
	int deQueue();
	bool isEmpty();
};
cycQueue::cycQueue(){
	tail=new Node;
	tail->data=NULL;
	tail->next=tail;
}
cycQueue::~cycQueue(){
	Node *q;
	while (tail->next!=tail){
		q=tail;
		tail=tail->next;
		delete q;
	}
	delete tail;
}
void cycQueue::enQueue(int x){
	if (tail->next==tail) tail->data=x;
	else {
		Node *q=new Node;
		q->data=x;
		q->next=tail->next;
		tail->next=q;
		tail=q;
	}
}
int cycQueue::deQueue(){
	Node *q;
	int num;
	q=tail->next;
	num=q->data;
	tail->next=q->next;
	delete q;
	return num;
}
bool cycQueue::isEmpty(){
	return (tail->next==tail);
}