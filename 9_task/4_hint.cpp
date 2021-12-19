#include <map>
#include <iostream>


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

    auto hintIt = myMap.find(201); 
    // вычисляется один раз, чтобы не влиять на время выполнения
    // кажется, что не должен меняться от итерации к итерации, 
    // т.к. в цикле один и тот же элемент добавляется и удаляется
    for (size_t i = 0; i < 500000; i++) {
        myMap.insert(hintIt, {200, 200});
        if (std::size(myMap) == size) {
            std::cout << "Bad insert new" << std::endl;
        }
        myMap.erase(200);
    }
    return 0;
}