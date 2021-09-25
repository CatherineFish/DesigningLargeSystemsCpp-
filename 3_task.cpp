/*
#include<iostream>
#include <vector>


int main()
{
	std::vector<bool> v {true, false};
	for (auto& x : v ) {
	}

	for (auto&& x : v ) {
	}
}

буквальный ответ компилятора:
cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’ {aka ‘std::_Bit_reference’}
    for (auto& x : v )
А вот for (auto&& x : v ) спокойно компилируется

Итераторы std::vector<T> разыменовываются к T&, который можно присвоить auto & .
std::vector <bool>, упаковывает свои значения вместе, и поэтому необходим Proxy для доступа к значениям. 
Возвращенный Proxy является prvalue (временным), он не может привязаться к ссылке lvalue, такой как auto &. 
В это же время auto && правильно свертывается в ссылку lvalue, если она задана, а также может быть свзяана с временным объектом, таким как Proxy.
*/



int main()
{
	std::vector<bool> v {true, false};
	for (auto& x : v ) {
	}

	for (auto&& x : v ) {
	}
}