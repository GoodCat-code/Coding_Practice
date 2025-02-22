#include <iostream>
using namespace std;

template<typename T>
class List {
public:
   List();
   ~List();
   void push_front(T data);
   void print_forward();
   void push_back(T data);
   void print_backward();
   void pop_front();
   void pop_back();
   void print_is_empty();

private:
   class Node {
   public:
      T data;
      Node *prev_ptr;
      Node *next_ptr;

      Node(T data, Node* prev = nullptr, Node* next = nullptr): data(data), prev_ptr(prev), next_ptr(next) {};
   };

   int Size;
   Node *Head;
   Node *Tale;
};

template<typename T>
List<T>::List()
{
   Size = 0;
   Head = nullptr;
   Tale = nullptr;
}

template<typename T>
List<T>::~List()
{
   while (Head != nullptr)
   {
      pop_front();
   }
}

template<typename T>
void List<T>::push_front(T data)
{
   if (Head == nullptr)
   {
      Head = new Node(data);
      Tale = Head;
   }
   else
   {
      Node* curr_node = Head;
      Head = new Node(data, nullptr, Head);
      curr_node->prev_ptr = Head;
   }
   Size++;
}

template<typename T>
void List<T>::print_forward()
{
   if (Head == nullptr)
      print_is_empty();
   else
   {
      Node *curr_node = Head;
      while (curr_node != nullptr)
      {
         cout << curr_node->data << "\t";
         curr_node = curr_node->next_ptr;
      }
   }
   cout << endl;
}

template<typename T>
void List<T>::push_back(T data)
{
   if (Tale == nullptr)
   {
      Tale = new Node(data);
      Head = Tale;
   }
   else
   {
      Node* curr_node = Tale;
      Tale = new Node(data, curr_node);
      curr_node->next_ptr = Tale;
   }
   Size++;
}

template<typename T>
void List<T>::print_backward()
{
   if (Tale == nullptr)
      print_is_empty();
   else
   {
      Node *curr_node = Tale;
      while (curr_node != nullptr)
      {
         cout << curr_node->data << "\t";
         curr_node = curr_node->prev_ptr;
      }
   }
   cout << endl;
}

template<typename T>
void List<T>::pop_front()
{
   if (Head == nullptr)
   {
      print_is_empty();
      return;
   }

   Node* for_del = Head;
   if (Head->next_ptr != nullptr)
   {
      Head = Head->next_ptr;
      Head->prev_ptr = nullptr;
   }
   else
   {
      Tale = nullptr;
      Head = nullptr;
   }
   delete for_del;
   Size--;
}

template<typename T>
void List<T>::pop_back()
{
   if (Tale == nullptr)
   {
      print_is_empty();
      return;
   }

   Node* for_del = Tale;
   if (Tale->prev_ptr != nullptr)
   {
      Tale = Tale->prev_ptr;
      Tale->next_ptr = nullptr;
   }
   else
   {
      Tale = nullptr;
      Head = nullptr;
   }
   delete for_del;
   Size--;
}

template<typename T>
void List<T>::print_is_empty()
{
   cout << "List is empty" << endl;
}


int main()
{
   List<int> Lst;
   Lst.push_front(20);
   Lst.push_front(12);
   Lst.push_front(33);
   Lst.push_back(40);
   Lst.push_back(51);
   Lst.print_forward();
   //Lst.print_backward();
   cout << "+++++" << endl;
   Lst.pop_front();
   Lst.pop_back();
   Lst.print_forward();
}
