#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

struct Tempos {
    double insere, busca, ordena, remove;
    size_t memoria;
};

template <typename T>
Tempos run_bench(int n, string filename) {
    vector<T> v;
    
    /*
    ------ Para geração aleatória de elementos -------

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(33, 126); 
    */

    vector<T> buffer;
    ifstream file(filename);
    if (!file.is_open()) return {0,0,0,0,0};

    T temp;
    for(int i=0; i<n && file >> temp; ++i) buffer.push_back(temp);
    file.close();

    //insere
    auto t0 = high_resolution_clock::now();
    for (const auto& item : buffer) v.push_back(item);
    auto t1 = high_resolution_clock::now();

    //busca
    T target = v[v.size() / 2];
    auto t2 = high_resolution_clock::now();
    auto it = find(v.begin(), v.end(), target);
    auto t3 = high_resolution_clock::now();

    //remove
    auto t6 = high_resolution_clock::now();
    if(!v.empty()) v.erase(v.begin() + (v.size() / 2));
    auto t7 = high_resolution_clock::now();

    //ordena
    auto t4 = high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto t5 = high_resolution_clock::now();


    size_t mem_kb = ((v.capacity() * sizeof(T)) + sizeof(v)) / 1024;

    return {
        duration_cast<nanoseconds>(t1 - t0).count() / 1e6,
        duration_cast<nanoseconds>(t3 - t2).count() / 1e6,
        duration_cast<nanoseconds>(t5 - t4).count() / 1e6,
        duration_cast<nanoseconds>(t7 - t6).count() / 1e6,
        mem_kb
    };
}

int main() {

    string filesInt[] = {"int_100.txt", "int_1000.txt", "int_10000.txt", "int_100000.txt", "int_1000000.txt"};
    string filesChar[] = {"char_100.txt", "char_1000.txt", "char_10000.txt", "char_100000.txt", "char_1000000.txt"};
    int sizes[] = {100, 1000, 10000, 100000, 1000000};

    cout << fixed << setprecision(4);
    cout << left << setw(10) << "Tipo" << setw(10) << "Tamanho" 
         << "| Inserir(ms) | Buscar(ms) | Remover(ms) | Ordenar(ms) | Memoria(KB)" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < 5; i++) {
        Tempos r_int = run_bench<int>(sizes[i], filesInt[i]);
        cout << left << setw(10) << "INT" << setw(10) << sizes[i] << "| "
             << setw(11) << r_int.insere << " | " << setw(10) << r_int.busca << " | "
             << setw(11) << r_int.remove << " | " << setw(11) << r_int.ordena << " | "
             << r_int.memoria << " KB" << endl;

        Tempos r_char = run_bench<char>(sizes[i], filesChar[i]);
        cout << left << setw(10) << "CHAR" << setw(10) << sizes[i] << "| "
             << setw(11) << r_char.insere << " | " << setw(10) << r_char.busca << " | "
             << setw(11) << r_char.remove << " | " << setw(11) << r_char.ordena << " | "
             << r_char.memoria << " KB" << endl;
        cout << string(85, '.') << endl;
    }
    return 0;
}