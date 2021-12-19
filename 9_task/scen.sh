#!/bin/bash

g++ -std=c++17 -o 1 1.cpp 
g++ -std=c++17 -o 1_hint 1_hint.cpp 
g++ -std=c++17 -o 2 2.cpp 
g++ -std=c++17 -o 2_hint 2_hint.cpp 
g++ -std=c++17 -o 3 3.cpp 
g++ -std=c++17 -o 3_hint 3_hint.cpp 
g++ -std=c++17 -o 4 4.cpp 
g++ -std=c++17 -o 4_hint 4_hint.cpp 

echo "Вставка в конец map:"
echo "-------------------"
echo "Без hint'а"
time ./1
echo "С hint'ом"
time ./1_hint
echo "==================="

echo "Вставка в начало map:"
echo "-------------------"
echo "Без hint'а"
time ./2
echo "С hint'ом"
time ./2_hint
echo "==================="

echo "Вставка в map (во вторую половину) с предварительным поиском следующего элемента (для hint'а):"
echo "-------------------"
echo "Без hint'а"
time ./3
echo "С hint'ом"
time ./3_hint
echo "==================="

echo "Вставка в map (в первую половину) с предварительным поиском следующего элемента (для hint'а):"
echo "-------------------"
echo "Без hint'а"
time ./4
echo "С hint'ом"
time ./4_hint
echo "==================="

rm 1 2 3 4 1_hint 2_hint 3_hint 4_hint 