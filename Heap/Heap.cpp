#include <iostream>
using namespace std;

template<typename T>
class Heap {
public:
	Heap();
	~Heap();
	bool IsEmpty();
	void Insert(T value);
	T ExtractMin();
	T PeekMin();
	void Print(); // for debug

private:
	size_t Size;
	size_t Capacity;
	T* H_arr;
	void Resize(size_t new_capacity);
	void ReworkUp();
	void ReworkDw(int index = 0);
};

template<typename T>
Heap<T>::Heap()
{
	Size = 0;
	Capacity = 4;
	H_arr = new T[Capacity];
}

template<typename T>
Heap<T>::~Heap()
{
	delete[] H_arr;
}

template<typename T>
bool Heap<T>::IsEmpty()
{
	return !Size;;
}

template<typename T>
void Heap<T>::Insert(T value)
{
	if (Size == Capacity)
		Resize(Capacity * 2);

	H_arr[Size] = value;
	ReworkUp();
	Size++;
}

template<typename T>
T Heap<T>::ExtractMin()
{
	if (IsEmpty())
		throw out_of_range("Heap is empty");
	if (Size < Capacity / 2)
		Resize(Capacity / 2);

	T temp = H_arr[0];
	H_arr[0] = H_arr[Size - 1];
	Size--;

	if (Size > 1) // rework excludes for empty and 1 element array
		ReworkDw();

	return temp;
}

template<typename T>
T Heap<T>::PeekMin()
{
	return H_arr[0];
}

template<typename T>
void Heap<T>::Print()
{
	int i = 0;
	while (i < Size)
	{
		cout << H_arr[i] << "\t";
		i++;
	}
	cout << endl;
}

template<typename T>
void Heap<T>::Resize(size_t new_capacity)
{
	if (new_capacity < Size) return; // just for best practice, there are necessary checks in methods

	T* temp_arr = new T[new_capacity];
	for (int i = 0; i < Size; i++)
		temp_arr[i] = H_arr[i];

	delete[] H_arr;
	H_arr = temp_arr;
	Capacity = new_capacity;
}

template<typename T>
void Heap<T>::ReworkUp()
{
	T temp;
	int index = Size;
	while (H_arr[index] < H_arr[(index - 1) / 2])
	{
		temp = H_arr[(index - 1) / 2];
		H_arr[(index - 1) / 2] = H_arr[index];
		H_arr[index] = temp;
		index = (index - 1) / 2;
	}

}

template<typename T>
void Heap<T>::ReworkDw(int index) // recursive
{
	T temp;

	while ((2 * index + 1) < Size || (2 * index + 2) < Size) // check index's value
	{
		if (H_arr[index] >= H_arr[2 * index + 1])
		{
			temp = H_arr[index];
			H_arr[index] = H_arr[2 * index + 1];
			H_arr[2 * index + 1] = temp;
			ReworkDw(index += 1);
		}
		else if (H_arr[index] >= H_arr[2 * index + 2])
		{
			temp = H_arr[index];
			H_arr[index] = H_arr[2 * index + 2];
			H_arr[2 * index + 2] = temp;
			ReworkDw(index += 2);
		}
		else return;
	}

}

int main()
{
	Heap<int> Hp;

	try
	{
		Hp.ExtractMin();
	}
	catch (exception e)
	{
		cout << e.what();
	};

	Hp.Print();

	cout << Hp.IsEmpty() << endl;

	Hp.Insert(10);
	Hp.Print();

	Hp.Insert(9);
	Hp.Print();

	Hp.Insert(8);
	Hp.Print();
	
	cout << Hp.ExtractMin() << endl;
	Hp.Print();

	Hp.Insert(20);
	Hp.Print();

	cout << Hp.PeekMin() << endl;
	cout << Hp.IsEmpty() << endl;
	Hp.Print();

	Hp.Insert(13);
	Hp.Print();

	Hp.Insert(7);
	Hp.Print();

	cout << Hp.ExtractMin() << endl;
	Hp.Print();

}
