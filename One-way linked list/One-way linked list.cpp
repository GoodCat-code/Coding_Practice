#include <iostream>
using namespace std;

template<typename T>
class List {
public:
	List();
	~List();
	void push_back(T data);
	void push_front(T data);
	void print();
	void print(int num);
	void delete_Node(int num);

private:
	struct Node {
		T data;
		Node *ptr_next;

		Node(T data) : data(data), ptr_next(nullptr) {}
	};

	int Size;
	Node *head;
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
};

template<typename T>
List<T>::~List()
{
	while (head != nullptr)
	{
		Node *curr_ptr = head;
		head = curr_ptr->ptr_next;
		delete curr_ptr;
	}
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node(data);
		Size++;
	}
	else
	{
		Node* curr_ptr = this->head;

		while (curr_ptr->ptr_next != nullptr)
		{
			curr_ptr = curr_ptr->ptr_next;
		}
		
		curr_ptr->ptr_next = new Node(data);
		Size++;
	}
};

template<typename T>
void List<T>::push_front(T data) {
	Node* curr_ptr = this->head;
	if (curr_ptr == nullptr)
	{
		head = new Node(data);
		Size++;
	}
	else
	{
		curr_ptr = new Node(data);
		curr_ptr->ptr_next = head;
		head = curr_ptr;
		Size++;
	}
}

template<typename T>
void List<T>::print()
{
	int iter = 0;
	Node* curr_ptr = this->head;

	while (iter != List::Size)
	{
		cout << curr_ptr->data << "\t";
		cout << curr_ptr->ptr_next << endl;
		curr_ptr = curr_ptr->ptr_next;
		iter++;
	}
}

template<typename T>
void List<T>::print(int num)
{
	if (num >= Size)
	{
		cout << "Index out of range" << endl;
		return;
	}
	Node* curr_ptr = this->head;

	for (int i = 0; i< List::Size; i++)
	{
		if (i == num)
		{
			cout << curr_ptr->data << "\t" << curr_ptr->ptr_next << endl;
			break;
		}
		curr_ptr = curr_ptr->ptr_next;
	}
}

template<typename T>
void List<T>::delete_Node(int num)
{
	if (num >= Size)
	{
		cout << "Index out of range" << endl;
		return;
	}
	Node* curr_ptr = this->head;
	for (int i = 0; i < List::Size; i++)
	{
		if (num == 0)
		{
			head = curr_ptr->ptr_next;
			delete curr_ptr;
			break;
		}
		else if ( (i+1) == num)
		{
			Node* next_node = curr_ptr->ptr_next;
			curr_ptr->ptr_next = next_node->ptr_next;
			delete next_node;
			break;
		}
		curr_ptr = curr_ptr->ptr_next;
	}
	Size--;
}


int main()
{
	List<int> Lst;
	Lst.push_back(12);
	Lst.push_back(24);
	Lst.push_back(30);
	Lst.push_front(01);
	Lst.print();
	Lst.delete_Node(1);
	cout << "=====" << endl;
	Lst.print();
	cout << "=====" << endl;
	Lst.print(1);
}
