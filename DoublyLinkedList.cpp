#include<iostream>
using namespace std;

class Node{
public:
	int data;
	Node* next;
	Node* prev;

};

class DoublyLinkedList{
public:
	Node * start; // special variable which stores address of head node.
	Node* last; // special variable which stores address of the last node.

	Node* ploc; //to be used by Search(value) method to store address of logical predecessor of value in a list.
	Node* loc;//to be used by Search(value) method to store address of the node containing the searched value in a list. If it is not found it contains NULL.

	DoublyLinkedList() {
		start = NULL;
		last = NULL;
		ploc = NULL;	loc = NULL;
	}

	bool isEmpty() {
		return start == NULL;
	}


	void InsertAtFront(int value) {
		Node* newnode = new Node();
		newnode->data = value;
		if (isEmpty()) {
			start = newnode;
			last = newnode;
		}
		else
		{
			newnode->next = start;
			start->prev = newnode;
			start = newnode;
		}
		
	}

	void InsertAtEnd(int value) {
		Node* newnode = new Node();
		newnode->data = value;

		if (!isEmpty())
		{
			newnode->prev = last;
			last->next = newnode;
			last = newnode;
		}
		else
		{
			start = newnode;
			last = newnode;
		}
		printlist(true);
	}

	void Search(int value)
	{
		loc = start;
		ploc = NULL;

		if (isEmpty())
		{
			cout << "list is empty";
			return;
		}
		while (loc != NULL && loc->data < value)
		{
			ploc = loc;
			loc = loc->next;
		}

		if (loc != NULL && loc->data != value)
		{
			loc = NULL;
		}
	}

	void printlist(bool direction)
	{
		if (!isEmpty())
		{
			Node* temp;
			if (direction)//prints in the forward direction
			{
				temp = start;
				while (temp != NULL)
				{
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << "\n";
			}
			else//prints in the reverse direction
			{
				temp = last;
				while (last != NULL)
				{
					cout << temp->data << " ";
					temp = temp->prev;
				}
				cout << "\n";
			}
		}
	}

	//implementation of function which rearranges order of the entire doubly linked list by reversing it.
	void Reverse() {
		Node* temp = NULL;
		Node* current = start;	
		while (current != NULL)
		{
			/* swap the next and previous of all nodes */
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}

		/* Before changing the head, check for the cases like empty
		list and list with only one node */
		if (temp != NULL)
			start = temp->prev;
		else {
			cout << "list contains only one element\n";
		}
		printlist(true);
	}

	/*implementation of a function which takes two values as input from the user and searches them in the list.
	If both the values are found,
	your task is to swap both the nodes in which these values are found. Note, that you are not supposed to swap values.*/
	void swapNodes(int val1, int val2)
	{
		/*case: both values are same*/
		if (val1 == val2)
		{
			cout << "both the values are same so swapping is not possible\n";
			return;
		}
		
		//searching value 1 and keeping track of its previous and next
		Node* prev_of_var1 = NULL;  Node* current_val1 = start;
		while (current_val1->data != val1)
		{
			prev_of_var1 = current_val1;
			current_val1 = current_val1->next;
		}

		//searching value 1 and keeping track of its previous and next
		Node* prev_of_var2 = NULL;  Node* current_val2 = start;
		while (current_val2->data != val2)
		{
			prev_of_var2 = current_val2;
			current_val2 = current_val2->next;
		}

		//if any one is not present then also nothing to do 
		if (current_val1 == NULL || current_val2 == NULL)
		{
			cout << "atleast any one value is not present so swapping not possible\n";
			return;
		}

		//if val1 is not starting node
		if (prev_of_var1 != NULL)
		{
			prev_of_var1->next = current_val2;
		}
		else //if val1 is starting
		{
			start = current_val2;
		}

		//if val2 is not starting node
		if (prev_of_var2 != NULL)
		{
			prev_of_var2->next= current_val1;
		}
		else //if val1 is starting
		{
			start = current_val1;
		}

		//now swapping the pointers 
		Node* temp = current_val2->next;
		current_val2->next = current_val1->next;
		current_val1->next = temp;
		printlist(true);
	}




	void InsertSorted(int value)
	{
		Search(value);
		if (loc != NULL)
		{
			cout << "DUPLICATION NOT ALLOWED\n";
		}
		else
		{
			if (ploc == NULL)
			{
				InsertAtFront(value);
			}
			Node* newnode = new Node;
			newnode->data = value;
			newnode->next = ploc->next;
			ploc->next = newnode;
			newnode->prev = ploc;

			//case:if ploc!=null
				if (ploc != last)
				{
					ploc->next->prev = newnode;

				}
				else//when ploc is last
				{
					last = newnode;
					//ploc->next = newnode;
				}
			}
		}

		void DeleteValue(int value)
		{
			Search(value);
			if (loc != NULL)
			{
				//1st node
				if (ploc == NULL)
				{
					if (loc = last)
					{
						start = NULL;
						last = NULL;
					}
					else
					{
						start = start->next;
						start->prev = NULL;
					}
				}
				//if value is not front node
				else
				{
					/*case: if loc is last */
					if (loc == last)
					{
						last = ploc;
						ploc->next = NULL;
					}
					/*case: if loc is not last*/
					else
					{
						loc->next->prev = ploc;
						ploc->next = loc->next;
					}
				}
				//deallocate memory
				delete loc;
			}
			else
			{
				cout << "value not found \n";
			}
			printlist(true);
		}

		void DeleteFrontNode() {
			if (!isEmpty()) {
				Node* temp = start;
				start = start->next;
				start->prev = NULL;
				delete temp;
			}
			printlist(true);
		}

		void DeleteEndNode() {
			if (!isEmpty())
			{
				Node* temp = last;
				last = last->prev;
				last->next = NULL;
				delete temp;
			}
			printlist(true);
		}

		void DestroyList() {
			Node* temp;

			while (start != NULL)
			{
				temp = start;
				start = start->next;
				delete temp;
			}
			last = NULL;
			cout << "YAYYY!!!!!!!!!!!! LIST IS DESTROYED\n \n ";
			printlist(true);
		}

		/*
		implementation ofa function which rearranges
		the linked list by group nodes having even numbered and odd numbered value in their data part.
		*/
		void EvenOdd() {
			Node* last = start;
			Node* current = start;

			/* Get pointer to the last node */
			while (last->next != NULL)
				last = last->next;

			Node* new_last = last;

			/* Consider all odd nodes before the first
			 even node and move then after end */
			while (current->data % 2 != 0 && current != last)
			{
				new_last->next = current;
				current = current->next;
				new_last->next->next = NULL;
				new_last = new_last->next;
			}


			/*case: if
			there is any even node */
			if (current->data % 2 == 0)
			{
				/* Change the head pointer to
				point to first even node */
				start = current;

				/* current pointer pointing to the first even node */
				while (current != last)
				{
					//checking if its even
					if ((current->data) % 2 == 0)
					{
						current->prev = current;
						current = current->next;
					}
					else
					{
						/* break the link between
						prev and current */
						current->prev->next = current->next;

						/* Make next of curr as NULL */
						current->next = NULL;

						/* Move curr to end */
						new_last->next = current;

						/* make curr as new end of list */
						new_last = current;

						/* Update current pointer to
						next of the moved node */
						current = current->prev->next;
					}
				}
			}

			/* We must have prev set before executing
			lines following this statement */
			else current->prev = current;

			/* If there are more than 1 odd nodes
			and end of original list is odd then
			move this node to end to maintain
			same order of odd numbers in modified list */
			if (new_last != last && (last->data) % 2 != 0)
			{
				current->prev->next = last->next;
				last->next = NULL;
				new_last->next = last;
			}
			printlist(true);


		}
		
};

int main() {
	cout << "-----------------------------------------------------------------------\n\t\t DOUBLY LINKED LIST\n-----------------------------------------------------------------------\n";
	DoublyLinkedList* obj = new DoublyLinkedList();
	cout << "inserting 1 at front \n";
	obj->InsertAtFront(1);

	obj->printlist(true);
	cout << "inserting 3,5,2,4,6 in list\n";
	obj->InsertSorted(2);
	obj->InsertSorted(3);
	obj->InsertSorted(4);
	obj->InsertSorted(5);
	obj->InsertSorted(6);

	obj->printlist(true);

	cout << "**********************************************************\n";
	//cout << "(1)calling function which rearranges order of the entire doubly linked list by reversing it. \n";
	//obj->Reverse();
	//cout << "(2)calling afunction which takes two values as input from the user and searches them in the list."
		//"If both the values are found, your task is to swap both the nodes in which these values are found. "
		//"Note, that you are not supposed to swap values.\n";
	//cout << "CASE# 2: SWAPPIG any two other tha 1st and last \n" << endl;
	//obj->swapNodes(1,10 );
	//obj->swapNodes(2, 3);
	//obj->swapNodes(2, 4);
	cout << "rearranging the even and odd valued nodes \n";
	obj->EvenOdd();
	cout << "**********************************************************\n";


	/*cout << "deleting the 5 from the list \n";
	obj->DeleteValue(5);

	cout << "deleting the front node \n";
	obj->DeleteFrontNode();

	cout << "deleting the end node \n";
	obj->DeleteEndNode();

	cout << "destroying the list \n";
	obj->DestroyList();*/

}
