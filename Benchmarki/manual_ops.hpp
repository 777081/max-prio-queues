using namespace std;

template <typename T, typename DT> void manual_add_front(T& structure){
    // Interaktywne dodawanie elementu na poczatek struktury
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    structure.add_front(elem);
}
template <typename T, typename DT> void manual_add_back(T& structure){
    // Interaktywne dodawanie elementu na koniec struktury
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    structure.add_back(elem);
}

template <typename T, typename DT> void manual_insert(T& structure){
    // Interaktywne wstawianie elementu na wybrana pozycje
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    cout << "Podaj indeks: \n> ";
    cin >> index;
    structure.insert(elem, index);
}


template <typename T> void manual_remove_front(T& structure){
    // Usuwanie pierwszego elementu ze struktury
    structure.remove_front();
}

template <typename T> void manual_remove_back(T& structure){
    // Usuwanie ostatniego elementu ze struktury
    structure.remove_back();
}

template <typename T> void manual_remove(T& structure){
    // Interaktywne usuwanie elementu z wybranej pozycji
    size_t index;
    cout << "Podaj indeks: \n> ";
    cin >> index;
    structure.remove(index);
}

template <typename T, typename DT> void manual_search(T& structure){
    // Interaktywne wyszukiwanie elementu w strukturze
    DT elem;
    cout << "Podaj element do wyszukania: \n> ";
    cin >> elem;
    cout << "Znaleziono " << elem << " na indeksie " << structure.search(elem, true) << " (-1 dla braku elementu)" << endl;
}

template <typename T, typename DT> void manual_search(T& structure, bool backwards){
    // Interaktywne wyszukiwanie z mozliwoscia wyboru kierunku
    DT elem;
    cout << "Podaj element do wyszukania: \n> ";
    cin >> elem;
    cout << "Znaleziono " << elem << " na indeksie " << structure.search(elem, backwards) << " (-1 dla braku elementu)" << endl;
}

template <typename T> void manual_print(T& structure){
    // Wyswietlanie zawartosci struktury
    structure.print();
}