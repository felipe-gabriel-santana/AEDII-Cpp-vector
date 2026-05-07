#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

template <typename T>
void run_and_print_csv(int n, string filename, string type_name) {
    vector<T> v;

    /*
    ------ Para geração aleatória de elementos -------

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(33, 126); 
    */
   
    vector<T> buffer;
    
    ifstream file(filename);
    if (!file.is_open()) return;
    T temp;
    while(buffer.size() < (size_t)n && file >> temp) buffer.push_back(temp);
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

    //ordena
    auto t4 = high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto t5 = high_resolution_clock::now();

    //remove
    auto t6 = high_resolution_clock::now();
    if(!v.empty()) v.erase(v.begin() + (v.size() / 2));
    auto t7 = high_resolution_clock::now();

    double ins = duration_cast<nanoseconds>(t1 - t0).count() / 1e6;
    double sea = duration_cast<nanoseconds>(t3 - t2).count() / 1e6;
    double sor = duration_cast<nanoseconds>(t5 - t4).count() / 1e6;
    double rem = duration_cast<nanoseconds>(t7 - t6).count() / 1e6;
    size_t mem = ((v.capacity() * sizeof(T)) + sizeof(v)) / 1024;

    cout << "CPP," << type_name << "," << n << "," 
         << fixed << setprecision(6) << ins << "," 
         << sea << "," << sor << "," << rem << "," << mem << endl;
}

int main() {
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    string fInt[] = {"int_100.txt", "int_1000.txt", "int_10000.txt", "int_100000.txt", "int_1000000.txt"};
    string fChar[] = {"char_100.txt", "char_1000.txt", "char_10000.txt", "char_100000.txt", "char_1000000.txt"};

    for (int i = 0; i < 5; i++) {
        run_and_print_csv<int>(sizes[i], fInt[i], "INT");
        run_and_print_csv<char>(sizes[i], fChar[i], "CHAR");
    }
}
