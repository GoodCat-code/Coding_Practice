#include <iostream>
using namespace std;

template<typename T>
class Stack {
public:
	Stack();
	~Stack();

	void Push(T data);
	void Pop();
	T Top() const;
	size_t Size() const;
	bool Is_empty() const;

private:
	int Size_arr;
	int Filled_el;
	T *Stack_arr;
	void Resize(int new_size);

};

template<typename T>
Stack<T>::Stack()
{
	Size_arr = 2;
	Filled_el = 0;
	Stack_arr = new T[Size_arr];
}

template<typename T>
Stack<T>::~Stack()
{
	delete[] Stack_arr;
}

template<typename T>
void Stack<T>::Resize(int new_size)
{
	T *temp_arr = new T[new_size];

	for (int i = 0; i < Filled_el; i++)
		temp_arr[i] = Stack_arr[i];

	delete[] Stack_arr;
	Stack_arr = temp_arr;
	Size_arr = new_size;
}

template<typename T>
size_t Stack<T>::Size() const
{
	return Filled_el;
}

template<typename T>
bool Stack<T>::Is_empty() const
{
	return Filled_el == 0;
}

template<typename T>
void Stack<T>::Push(T data)
{
	Stack_arr[Filled_el] = data;
	Filled_el++;
	if (Size_arr == Filled_el) // in theory should be placed upper then adding element, but for this is not
		Resize(Size_arr * 2);
}

template<typename T>
void Stack<T>::Pop()
{
	if (Filled_el > 0)
		Filled_el--;

	if (Filled_el < Size_arr / 4) // in theory Size_arr also shouldn'be < 2, but for this is not
		Resize(Size_arr / 2);
}

template<typename T>
T Stack<T>::Top() const
{
	if (Filled_el > 0)
		return Stack_arr[Filled_el - 1];
	else throw out_of_range("Stack is empty");
}

int main()
{
	Stack<int> Stk;

	Stk.Push(10);
	Stk.Push(17);
	Stk.Push(22);
	cout << Stk.Top() << endl;
	Stk.Push(33);
	Stk.Push(34);
	Stk.Push(35);
	Stk.Push(36);
	Stk.Push(37);
	cout << Stk.Top() << endl;
	Stk.Pop();
	cout << Stk.Top() << endl;
	Stk.Push(44);
	for (int i = 7; i > 0; i--)
		Stk.Pop();
	cout << Stk.Top() << endl;
	Stk.Push(37);
	cout << Stk.Is_empty();

}

