#include<string>

#include<set>

#include<vector>

#include<utility>

#include<tuple>

#include<sstream>

#include<iterator>

#include<iostream>


struct Printer {
    std::stringstream mystr;
    std::string str() const {
        return mystr.str();
    } // возвращает строковое представление
    // далее перегруженные/шаблонные функции вида:

    template < typename T >
        Printer & format(T elem) {
            mystr << elem;
            return *this;
        }

    template < typename T >
        void noCodeCopy(T obj) {
            for (auto i = obj.begin(); i != obj.end(); i++) {
                format( * i);
                if (std::next(i) != obj.end()) {
                    mystr << ", ";
                } else {
                    mystr << " ";
                }
            }
        }

    template < typename T >
        Printer & format(std::set < T > s) {
            mystr << "{ ";
            noCodeCopy(s);
            mystr << "}";
            return *this;
        }

    template < typename T >
        Printer & format(std::vector < T > v) {
            mystr << "[ ";
            noCodeCopy(v);
            mystr << "]";
            return *this;
        }

    template < typename T_1, typename T_2 >
        Printer & format(std::pair < T_1, T_2 > p) {
            mystr << "( ";
            format(p.first);
            mystr << ", ";
            format(p.second);
            mystr << " )";
            return *this;
        }

    template < typename...Args >
        Printer & format(std::tuple < Args... > t) {
            // Getting size of tuple
            std::size_t length = sizeof...(Args);

            std::apply(

                // A lambda function
                [ = ](auto
                    const & ...ps) {
                    mystr << "( ";
                    int k = 0;

                    // Variadic expansion used.
                    ((format(ps),
                            mystr << (++k == length ? " " : ", ")),
                        ...);

                    mystr << ")";
                },
                t);
            return *this;
        }

};

template < typename T >
    std::string format(const T & t) {
        return Printer().format(t).str();
    }

int main() {
    std::tuple < std::string, int, int > t = {"xyz", 1, 2};
    std::vector < std::pair < int, int > > v = {{1, 4}, {5, 6}};
    std::string s1 = Printer().format(" vector: ").format(v).str();
    // " vector: [ ( 1, 4 ), ( 5, 6 ) ]"
    std::cout << s1 << std::endl;
    std::string s2 = Printer().format(t).format(" ! ").format(0).str();
    // "( xyz, 1, 2 ) ! 0"
    std::cout << s2 << std::endl;
}