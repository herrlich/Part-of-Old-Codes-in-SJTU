template <class Type>
void BinaryTree<Type>::preOrder() const{
	linkStack<Node*> s;
	Node* current;
	cout<<"Ç°Ðò±éÀú:";
	s.push(root);
	while (!s.isEmpty()){
		current=s.pop();
		cout<<current->data;
		if (current->right!=NULL) s.push(current->right);
		if (current->left!=NULL) s.push(current->left);
	}
}