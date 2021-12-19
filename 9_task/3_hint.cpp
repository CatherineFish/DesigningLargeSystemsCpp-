#include <map>
#include <iostream>


int main (int argc, char* argv[]) {
    std::map<int, int> myMap;
    size_t size = 0;
    for (size_t i = 0; i < 1000; i++) {
        if (i == 800) {
            continue;
        } 
        myMap.insert({i, i});
        if (std::size(myMap) == size) {
            std::cout << "Bad insert" << std::endl;
        }
        size++;
    }
    
    for (size_t i = 0; i < 500000; i++) {
        auto it = myMap.find(801);
        myMap.insert(it, {800, 800});
        if (std::size(myMap) == size) {
            std::cout << "Bad insert new" << std::endl;
        }
        myMap.erase(800);
    }
    return 0;
}