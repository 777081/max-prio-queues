#pragma once

#include "dynamic_array.hpp"

template<typename E>
class HeapPriorityQueue {
    private:
        DynamicArray<PQNode<E>> heap;
        int parent(int index) { return (index - 1) / 2; }
        int leftChild(int index) { return (2 * index) + 1; }
        int rightChild(int index) { return (2 * index) + 2; }
        void shift_up(int index);
        void shift_down(int index);


    public:
        HeapPriorityQueue() = default;
        HeapPriorityQueue(const HeapPriorityQueue& other);

        void insert(const E &e, unsigned int p);
        PQNode<E> extract_max();
        const PQNode<E> &find_max() const;
        void modify_key(const E &e, unsigned int new_priority);
        size_t return_size() const { return heap.getSize(); }
        bool empty() const { return heap.getSize() == 0; }
    };

template <typename E>
HeapPriorityQueue<E>::HeapPriorityQueue(const HeapPriorityQueue<E>& other)
    : heap(other.heap){}

template <typename E> void HeapPriorityQueue<E>::shift_up(int index){
    while(index > 0 && heap.get(parent(index)).priority < heap.get(index).priority){
        heap.swap(parent(index), index);
        index = parent(index);
    }
}

template <typename E> void HeapPriorityQueue<E>::shift_down(int index){
    int max_index = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < static_cast<int>(heap.getSize()) && heap.get(left).priority > heap.get(max_index).priority) {
        max_index = left;
    }
    
    if (right < static_cast<int>(heap.getSize()) && heap.get(right).priority > heap.get(max_index).priority) {
        max_index = right;
    }

    if (index != max_index) {
        heap.swap(index, max_index);
        shift_down(max_index);
    }
}

template <typename E> void HeapPriorityQueue<E>::insert(const E &e, unsigned int p){
    PQNode<E> newNode{e, static_cast<int>(p)};
    heap.add_back(newNode);
    shift_up(static_cast<int>(heap.getSize()) - 1);
}

template <typename E> PQNode<E> HeapPriorityQueue<E>::extract_max(){
    PQNode<E> result = heap.get(0);
    heap.swap(0, static_cast<int>(heap.getSize()) - 1);
    heap.remove_back();
    if (!empty()) {
        shift_down(0);
    }
    return result;
}

template <typename E> const PQNode<E> &HeapPriorityQueue<E>::find_max() const {
    return heap.get(0);
}

template <typename E> void HeapPriorityQueue<E>::modify_key(const E &e, unsigned int new_priority){
    int index = 0;
    while (index < static_cast<int>(heap.getSize()) && e != heap.get(index).value) {
        ++index;
    }
    if (index < static_cast<int>(heap.getSize())) {
        E value = heap.get(index).value;
        heap.remove(index);
        insert(value, new_priority);
    }
}