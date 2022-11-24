/*	Implementation of Singly Linked Lists in C++,
*	Along with multiple functions/manipulations
*	(based on 'Cracking the Coding Interview' by Gayle Laakmann McDowell)
*
*	Author: Apurv Mishra (mr.mishra1408@gmail.com)
* 
*	Constraints: All nodes contain integer values only.	*/

// include necessary header files
#include <iostream>
#include <unordered_set>
#include <memory>
#include <cmath>

using namespace std;

// define initialization macro for smart pointers
#define SHARED_PTR shared_ptr<SinglyLinkedListNode>

// Linked list node class
class SinglyLinkedListNode
{
public:
	int data;
	SHARED_PTR next;

	SinglyLinkedListNode(int new_data)
	{
		data = new_data;
		next = nullptr;
	}
};

// Linked list wrapper class
class SinglyLinkedList
{
public:
	SHARED_PTR head;
	SHARED_PTR tail;
	int total_length;

	// initialize with head and tail nodes
	SinglyLinkedList()
	{
		head = nullptr;
		tail = nullptr;
		total_length = 0;
	}

	// append nodes from front
	void insertNode(int new_data)
	{
		SHARED_PTR node = make_shared<SinglyLinkedListNode>(new_data);

		if (!head)
			head = node;
		else
			tail->next = node;

		tail = node;
		total_length++;
	}

	// append nodes from back
	void pushBackNode(int new_data)
	{
		SHARED_PTR node = make_shared<SinglyLinkedListNode>(new_data);

		if (!tail)
			tail = node;
		else
			node->next = head;

		head = node;
	}

	// delete head node
	void deleteHead()
	{
		head = head->next;
	}

	// delete tail node
	void deleteTail()
	{
		SHARED_PTR curr = head;
		while (curr->next->next)
			curr = curr->next;
		curr->next = nullptr;
		tail = curr;
	}

	// delete middle node
	void deleteNode(SinglyLinkedListNode* node)
	{
		SHARED_PTR nextNode = node->next;
		node->data = nextNode->data;
		node->next = nextNode->next;
	}

	// print the complete list
	void printNodes(SHARED_PTR curr)
	{
		while (curr)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	// remove duplicate elements
	void removeDups()
	{
		// hashmap to contain set of unique elements
		unordered_set<int> list_elements;

		// remove duplicates and keep unique elements
		SHARED_PTR curr = head;
		SHARED_PTR prev = nullptr;
		while (curr)
		{
			if (list_elements.find(curr->data) == list_elements.end())
			{
				list_elements.insert(curr->data);
				prev = curr;
			}
			else
				prev->next = curr->next;

			curr = curr->next;
		}

		// print list elements
		printNodes(head);
	}

	// print elements from kth to the last one
	void printKthToLast(int k)
	{
		// set current node to head
		SHARED_PTR curr = head;

		// iterate and print
		cout << "From kth to last elements: ";
		int i = 1;
		while (curr && i < k)
		{
			i++;
			curr = curr->next;
		}
		printNodes(curr);
	}

	// print elements from start till k
	void printTillKth(int k)
	{
		// set current node to head
		SHARED_PTR curr = head;

		// iterate and print
		cout << "First k elements: ";
		int i = 1;
		while (curr && i <= k)
		{
			i++;
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	// find kth element from the last
	SHARED_PTR findKthFromLast(int k)
	{
		// initialize to count till k
		int count = 0;

		// pointers to find kth element
		SHARED_PTR ptr1 = head;
		SHARED_PTR ptr2 = head;

		// find kth element from start
		while (ptr1 && count < k)
		{
			ptr1 = ptr1->next;
			count++;
		}

		// find kth element from last
		while (ptr1)
		{
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}

		// return the kth from last element
		return ptr2;
	}

	// partition into two lists, given a partition point
	// elements smaller and greater than the given value separtated
	void partitionList(shared_ptr<SinglyLinkedList> lesser,
					   shared_ptr<SinglyLinkedList> greater, int pivot)
	{
		// make sure that the head nodes of new lists are null
		lesser->head = nullptr;
		greater->head = nullptr;

		// define a current node to traverse the list
		SHARED_PTR curr = this->head;

		// traverse the list while partitioning as needed
		while (curr)
		{
			if (curr->data < pivot)
				lesser->insertNode(curr->data);
			else
				greater->insertNode(curr->data);

			// move to the next node
			curr = curr->next;
		}

		// print the partitioned lists
		cout << "Partitioned lists:" << endl;
		lesser->printNodes(lesser->head);
		greater->printNodes(greater->head);
	}

	// reverse a linked list
	SHARED_PTR reverseListHead()
	{
		// head for the reversed list
		unique_ptr<SinglyLinkedList> reversedList = make_unique<SinglyLinkedList>();

		// current node to iterate through the original list
		SHARED_PTR curr = this->head;

		// iterate, reverse and clone
		while (curr)
		{
			reversedList->pushBackNode(curr->data);
			curr = curr->next;
		}

		// return head
		return reversedList->head;
	}

	// check if two lists are equal
	bool isEqual(SHARED_PTR reversedHead)
	{
		// make the two head variables
		SHARED_PTR head1 = head, head2 = reversedHead;
		
		// compare each node
		while (head1 && head2)
		{
			if (head1->data == head2->data)
			{
				head1 = head1->next;
				head2 = head2->next;
			}
			else
				return false;
		}

		// return true, otherwise
		return true;
	}

	// check if palindrome, using linked list functions
	bool isPalindrome() 
	{
		// reverse the list and check if equal
		return this->isEqual(this->reverseListHead());
	}

	// check if palindrome, using stack
	bool isPalindrome_usingStack()
	{
		// initialize stack to store elements in reverse order
		vector<int> reversedList;

		// pointer to the header node
		SHARED_PTR slow = head, fast = head;

		// store reversed list
		while (fast && fast->next)
		{
			reversedList.push_back(slow->data);
			slow = slow->next;
			fast = fast->next->next;
		}

		// if odd number of nodes, then skip middle node
		if (fast)
			slow = slow->next;

		// compare the two, element-wise
		while (slow)
		{
			if (reversedList.back() == slow->data)
			{
				reversedList.pop_back();
				slow = slow->next;
			}
			else
				return false;
		}

		// return true, otherwise
		return true;
	}

	// check if two linked lists are intersecting
	bool intersectsWith(SHARED_PTR secondTail) 
	{
		// if tail nodes are same
		if (tail == secondTail)
			return true;
		
		// else
		return false;
	}

	// find intersecting node
	SHARED_PTR intersectsAt(shared_ptr<SinglyLinkedList> secondList)
	{
		// check if there is an intersection
		if (!intersectsWith(secondList->tail))
			return NULL;

		// heads for two lists, first node is for the longer list, and second one for shorter list
		SHARED_PTR curr1 = (this->total_length > secondList->total_length) ? this->head : secondList->head;
		SHARED_PTR curr2 = (this->total_length > secondList->total_length) ? secondList->head : this->head;

		// starting node for longer list
		int startAt = abs(this->total_length - secondList->total_length);

		// find intersection point
		int index = 0;
		while (curr1 != curr2)
		{
			// catching up nodes, increment for shorter list only
			// after traversing the excess length in the longer list
			if (index >= startAt)
				curr2 = curr2->next;
			curr1 = curr1->next;		// increment for longer list
			index++;
		}
		
		// return intersecting node
		return curr1;
	}

	// loop detection, returns node where loop starts or NULL if no loop
	SHARED_PTR detectLoop()
	{
		// using a slow and a fast pointer
		SHARED_PTR slow = head;
		SHARED_PTR fast = head;

		// iterate through and check collision
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)			// collision
				break;
		}

		// if fast pointer or the next one is NULL, then no loop detected
		if (!fast || !fast->next)
			return nullptr;

		// find the start of loop
		// move the slow pointer to head node
		slow = head;
		while (slow != fast)			// they are both at equal steps from loop start
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		// return any one of them
		return slow;
	}
};

// construct linked list from user inputs
void inputList(shared_ptr<SinglyLinkedList> list)
{
	int n, data;
	cout << "Enter the desired length of the integer list: ";
	cin >> n;
	cout << "Enter the elements:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> data;
		list->insertNode(data);
	}
	cout << endl;
}

// entry point
int main()
{
	// declare linked lists
	shared_ptr<SinglyLinkedList> list1 = make_shared<SinglyLinkedList>();
	shared_ptr<SinglyLinkedList> list2 = make_shared<SinglyLinkedList>();

	// initiliaze linked lists
	inputList(list1);
	inputList(list2);

	// print the lists
	cout << "Given lists: " << endl;
	list1->printNodes(list1->head);
	list2->printNodes(list2->head);

	// reverse and print lists
	cout << endl << "Reversed lists:" << endl;
	list1->printNodes(list1->reverseListHead());
	list2->printNodes(list2->reverseListHead());

	// check if the list is palindrome
	cout << endl << "Check if given lists were palindrome..." << endl;
	cout << "List 1 - " << (list1->isPalindrome() ? "true" : "false") << endl;
	cout << "List 2 - " << (list2->isPalindrome() ? "true" : "false") << endl;

	// check if the list is palindrome, using stack
	cout << endl << "Check if given lists were palindrome... (using stack)" << endl;
	cout << "List 1 - " << (list1->isPalindrome_usingStack() ? "true" : "false") << endl;
	cout << "List 2 - " << (list2->isPalindrome_usingStack() ? "true" : "false") << endl;

	// check for intersection of two lists
	cout << endl << "Checking if the two lists intersect..." << endl;
	SHARED_PTR intersectingNode = list1->intersectsAt(list2);
	if (intersectingNode == NULL)
		cout << "No intersection exists!" << endl;
	else
		cout << "Intersection at value = " << intersectingNode->data << ", at address " << intersectingNode;

	/* check for presence of a loop	*/
	SHARED_PTR loopStart;
	cout << endl << "Checking if the lists have a loop..." << endl;

	// list 1
	cout << "List 1: ";
	loopStart = list1->detectLoop();
	if (loopStart == NULL)
		cout << "No loop exists!" << endl;
	else
		cout << "Loop starts at value = " << loopStart->data << ", at address " << loopStart;

	// list 2
	cout << "List 2: ";
	loopStart = list2->detectLoop();
	if (loopStart == NULL)
		cout << "No loop exists!" << endl;
	else
		cout << "Loop starts at value = " << loopStart->data << ", at address " << loopStart;

	// remove head node
	list1->deleteHead();

	//remove tail node
	list2->deleteTail();

	// print the lists again
	cout << endl << "Removed head from list 1 and tail from list 2: " << endl;
	list1->printNodes(list1->head);
	list2->printNodes(list2->head);

	// remove duplicates and print
	cout << endl << "After removing duplicates: " << endl;
	list1->removeDups();
	list2->removeDups();

	// print kth to last element
	int k;
	cout << endl << "Enter index k to print elements from: ";
	cin >> k;
	list1->printKthToLast(k);
	list2->printKthToLast(k);

	// print kth to last element
	cout << endl << "Enter index k to print elements till: ";
	cin >> k;
	list1->printTillKth(k);
	list2->printTillKth(k);

	// find and print kth from last element
	cout << endl << "Enter index k to print element from the end: ";
	cin >> k;
	cout << "Required element from list 1: " << list1->findKthFromLast(k)->data << endl;
	cout << "Required element from list 2: " << list2->findKthFromLast(k)->data << endl;

	/*	partition the list into two lists, given a partition data
		new lists contain lesser and greater data, respectively	*/
	shared_ptr<SinglyLinkedList> lesser_nodes = make_shared<SinglyLinkedList>();
	shared_ptr<SinglyLinkedList> greater_nodes = make_shared<SinglyLinkedList>();

	// list 1
	cout << endl << "Enter the partition pivot data for list 1: ";
	cin >> k;
	list1->partitionList(lesser_nodes, greater_nodes, k);

	// list 2
	cout << endl << "Enter the partition pivot data for list 2: ";
	cin >> k;
	list2->partitionList(lesser_nodes, greater_nodes, k);

	// END
	cout << endl << "----------- END OF CODE -----------" << endl;

	// just in case, as the output might quickly disappear
	cin.get();
}