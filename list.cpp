#ifndef LIST
#define LIST

#include <iostream>
#include <stdexcept> // For out_of_range exception
using namespace std;

template <typename T>
class List
{
    T *arr;
    int index;
    int size;

public:
    List(int size = 10);        // Constructor
    List(const List<T> &other); // Copy Constructor
    bool push_back(T elem);     // Push element to the end
    bool push_front(T elem);    // Push element to the start
    void pop_last();            // Remove the last element
    bool pop_start();           // Remove the first element
    bool removeAt(int i);
    T get(int i) const; // Get the element at index i
    int length() const; // Get the current length of the list
    void print();       // Print the list
    void clear();
    T &operator[](int i) const; // Access element by index
    ~List();                    // Destructor

private:
    void moveValuesToRight(); // Move values to the right (for push_front)
    void moveValuesToLeft();  // Move values to the left (for pop_start)
};

// Constructor definition
template <typename T>
List<T>::List(int size) : size(size), index(-1)
{
    arr = new T[size];
}

// Copy constructor definition
template <typename T>
List<T>::List(const List<T> &other) : size(other.size), index(other.index)
{
    arr = new T[size];
    for (int i = 0; i <= index; ++i)
    {
        arr[i] = other.arr[i]; // Deep copy elements
    }
}

// push_back definition
template <typename T>
bool List<T>::push_back(T elem)
{
    if (index == size - 1)
    {
        cout << "List is full" << endl;
        return false;
    }
    arr[++index] = elem;
    return true;
}

// push_front definition
template <typename T>
bool List<T>::push_front(T elem)
{
    if (index == size - 1)
    {
        cout << "List is full" << endl;
        return false;
    }
    moveValuesToRight();
    arr[0] = elem;
    index++;
    return true;
}

// pop_last definition
template <typename T>
void List<T>::pop_last()
{
    if (index == -1)
    {
        cout << "List is empty." << endl;
        return;
    }
    index--; // Decrease index to remove the last element
}

// pop_start definition
template <typename T>
bool List<T>::pop_start()
{
    if (index == -1)
    {
        cout << "List is empty." << endl;
        return false;
    }
    moveValuesToLeft();
    index--;
    return true;
}

// removeAt definition
template <typename T>
bool List<T>::removeAt(int i)
{
    if (i < 0 || i > index)
    {
        cout << "Index out of bounds" << endl;
        return false;
    }

    // Shift elements to the left, starting from the index to remove
    for (int j = i; j < index; j++)
    {
        arr[j] = arr[j + 1];
    }

    index--; // Decrease the index to reflect the removed element
    return true;
}

// get definition
template <typename T>
T List<T>::get(int i) const
{
    if (i < 0 || i > index)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[i];
}

// length definition
template <typename T>
int List<T>::length() const
{
    return index + 1;
}

// print definition
template <typename T>
void List<T>::print()
{
    for (int i = 0; i <= index; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

// clear definition
template <typename T>
void List<T>::clear()
{
    index = -1; // Reset index to -1, effectively clearing the list
}

// operator[] definition
template <typename T>
T &List<T>::operator[](int i) const
{
    if (i < 0 || i > index)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[i];
}

// Destructor definition
template <typename T>
List<T>::~List()
{
    delete[] arr;
}

// moveValuesToRight definition
template <typename T>
void List<T>::moveValuesToRight()
{
    for (int i = index; i >= 0; i--)
    {
        arr[i + 1] = arr[i];
    }
}

// moveValuesToLeft definition
template <typename T>
void List<T>::moveValuesToLeft()
{
    for (int i = 0; i < index; i++)
    {
        arr[i] = arr[i + 1];
    }
}

#endif