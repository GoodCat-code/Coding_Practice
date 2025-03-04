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
	void Print();

private:
	int Size;
	size_t Capacity;
	T* H_arr;
	void Resize(size_t new_capacity);
	void H_rework_up();
	void H_rework_dw(int index = 0);
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
	cout << "destruction";
	delete[] H_arr;
	cout << "end_destruction";
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
	H_rework_up();
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
	//H_arr[Size] = temp;
	Size--;

	if (Size > 1)
		H_rework_dw();

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
	T* temp_arr = new T[new_capacity];
	for (int i = 0; i < Size; i++)
		temp_arr[i] = H_arr[i];

	delete[] H_arr;
	H_arr = temp_arr;
	Capacity = new_capacity;
}

template<typename T>
void Heap<T>::H_rework_up()
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
void Heap<T>::H_rework_dw(int index)
{
	T temp;
	//cout << index << endl;
	//cout << H_arr[index] << "\t" << H_arr[2 * index + 1] << "\t" << H_arr[2 * index + 2] << endl;
	//Heap::Print();

	while ((2 * index + 1) < Size || (2 * index + 2) < Size)
	{
		if (H_arr[index] >= H_arr[2 * index + 1])
		{
			//cout << H_arr[index] << "\t" << H_arr[2 * index + 1] << endl;
			temp = H_arr[index];
			H_arr[index] = H_arr[2 * index + 1];
			H_arr[2 * index + 1] = temp;
			H_rework_dw(index += 1);
		}
		else if (H_arr[index] >= H_arr[2 * index + 2])
		{
			//cout << H_arr[index] << "\t" << H_arr[2 * index + 2] << endl;
			temp = H_arr[index];
			H_arr[index] = H_arr[2 * index + 2];
			H_arr[2 * index + 2] = temp;
			H_rework_dw(index += 2);
		}
		else return;
	}

}

int main()
{
	Heap<int> Hp;

	cout << Hp.ExtractMin() << endl;
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
