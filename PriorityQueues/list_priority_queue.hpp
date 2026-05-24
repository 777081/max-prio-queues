#pragma once
#include "doubly_linked_list.hpp"
#include <functional>
#include <stdexcept>

/*
    Priority queue implementation based on doubly linked list interface
*/

template<typename E>
struct PQNode
{ 
    E value; 
    int priority;
};

template <typename E>
class ListPriorityQueue
{
public:
    ListPriorityQueue() = default;
    ListPriorityQueue(const ListPriorityQueue& other) : list(other.list), size(other.size) {}
    
    void insert(const E &e, unsigned int p);
    PQNode<E> extract_max();
    const PQNode<E> &find_max() const;
    void modify_key(const E &e, unsigned int new_priority);
    size_t return_size() const;
    bool empty() const;

private:
    DLinkedList<PQNode<E>> list;
    size_t size=0;
};

// FIFO approach
template <typename E>
void ListPriorityQueue<E>::insert(const E &e, unsigned int p)
{
    PQNode<E> newNode{e, static_cast<int>(p)};

    if (empty()) 
    {
        list.add_front(newNode);
        size++;
        return;
    }
        
    int i = 0;
    while (i < size && list.get(i).priority >= static_cast<int>(p)) 
    {
        i++;
    }

    if (i == 0) {
        list.add_front(newNode);
    } else if (i == size) {
        list.add_back(newNode);
    } else {
        list.insert(newNode, i);
    }
    
    size++;
}

template <typename E> 
PQNode<E> ListPriorityQueue<E>::extract_max()
{
    if (empty()) throw std::runtime_error("Queue is empty");

    PQNode<E> max_element = list.front();
    list.remove_front();
    size--;

    return max_element;
}

template <typename E>
const PQNode<E> &ListPriorityQueue<E>::find_max() const
{
    if (empty()) throw std::runtime_error("Queue is empty");
    return list.front();
}

// modifies the first matching element
template <typename E>
void ListPriorityQueue<E>::modify_key(const E &e, unsigned int p)
{
    if (empty()) throw std::runtime_error("Queue is empty");

    bool found = false;
    size_t original_size = size;

    for (size_t i = 0; i < original_size; )
        {
            if (list.get(i).value == e)
            {
                list.remove(i);
                --size;
                insert(e, p);
                found = true;
                --original_size;
            }
            else
            {
                ++i;
            }
        }

}

template <typename E>
size_t ListPriorityQueue<E>::return_size() const
{
    return size;
}                                 

template <typename E>
bool ListPriorityQueue<E>::empty() const
{
    return size == 0;
}

