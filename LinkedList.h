#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class LinkedList {
public:
	//Nested Struct Node
	struct Node {
		Node(const T &d) {
			data = d;
		}
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};
//**------------------------Accessor Functions-------------------**
	//Print Nodes in 'Forward' Direction
	void PrintForward() const {
		//Create Node to iterate through
		Node *currentNode = head;
		do { //Iterate through Node print data
			cout << currentNode->data << endl;
			currentNode = currentNode->next;
		} while (currentNode != nullptr);
	}

	//Print Nodes in 'Reverse' Direction
	void PrintReverse() const {
		// Create Node to iterate through
		Node *currentNode = tail; //This time start at head and move back
			do {
			cout << currentNode->data << endl;
			currentNode = currentNode->prev;
			} while (currentNode != nullptr);
	}
	
	//Return Number of Nodes
	unsigned int NodeCount() const {
		return numNodes;
	}
	//Find all Nodes
	void FindAll(vector <Node*> &outData, const T &value) const {
		Node *currentNode = head;
		for (int i = 0; i < numNodes; i++) {
			if (currentNode->data == value) {
				outData.push_back(currentNode);
			}
			currentNode = currentNode->next;
		}
	}
	//Find  Method
	Node *Find(const T& data) const{
		Node *currentNode = head;
		do { //Execute as long as currentNode is not nullptr
			if (currentNode->data == data) {
				break;
			}
			currentNode = currentNode->next;
		} while (currentNode != nullptr);
		if (currentNode != nullptr) {
			return currentNode;
		}
		return nullptr;
	}
	
	//GetNode
	Node *GetNode(unsigned int index) {
		unsigned int numNodes1 = numNodes;
		if (index > numNodes1) { //If index is out of range
			throw "No such Index";
		}
		else {
			unsigned int indexCounter = 0;
			Node *currentNode = head;
			do {
				currentNode = currentNode->next;
				indexCounter++;
			} while (indexCounter != index);
			return currentNode;
		}
	}

	//Get Head Methods
	Node *Head() {
		return head;
	}
	const Node *Head() const {
		return head;
	}

	//Get Tail Methods
	Node *Tail() {
		return tail;
	}
	const Node *Tail() const {
		return tail;
	}

//**-------------Insertion Operations------------------------**
	//AddHead Method
	void AddHead(const T &data) {
		//Create Temporary Node to Assess
		Node *tempNode = new Node(data);
		if (head != nullptr) { // Check if Head is null, if not next becomes head
			tempNode->next = head;
			head->prev = tempNode;
		}
		else if (head == nullptr) { // If Head is null then tail becomes the tempNode
			tail = tempNode;
		}
		head = tempNode;
		numNodes++; //Increment nodes since we are adding to head
	}

	//AddTail Method -- Similar to Head Just Swap with Tail now
	void AddTail(const T& data) {
		Node *tempNode = new Node(data);
		if (head == nullptr || tail == nullptr) { //Check both ends are not null
			head = tempNode;
			tail = tempNode;
		}
		else if (tail != nullptr) {
			tail->next = tempNode;
			tempNode->prev = tail;
			tail = tempNode;
		}
		numNodes++; //Increment nodes since adding to tail
	}

	//AddNodesHead Method
	void AddNodesHead(const T *data, unsigned int count) {
		int index = count - 1;
		//Iterate through array (beginning at bottom) and call AddHead for each index
		for (int i = index; i >= 0; --i) {
			AddHead(data[i]);
			numNodes++; //Update Node Count
		}
	}
	
	//AddNodesTail Method
	void AddNodesTail(const T *data, unsigned int count) {
		//Iterate through array (from top) and call AddTail
		for (unsigned int i = 0; i < count; ++i) {
			AddTail(data[i]);
			numNodes++; //Update Node Count
		}
	}

	//InsertAfter Method
	void InsertAfter(Node *node, const T &data) {
		if (node == head) {
			AddHead(data);
		}
		else if (node == tail) {
			AddTail(data);
		}
		else {
			//Create New Node
			Node *newNode = new Node(data);
			//Update this node
			newNode->next = node->next;
			node->next->prev = newNode;
			node->next = newNode;
			newNode->prev = node;
			numNodes++;
		}
	}

	//InsertBefore Method
	void InsertBefore(Node *node, const T &data) {
		if (node == head) { 
			AddHead(data);
		}
		else if (node == tail) {
			AddTail(data);
		}
		else {
			//Create New Node
			Node *newNode = new Node(data);
			//Update this node
			newNode->next = node;
			node->prev->next = newNode;
			newNode->prev = node->prev;
			node->prev = newNode;
			numNodes++;
		}
	}

	//InsertAt method
	void InsertAt(const T& data, int index) {
		Node *currentNode = head;
		for (int i = 1; i < index && currentNode != nullptr; ++i) {
			currentNode = currentNode->next;
		}
		if (currentNode != nullptr)	{
			InsertAfter(currentNode, data);
		}
		else
			throw "No such index";
	}
//**----------------------------Removal-------------------------**
	//RemoveHead method
	bool RemoveHead() {
		Node *removedNode = head;
		if (head != nullptr) {
			head = head->next;
			if (head != nullptr) { //Checks if last element remaining
				head->prev = nullptr;
			}
		}
		else { //If head is nullptr
			return false; //Operation Failed, return false
		}
		delete removedNode;
		numNodes--; // Update Node Count
		return true; //If operation successful return true
	}
	
	//RemoveTail
	bool RemoveTail() {
		// Checks if empty
		if (tail == nullptr) {
			return false; //Operation Failed, return false
		}
		// Checks for final element in list
		else if (tail->prev == nullptr) {
			Node *removedNode = tail;
			delete removedNode;
			tail = nullptr;
			head = nullptr;
			numNodes--;
			return true; //Operation successful, return true
		}
		else {
			Node *removedNode = tail;
			tail->prev->next = nullptr;
			tail = tail->prev;
			delete removedNode;
			numNodes--;
			return true; //Operation successful, return true
		}
	}

	//Remove Method
	unsigned int Remove(const T &data) {
		Node *currentNode = head;
		int numNodesDeleted = 0;
		while (currentNode != nullptr) {
			if (currentNode->data == data) {
				currentNode->prev->next = currentNode->next;
				currentNode->prev->next->prev = currentNode->prev;
				Node *removedNode = currentNode;
				currentNode = currentNode->prev;
				delete removedNode;
				numNodesDeleted++;
			}
			currentNode = currentNode->next;
		}
		//Update Node Count
		numNodes -= numNodesDeleted; //Removes amount of nodes that were deleted from numNodes
		return numNodesDeleted;
	}

	//RemoveAt Method
	bool RemoveAt(int index) {
		Node *currentNode = head;
		for (int i = 0; i < index && currentNode != nullptr; ++i) {
			currentNode = currentNode->next;
		}
		if (currentNode != nullptr) {
			if (currentNode == head) {
				RemoveHead();
			}
			else if (currentNode == tail) {
				RemoveTail();
			}
			else {
				Node *removedNode = currentNode;
				currentNode = currentNode->prev;
				currentNode->next = currentNode->next->next;
				currentNode->next->prev = currentNode;
				delete removedNode;
			}
		}
		else {
			return false; //Operation failed, return false
		}
		numNodes--; // Update Node Count
		return true; //Operation successful, return true.
	}

	//Clear Method
	void Clear() {
		while (head != nullptr) {
			Node* removedNode = head;
			head = head->next;
			delete removedNode;
		} 
		numNodes = 0;
		head = nullptr;
		tail = nullptr;
	}
//**---------------------Operators---------------------------------**//
	const T &operator[] (unsigned int index) const {
		if (index > numNodes) {
			throw "No such index";
		}
		else {
			unsigned int numIndex = 0;
			Node *currentNode = head;
			while (numIndex != index) {
				currentNode = currentNode->next;
				numIndex++;
			}
			return currentNode->data;
		}
	}

	T &operator[] (unsigned int index) {
		int indexVal = index;
		if (indexVal > numNodes) {
			throw "No such index";
		}
		else {
			unsigned int numIndex = 0;
			Node *currentNode = head;
			while (numIndex != index) {
				currentNode = currentNode->next;
				numIndex++;
			}
			return currentNode->data;
		}
	}
	bool operator==(const LinkedList<T> &rhs) const {
		bool equalCheck = true;
		if (numNodes != rhs.numNodes) { //Check if numNodes are equal
			return false;
		}
		Node *currentNode = head;
		Node *currentNode2 = rhs.head;
		do {
			if (currentNode->data != currentNode2->data) {
				equalCheck = false;
			}
			currentNode = currentNode->next;
			currentNode2 = currentNode2->next;
		} while (currentNode != nullptr && currentNode2 != nullptr);
		return equalCheck;
	}

	LinkedList<T> &operator=(const LinkedList<T>& rhs) {
		Node* currentNode = rhs.head;
		do {
			AddTail(currentNode->data);
			currentNode = currentNode->next;
		} while (currentNode != nullptr);
		numNodes = rhs.numNodes;
		return *this;
	}

//**------------------Constructor/Destructor--------------------------------------**
	//Default Constructor for LinkedList
	LinkedList() {
		numNodes = 0;
		head = nullptr;
		tail = nullptr;
	}
	//Copy Constructor
	LinkedList(LinkedList<T> &d) {
		Node *currentNode = d.head;
		do {
			AddTail(currentNode->data);
			currentNode = currentNode->next;
		} while (currentNode != nullptr);
		numNodes = d.numNodes;
	}
	//Destructor
	~LinkedList() {
		Clear();
	}
	Node *head{ nullptr };
	Node *tail{ nullptr };
	int numNodes{ 0 };
};