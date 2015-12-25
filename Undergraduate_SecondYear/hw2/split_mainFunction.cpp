int main(int argc, char* argv[]){
	
	Node *first = new Node;	
	Node *second = new Node;	
	Node *third = new Node;	
	Node *fourth = new Node;
	Node *smaller;
	Node *larger;

	first->value=2;
	second->value = 0;
	third->value = 4;
	fourth->value = 100;

	first->next=second;
	second->next=third;
	third->next=fourth;
	fourth->next=NULL;	

	split(first, smaller, larger, 5);

	cout<<"Smaller contains: "<<endl;
	while(smaller!=NULL){
		cout<<smaller->value<<endl;
		smaller=smaller->next;
	}
	cout<<"Larger contains: "<<endl;
	while(larger!=NULL){
		cout<<larger->value<<endl;
		larger=larger->next;
	}

	while(smaller!=NULL){
		cout<<smaller->value<<endl;
		Node *temp = smaller;
		smaller=smaller->next;
		delete temp;
	}
	while(larger!=NULL){
		cout<<larger->value<<endl;
		Node *temp = larger;
		larger=larger->next;
		delete temp;
	}

	delete first;
	delete second;
	delete third;
	delete fourth;

	return 0;
}
