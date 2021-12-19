#include <iostream>
#include <map>

int main (int argc, char* argv[]) {
    std::map<int, int> myMap;
    size_t size = 0;
    for (size_t i = 0; i < 500000; i++) {
        myMap.insert({i, i});
        if (std::size(myMap) == size) {
            std::cout << "Bad insert" << std::endl;
        }
        size++;
    }
    return 0;
}