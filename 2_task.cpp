#include <array>

#include <iostream>


template < std::size_t N >
    constexpr std::array < std::array < int, N - 1 > , N - 1 >
    minor(const std::array < std::array < int, N > , N > & a, int k) 
    {
        std::array < std::array < int, N - 1 > , N - 1 > newMinor {};
        for (std::size_t i = 0; i < N - 1; i++) {
            for (std::size_t j = 0; j < N - 1; j++) {
                ( & std::get < 0 > ((( & std::get < 0 > (newMinor))[i])))[j] = a[i + 1][j + (j >= k ? 1 : 0)];
            }
        }
        return newMinor;
    }

template < std::size_t N >
    constexpr int det(const std::array < std::array < int, N > , N > & a) 
    {
        int det_ = 0;
        for (std::size_t k = 0; k < N; k++) {
            det_ += (k % 2 ? (-1) : 1) * ( & std::get < 0 > ((( & std::get < 0 > (a))[0])))[k] * det < N - 1 > (minor(a, k));
        }
        return det_;
    }

template < >
    constexpr int det < 1 > (const std::array < std::array < int, 1 > , 1 > & a) 
    {
        return ( & std::get < 0 > ((( & std::get < 0 > (a))[0])))[0];
    }

int main() {
    const std::array < std::array < int, 3 > , 3 > A_1 = {
        {{0, 1, 2}, 
         {1,2,3}, 
         {2,3,7}}
    };
    constexpr int res_1 = det < 3 > (A_1);
    std::cout << res_1 << std::endl;

    const std::array < std::array < int, 5 > , 5 > A_2 = {
        {{1, 2, 3, 4, 5},
         {2, 3, 4, 5, 6}, 
         {3, 4, 5, 6, 7},
         {4, 5, 6, 7, 8},
         {5, 6, 7, 8, 9}}
    };
    constexpr int res_2 = det < 5 > (A_2);
    std::cout << res_2 << std::endl;

    const std::array < std::array < int, 2 > , 2 > A_3 = {
        {{-5, 15}, 
         {-9, 20}}
    };
    constexpr int res_3 = det < 2 > (A_3);
    std::cout << res_3 << std::endl;
}