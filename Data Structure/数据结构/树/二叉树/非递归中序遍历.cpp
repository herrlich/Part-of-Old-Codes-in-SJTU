struct StNode{
	Node* node;
	int TimesPop;
	StNode(Node *N=NULL):node(N),TimesPop(0) {}
};
template <class Type>
void BinaryTree<Type>::midOrder() const{
	linkStack<StNode> s;
	StNode current(root);
	cout<<"ÖÐÐò±éÀú:";
	s.push(current);
	while (!s.empty()){
		current=s.pop();
		if (++current.TimesPop==2){
			cout<<current.node->data;
			if (current.node->right!=NULL) s.push(StNode(current.node->right));
		}
		else{
			s.push(current);
			if (current.node->left!=NULL) s.push(StNode(current.node->left));
		}
	}
}