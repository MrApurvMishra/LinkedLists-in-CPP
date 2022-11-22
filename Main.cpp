#include <iostream>
#include <unordered_set>
#include <memory>

// Linked list node class
class SinglyLinkedListNode
{
public:
	int data;
	std::shared_ptr<SinglyLinkedListNode> next;

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
	std::shared_ptr<SinglyLinkedListNode> head;
	std::shared_ptr<SinglyLinkedListNode> tail;

	// initialize with head and tail nodes
	SinglyLinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}

	// append nodes
	void insertNode(int new_data)
	{
		std::shared_ptr<SinglyLinkedListNode> node = std::make_shared<SinglyLinkedListNode>(new_data);

		if (!head)
			head = node;
		else
			tail->next = node;

		tail = node;
	}

	// delete head node
	void deleteHead()
	{
		head = head->next;
	}

	void deleteTail()
	{
		std::shared_ptr<SinglyLinkedListNode> curr = head;
		while (curr->next->next)
			curr = curr->next;
		curr->next = nullptr;
		tail = curr;
	}

	// delete middle node
	void deleteNode(SinglyLinkedListNode* node)
	{
		std::shared_ptr<SinglyLinkedListNode> nextNode = node->next;
		node->data = nextNode->data;
		node->next = nextNode->next;
	}

	// print the complete list
	void printNodes(std::shared_ptr<SinglyLinkedListNode> curr)
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
		std::shared_ptr<SinglyLinkedListNode> curr = this->head;
		std::shared_ptr<SinglyLinkedListNode> prev = nullptr;
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
		std::shared_ptr<SinglyLinkedListNode> curr = this->head;

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
		std::shared_ptr<SinglyLinkedListNode> curr = this->head;

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
	std::shared_ptr<SinglyLinkedListNode> findKthFromLast(int k)
	{
		// initialize to count till k
		int count = 0;

		// pointers to find kth element
		std::shared_ptr<SinglyLinkedListNode> ptr1 = this->head;
		std::shared_ptr<SinglyLinkedListNode> ptr2 = this->head;

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
	void partitionList(std::shared_ptr<SinglyLinkedList> lesser, std::shared_ptr<SinglyLinkedList> greater, int pivot)
	{
		// make sure that the head nodes of new lists are null
		lesser->head = nullptr;
		greater->head = nullptr;

		// define a current node to traverse the list
		std::shared_ptr<SinglyLinkedListNode> curr = this->head;

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
}