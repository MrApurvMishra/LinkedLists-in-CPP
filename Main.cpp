/*	Implementation of Linked Lists in C++,
*	Along with multiple functions/manipulations
*	(based on 'Cracking the Coding Interview' by Gayle Laakmann McDowell)
*
*	Author: Apurv Mishra (mr.mishra1408@gmail.com)	*/

// include necessary header files
#include <iostream>
#include <unordered_set>
#include <memory>

// define initialization macro for smart pointers
#define SHARED_PTR std::shared_ptr<SinglyLinkedListNode>

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

	// initialize with head and tail nodes
	SinglyLinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}

	// append nodes from front
	void insertNode(int new_data)
	{
		SHARED_PTR node = std::make_shared<SinglyLinkedListNode>(new_data);

		if (!head)
			head = node;
		else
			tail->next = node;

		tail = node;
	}

	// append nodes from back
	void pushBackNode(int new_data)
	{
		SHARED_PTR node = std::make_shared<SinglyLinkedListNode>(new_data);

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
			std::cout << curr->data << " ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}

	// remove duplicate elements
	void removeDups()
	{
		// hashmap to contain set of unique elements
		std::unordered_set<int> list_elements;

		// remove duplicates and keep unique elements
		SHARED_PTR curr = this->head;
		SHARED_PTR prev = nullptr;
		while (curr)
		{
			if (list_elements.find(curr->data) == list_elements.end())
			{
				list_elements.insert(curr->data);
				prev = curr;
			}
			else
			{
				prev->next = curr->next;
			}
			curr = curr->next;
		}

		// print list elements
		this->printNodes(this->head);
	}

	// print elements from kth to the last one
	void printKthToLast(int k)
	{
		// set current node to head
		SHARED_PTR curr = this->head;

		// iterate and print
		std::cout << "From kth to last elements: ";
		int i = 1;
		while (curr && i < k)
		{
			i++;
			curr = curr->next;
		}
		this->printNodes(curr);
	}

	// print elements from start till k
	void printTillKth(int k)
	{
		// set current node to head
		SHARED_PTR curr = this->head;

		// iterate and print
		std::cout << "First k elements: ";
		int i = 1;
		while (curr && i <= k)
		{
			i++;
			std::cout << curr->data << " ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}

	// find kth element from the last
	SHARED_PTR findKthFromLast(int k)
	{
		// initialize to count till k
		int count = 0;

		// pointers to find kth element
		SHARED_PTR ptr1 = this->head;
		SHARED_PTR ptr2 = this->head;

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
	void partitionList(std::shared_ptr<SinglyLinkedList> lesser,
					   std::shared_ptr<SinglyLinkedList> greater, int pivot)
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
			{
				lesser->insertNode(curr->data);
			}
			else
			{
				greater->insertNode(curr->data);
			}

			// move to the next node
			curr = curr->next;
		}

		// print the partitioned lists
		std::cout << "Partitioned lists:" << std::endl;
		lesser->printNodes(lesser->head);
		greater->printNodes(greater->head);
	}

	// reverse a linked list
	SHARED_PTR reverseListHead()
	{
		// head for the reversed list
		std::unique_ptr<SinglyLinkedList> reversedList = std::make_unique<SinglyLinkedList>();

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
		SHARED_PTR head1 = this->head, head2 = reversedHead;
		
		// compare each node
		while (head1 && head2)
		{
			if (head1->data == head2->data)
			{
				head1 = head1->next;
				head2 = head2->next;
			}
			else
			{
				return false;
			}
		}

		// return true, otherwise
		return true;
	}

	// check if palindrome, using stack
	bool isPalindrome() 
	{
		// reverse the list and check if equal
		return this->isEqual(this->reverseListHead());
	}
};

// construct linked list from user inputs
void inputList(std::shared_ptr<SinglyLinkedList> list)
{
	int n, data;
	std::cout << "Enter the desired length of the integer list: ";
	std::cin >> n;
	std::cout << "Enter the elements:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cin >> data;
		list->insertNode(data);
	}
	std::cout << std::endl;
}

// entry point
int main()
{
	// declare linked lists
	std::shared_ptr<SinglyLinkedList> list1 = std::make_shared<SinglyLinkedList>();
	std::shared_ptr<SinglyLinkedList> list2 = std::make_shared<SinglyLinkedList>();

	// initiliaze linked lists
	inputList(list1);
	inputList(list2);

	// print the lists
	std::cout << "Given lists: " << std::endl;
	list1->printNodes(list1->head);
	list2->printNodes(list2->head);

	// reverse and print lists
	std::cout << std::endl << "Reversed lists:" << std::endl;
	list1->printNodes(list1->reverseListHead());
	list2->printNodes(list2->reverseListHead());

	// check if the list is palindrome
	std::cout << std::endl << "Check if given lists were palindrome..." << std::endl;
	std::cout << "List 1 - " << (list1->isPalindrome() ? "true" : "false") << std::endl;
	std::cout << "List 2 - " << (list2->isPalindrome() ? "true" : "false") << std::endl;

	// remove duplicates and print
	std::cout << std::endl << "After removing duplicates: " << std::endl;
	list1->removeDups();
	list2->removeDups();

	// remove head node
	list1->deleteHead();

	//remove tail node
	list2->deleteTail();

	// print the lists again
	std::cout << std::endl << "Removed head from list 1 and tail from list 2: " << std::endl;
	list1->printNodes(list1->head);
	list2->printNodes(list2->head);

	// print kth to last element
	int k;
	std::cout << std::endl << "Enter index k to print elements from: ";
	std::cin >> k;
	list1->printKthToLast(k);
	list2->printKthToLast(k);

	// print kth to last element
	std::cout << std::endl << "Enter index k to print elements till: ";
	std::cin >> k;
	list1->printTillKth(k);
	list2->printTillKth(k);

	// find and print kth from last element
	std::cout << std::endl << "Enter index k to print element from the end: ";
	std::cin >> k;
	std::cout << "Required element from list 1: " << list1->findKthFromLast(k)->data << std::endl;
	std::cout << "Required element from list 2: " << list2->findKthFromLast(k)->data << std::endl;

	/*	partition the list into two lists, given a partition data
		new lists contain lesser and greater data, respectively	*/
	std::shared_ptr<SinglyLinkedList> lesser_nodes = std::make_shared<SinglyLinkedList>();
	std::shared_ptr<SinglyLinkedList> greater_nodes = std::make_shared<SinglyLinkedList>();

	// list 1
	std::cout << std::endl << "Enter the partition pivot data for list 1: ";
	std::cin >> k;
	list1->partitionList(lesser_nodes, greater_nodes, k);

	// list 2
	std::cout << std::endl << "Enter the partition pivot data for list 2: ";
	std::cin >> k;
	list2->partitionList(lesser_nodes, greater_nodes, k);

	// END
	std::cout << std::endl << "----------- END OF CODE -----------" << std::endl;

	// just in case, as the output might quickly disappear
	std::cin.get();
}