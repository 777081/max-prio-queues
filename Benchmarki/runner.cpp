#include <iostream>
#include <exception>
#include "../PriorityQueues/list_priority_queue.hpp"
#include "../PriorityQueues/heap_priority_queue.hpp"
#include "manual_ops.hpp"
#include "benchmarks.hpp"

using namespace std;


int main(){
    // Glowne menu wyboru struktury danych do testowania
    int choice = -1;
    while(choice != 0){
        cout << "Wybierz strukture:" << endl 
        << "1. List priority queue" << endl
        << "2. Heap priority queue" << endl
        << "0. Wyjdz" << endl
        << ">";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Starting benchmark for ListPriorityQueue<int>..." << endl;
            try {
                run_test_suite<ListPriorityQueue<int>>(4, 100, 100, 100, 100, 100);
                cout << "Benchmark completed successfully." << endl;
            } catch (const exception& e) {
                cerr << "Benchmark failed: " << e.what() << endl;
            } catch (...) {
                cerr << "Benchmark failed with unknown error." << endl;
            }
            break;
        case 2:
            cout << "Starting benchmark for HeapPriorityQueue<int>..." << endl;
            try {
                run_test_suite<HeapPriorityQueue<int>>(4, 50, 100, 100, 100, 10);
                cout << "Benchmark completed successfully." << endl;
            } catch (const exception& e) {
                cerr << "Benchmark failed: " << e.what() << endl;
            } catch (...) {
                cerr << "Benchmark failed with unknown error." << endl;
            }
            break;
        }
    }
}