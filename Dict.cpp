#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include "LinkedList.hpp"
#define N 10000

size_t hash(std::string str);

template<class K, class V>
class Dict {
public:
    using Pair = std::pair<K, V>;

    void clear() {
        for (size_t i = 0; i < n_buckets; ++i) {
            bucketstab[i].clear();
        }
    }

    bool insert(const Pair& p) {
        size_t h = hash(p.first);
        size_t b = h % n_buckets;
        for(auto& pair: bucketstab[b]){
            if(pair.first==p.first){
                if(pair==p) return false;
                else{
                    bucketstab[b].remove(pair);
                    bucketstab[b].push_back(p);
                    return true;
                }
            }
        } 
        bucketstab[b].push_back(p);
        return true;
        
    }

    bool find(const K& k) {
        size_t h = hash(k);
        size_t index = h % n_buckets;
        for(auto& p: bucketstab[index]){
            if(p.first==k) return true;
        } 
        return false;
    }

    V& operator[](const K& k) {
       size_t h = hash(k);
       size_t index=h%n_buckets;
       for(auto& pair: bucketstab[index]){
            if(pair.first==k) return pair.second;
        } 
        temp.first = k; 
        insert(temp); 
        return temp.second;
        
    }

    bool erase(const K& k) {
        size_t h = hash(k);
        size_t index = h % n_buckets;
        for(auto& p: bucketstab[index]){
            if(p.first==k){
                bucketstab[index].remove(p);
                return true;
            }
        } 
        return false;  
    }

    int size() {
        int num_elem = 0;
        for (size_t i = 0; i < n_buckets; i++) {
            num_elem += bucketstab[i].size();
        }
        return num_elem;
    }

    bool empty() {
        for (size_t i = 0; i < n_buckets; i++) {
            if (!bucketstab[i].empty()) {
                return false;
            }
        }
        return true;
    }

    void buckets() {
        int shortestList = std::numeric_limits<int>::max();
        int longestList = 0;

        for (size_t i = 0; i < n_buckets; ++i) {
            int currentSize = bucketstab[i].size();
            shortestList = std::min(shortestList, currentSize);
            longestList = std::max(longestList, currentSize);
        }

        std::cout << "# " << size() << " " << n_buckets << " " << shortestList << " " << longestList << std::endl;
    }

private:
    static const size_t n_buckets = N;
    List<Pair> bucketstab[n_buckets];
    Pair temp;
};

size_t hash(std::string str) {
    size_t h = 0;
    for (size_t i = 0; i < str.length(); i++) {
        h = (h << 5) + str[i];
    }
    return h;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <nazwa_pliku>" << std::endl;
        return 1;
    }

    // Utwórz słownik
    Dict<std::string, std::string> slownik;

    // Wczytaj pary słów z pliku
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << argv[1] << std::endl;
        return 1;
    }

    std::string key, value;
    while (file >> key >> value) {
        slownik.insert(std::make_pair(key, value));
    }

    file.close();
    

    // Wczytaj słowa
    std::string input;
    while (std::cin >> input) {
        if (slownik.find(input)) {
            std::cout << slownik[input]<<std::endl;
        } else {
            std::cout << "-" << std::endl;
        }
    }

    return 0;
}