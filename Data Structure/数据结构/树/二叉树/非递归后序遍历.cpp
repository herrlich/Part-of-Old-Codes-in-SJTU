struct StNode{
	Node* node;
	int TimesPop;
	StNode(Node *N=NULL):node(N),TimesPop(0) {}
};
template <class Type>
void BinaryTree<Type>::posrOrder() const{
	linkStack<StNode> s;
	StNode current(root);
	cout<<"ºóÐò±éÀú:";
	s.push(current);
	while (!s.empty()){
		current=s.pop();
		if (++current.TimesPop==3){
			cout<<current.node->data;
			continue;
		}
		s.push(current);
		if (current.TimesPop==1){
			if (current.node->left!=NULL) s.push(StNode(current.node->left));
		}
		else {
			if (current.node->right!=NULL) s.push(StNode(current.node->right));
		}
	}
}