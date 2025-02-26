#include <iostream>
using namespace std;

template<typename T>
class Queue {
public:
	Queue();
	~Queue();
	void Print();

	void Enqueue(T data);
	void Dequeue();
	T Front() const;
	size_t Size() const;
	bool IsEmpty() const;
private:
	bool Tale_occupied;
	int Qu_size;
	int Outs;
	int Inputs;
	T* Tale;
	T* Qu_arr;

	void Resize(int new_size);
};

template<typename T>
Queue<T>::Queue()
{
	Tale_occupied = false;
	Qu_size = 2;
	Outs = 0;
	Inputs = 0;
	Qu_arr = new T[Qu_size];
	Tale = &Qu_arr[Qu_size - 1];
}

template<typename T>
Queue<T>::~Queue()
{
	delete[] Qu_arr;
}

template<typename T>
void Queue<T>::Print()
{
	cout << "Array is: ";
	for (int i = 0; i < Qu_size; i++)
		cout << Qu_arr[i] << "\t";
	cout << endl;
}

template<typename T>
void Queue<T>::Resize(int new_size)
{
	T* temp_arr = new T[new_size];

	if (Outs != 0)
	{
		temp_arr[0] = Qu_arr[Outs];
		for (int i = 0; i < Outs; i++)
			temp_arr[i+1] = Qu_arr[i];
		for (int i = Outs + 1; i <= Qu_size; i++)
			temp_arr[i] = Qu_arr[i];
		Outs = 0;
	}
	else
	{
		for (int i = 0; i < Qu_size; i++)
			temp_arr[i] = Qu_arr[i];
	}
	
	Qu_size = new_size;
	delete[] Qu_arr;
	Qu_arr = temp_arr;
	Tale = &Qu_arr[Qu_size - 1];
	Tale_occupied = false;
}

template<typename T>
void Queue<T>::Enqueue(T data)
{
	int index;

	if (!Tale_occupied || (Inputs - Outs) == Qu_size)
		index = Inputs - Outs;
	else
		index = Inputs - Qu_size;

	if ((Inputs - Outs) == 0)
	{
		Qu_arr[0] = data;
	}
	else if ((Inputs - Outs) != Qu_size)
	{
		Qu_arr[index] = data;
		if (Tale == &Qu_arr[index])
			Tale_occupied = true;
	}
	else
	{
		Resize(Qu_size * 2);
		Qu_arr[index] = data;
	}
	
	Inputs++;
}

template<typename T>
void Queue<T>::Dequeue()
{
	if (!IsEmpty())
	{
		if (Tale == &Qu_arr[Outs])
		{
			Inputs -= Outs + 1;
			Outs = 0;
			Tale_occupied = false;
		}
		else Outs++;
	}
	else
	{
		Tale_occupied = false;
	}

	if ((Inputs - Outs) < Qu_size / 4)
		Resize(Qu_size / 2);

	cout << endl << "Element has been deleted" << endl << endl;
}

template<typename T>
T Queue<T>::Front() const
{
	if (IsEmpty())
		throw out_of_range("Queue is empty");
	return Qu_arr[Outs];
}

template<typename T>
size_t Queue<T>::Size() const
{
	return Inputs - Outs;
}

template<typename T>
bool Queue<T>::IsEmpty() const
{
	return !(Inputs - Outs);
}

int main()
{
	Queue<int> Que;

	//Que.Enqueue(7);
	//Que.Print();
	//cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	//Que.Enqueue(11);
	//Que.Print();
	//cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	Que.Dequeue();
	//cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	Que.Enqueue(22);
	Que.Print();
	cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	//Que.Dequeue();
	//cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	Que.Enqueue(33);
	Que.Print();
	cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;

	Que.Dequeue();
	cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;
	
	Que.Enqueue(44);
	Que.Print();
	cout << "Head is: " << Que.Front() << "\t" << "Size is: " << Que.Size() <<endl;
}
