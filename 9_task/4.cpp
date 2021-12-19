#include <iostream>
#include <map>

int main (int argc, char* argv[]) {
    std::map<int, int> myMap;
    size_t size = 0;
    for (size_t i = 0; i < 1000; i++) {
        if (i == 200) {
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
        myMap.insert({200, 200});
        if (std::size(myMap) == size) {
            std::cout << "Bad insert new" << std::endl;
        }
        myMap.erase(200);
    }
    return 0;
}