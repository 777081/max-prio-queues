#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

template <typename T> struct testItem {
    T structure;
    int min_prio_elem;
};

// Rozmiary struktur do testowania wydajnosci
const int MEASUREMENT_POINTS[6] = {5000, 6000, 7000, 8000, 9000, 10000};
const int MAX_PRIO = 30000;
const int VAL_RANGE = 50000;


template <typename T> double test_insert(T structure, int reiterations, int value, unsigned int priority){
    auto reiter_copies = create_reiteration_copies<T>(structure, reiterations);
    vector<int> prios;
    if(priority == -1){
        for(int i = 0; i < reiterations; i++){
            prios.push_back(structure.extract_max().priority+1);
        }
    }
    else if(priority == -2){
        random_device seed;
        mt19937 rng(seed());
        std::uniform_int_distribution<int> dist(0, 100000);
        for(int i = 0; i < reiterations; i++){
            prios.push_back(dist(rng));
        }
    }
    else{
        for(int i = 0; i < reiterations; i++){
            prios.push_back(priority);
        }
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < reiterations; i++) {
        reiter_copies.at(i).insert(value, prios.at(i));
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;   
}

template <typename T> double test_extract_max(T structure, int reiterations){
    auto reiter_copies = create_reiteration_copies<T>(structure, reiterations);
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < reiterations; i++) {
        reiter_copies.at(i).extract_max();
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;   
}

template <typename T> double test_peek(T structure, int reiterations){
    auto start = chrono::steady_clock::now();
    T new_structure = T(structure);
    for (int i = 0; i < reiterations; i++) {
        new_structure.find_max();
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;   
}

template <typename T> double test_modify(testItem<T> item, int reiterations, int scenario){
    auto reiter_copies = create_reiteration_copies<T>(item.structure, reiterations);
    vector<int> values;
    vector<int> prios;
    if(scenario == 0){
        //modyfikacja poczatku
        for(int i = 0; i < reiterations; i++){
            values.push_back(item.structure.find_max().value);
            prios.push_back(item.structure.find_max().priority+1);
        }
    }
    else if(scenario == 1){
        //modyfikacja konca
        for(int i = 0; i < reiterations; i++){
           values.push_back(item.min_prio_elem);
           prios.push_back(0);
        }
    }
    else if(scenario == 2){
        //losowy scenariusz
        random_device seed;
        mt19937 rng_val(seed());
        mt19937 rng_prio(((seed()+13)%7)*74);
        std::uniform_int_distribution<int> dist_val(-VAL_RANGE, VAL_RANGE);
        std::uniform_int_distribution<int> dist_prio(0, MAX_PRIO);
        for(int i = 0; i < reiterations; i++){
            values.push_back(dist_val(rng_val));
            prios.push_back(dist_prio(rng_prio));
        }
    }
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < reiterations; i++) {
        reiter_copies.at(i).modify_key(values[i], prios[i]);
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;   
}

template <typename T> double test_get_size(T structure, int reiterations){
    T new_structure = T(structure);
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < reiterations; i++) {
        new_structure.return_size();
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;   
}

template <typename T> vector<T> create_reiteration_copies(T structure, int reiterations){
    // Tworzenie wielu kopii struktury do wielokrotnych pomiarow
    vector<T> reiter_copies;
    for(int i = 0; i < reiterations; i++){
        reiter_copies.push_back(structure);
    }
    return reiter_copies;
}

template <typename T> testItem<T> populate_structure(int seed, int size){
    // Tworzenie struktury z losowymi danymi
    mt19937 rng_val(seed*2+15);
    mt19937 rng_prio((((seed*3+17)%3)+8)*7);
    uniform_int_distribution<int> dist_val(-VAL_RANGE, VAL_RANGE);
    uniform_int_distribution<unsigned int> dist_prio(0, MAX_PRIO);
    T structure;
    int min_prio = MAX_PRIO + 1;
    int min_prio_val;
    int prio;
    int val;
    testItem<T> testitem;
    for(int i = 0; i<size; i++){
        val = dist_val(rng_val);
        prio = dist_prio(rng_prio);
        if (i % 500 == 0 || i == size - 1) {
            cout << "    inserting item " << i << " / " << size << " (prio=" << prio << ")" << endl;
        }
        try {
            testitem.structure.insert(val, prio);
        } catch (const exception& e) {
            cerr << "    insert failed at i=" << i << " val=" << val << " prio=" << prio << " : " << e.what() << endl;
            throw;
        } catch (...) {
            cerr << "    insert failed with unknown error at i=" << i << " val=" << val << " prio=" << prio << endl;
            throw;
        }
        if(prio < min_prio){
            min_prio = prio;
            min_prio_val = val;
        }
    }
    cout << "    completed insertion of " << size << " items." << endl;
    testitem.min_prio_elem = min_prio_val;
    return testitem;
}

template <typename T> vector<testItem<T>> generate_test_structures(int batch){
    // Generowanie zestawu struktur o roznych rozmiarach do testowania
    vector<testItem<T>> structures;
    for(int i = 0; i<size(MEASUREMENT_POINTS); i++){
        cout << "  Generating structure for size " << MEASUREMENT_POINTS[i] << "..." << endl;
        structures.push_back(populate_structure<T>(batch, MEASUREMENT_POINTS[i]));
        cout << "    done size " << MEASUREMENT_POINTS[i] << "" << endl;
    }
    return structures;
}

template <typename T> void vector_to_file(vector<T> batch, fstream& file, bool newline=true){
    // Zapisywanie wynikow pomiarow do pliku CSV
    for(int i = 0; i < batch.size(); i++){
        file << batch.at(i);
        if(i != batch.size()-1){
            file << ",";
        }
    }
    if(newline){
        file << "\n";
    }
}

template <typename T> void run_test_suite(int seeds, int insert_reiterations, int extract_reiterations, int peek_reiterations, int size_reiterations, int modify_reiterations){
    cout << "Generating test structures for " << seeds << " seeds..." << endl;
    vector<vector<testItem<T>>> structures;
    for(int i = 0; i < seeds; i++){
        cout << "Seed " << i << ":" << endl;
        structures.push_back(generate_test_structures<T>(i));
        cout << "Seed " << i << " generation complete." << endl;
    }
    for(int i = 0; i<size(MEASUREMENT_POINTS); i++){
        cout << "Processing measurement size " << MEASUREMENT_POINTS[i] << "..." << endl;
        fstream size_file("size" + to_string(MEASUREMENT_POINTS[i]) + ".csv", ios::out);
        if (!size_file.is_open()) {
            cerr << "Failed to open output file for size " << MEASUREMENT_POINTS[i] << endl;
            continue;
        }
        cout << "Opened file size" << MEASUREMENT_POINTS[i] << ".csv" << endl;
        size_file << "seed, insert_max, insert_rand, insert_min, extract-max, peek, modify_max, modify_rand, modify_min, get-size\n";
        for(int j = 0; j < seeds; j++){
            cout << "  seed " << j << ": ";
            double insert_max = test_insert<T>(structures[j][i].structure, insert_reiterations, 4522, -1);
            double insert_rand = test_insert<T>(structures[j][i].structure, insert_reiterations, 43533, -2);
            double insert_min = test_insert<T>(structures[j][i].structure, insert_reiterations, 1234, 0);
            double extract_max = test_extract_max<T>(structures[j][i].structure, extract_reiterations);
            double peek = test_peek<T>(structures[j][i].structure, peek_reiterations);
            double modify_max = test_modify<T>(structures[j][i], modify_reiterations, 0);
            double modify_rand = test_modify<T>(structures[j][i], modify_reiterations, 2);
            double modify_min = test_modify<T>(structures[j][i], modify_reiterations, 1);
            double get_size = test_get_size<T>(structures[j][i].structure, size_reiterations);
            cout << "done" << endl;
            size_file << j << "," << insert_max << "," << insert_rand << "," << insert_min << "," << extract_max << "," << peek << "," << modify_max << "," << modify_rand << "," << modify_min << "," << get_size << "\n";
        }
        size_file.close();
        cout << "Finished size " << MEASUREMENT_POINTS[i] << "." << endl;
    }
}