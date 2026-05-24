#pragma once
#include <algorithm>
#include <iostream>


template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(size_t cap);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    T *getCollection() { return collection; }
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    
    void upsize_();
    bool needsToUpsize() const { return this->size + 1 >= this->capacity; }

    const T &get(int index) const;

    void insert(T val, size_t position);
    void add_back(T val);
    void add_front(T val);

    void remove(size_t position);
    void remove_back();
    void remove_front();
    void swap(size_t pos1, size_t pos2);

    int search(T e, bool compatibility_flag);

    void print();
private:
    T *collection;   // tablica
    size_t capacity; // rozmiar tablicy
    size_t size;     // ilość elementów w tablicy
};

template <typename T>
DynamicArray<T>::DynamicArray() : capacity(4), size(0)
{
    collection = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t cap) : capacity(cap), size(0)
{
    collection = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : capacity(other.capacity), size(other.size)
{
    collection = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        collection[i] = other.collection[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] collection;
}

template <typename T>
void DynamicArray<T>::upsize_()
{
    // Powiększanie pojemnosci tablicy o jego dwa razy
    size_t new_capacity = capacity * 2;
    T *new_collection = new T[new_capacity];
    std::move(collection, collection + size, new_collection);
    delete[] collection;
    collection = new_collection;
    capacity = new_capacity;
}

template <typename T>
const T &DynamicArray<T>::get(int index) const
{
    // Zwracanie elementu na podanym indeksie
    return collection[index];
}

template <typename T>
void DynamicArray<T>::insert(T val, size_t position)
{
    // Wstawianie elementu na pozycje oraz przesuniecie pozostalych
    if (needsToUpsize())
    {
        upsize_();
    }
    std::move(collection + position, collection + size, collection + position + 1);
    collection[position] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::add_front(T val)
{
    // Dodawanie elementu na poczatek tablicy
    if (needsToUpsize())
    {
        upsize_();
    }
    std::move(collection, collection + size, collection + 1);
    collection[0] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::add_back(T val)
{
    // Dodawanie elementu na koniec tablicy
    if (needsToUpsize())
    {
        upsize_();
    }
    collection[size] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::remove(size_t position)
{
    // Usuwanie elementu i przesuniecie pozostalych w lewo
    std::move(collection + position + 1, collection + size, collection + position);
    size--;
}

template <typename T>
void DynamicArray<T>::remove_back()
{
    // Usuwanie ostatniego elementu
    size--;
}

template <typename T>
void DynamicArray<T>::remove_front()
{
    // Usuwanie pierwszego elementu i przesuniecie pozostalych w lewo
    std::move(collection + 1, collection + size, collection);
    size--;
}

template <typename T>
void DynamicArray<T>::swap(size_t pos1, size_t pos2)
{
    // Zamiana dwoch elementow tablicy
    if (pos1 >= size || pos2 >= size) {
        throw std::out_of_range("swap out of range");
    }
    T temp = collection[pos1];
    collection[pos1] = collection[pos2];
    collection[pos2] = temp;
}

template <typename T>
int DynamicArray<T>::search(T e, bool compatibility_flag)
//comatibility_flag jest nieuzywany, ale pozostawiony dla kompatybilnosci z DLinkedList
{
    // Przeszukiwanie tablicy w poszukiwaniu elementu
    for (size_t i = 0; i < size; i++)
    {
        if (collection[i] == e)
            return i;
    }
    return -1;
}

template <typename T>
void DynamicArray<T>::print(){
    std::cout << "[";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << collection[i];
        if(i != size-1){
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}