#include <iostream>
#include <memory>
#include <typeinfo>

class A {
public:
	
	static void * operator new(std::size_t size) {
		std::cout << "operator new!" << std::endl;
		return ::operator new(size);
	}

	static void operator delete(void *p, std::size_t size) {
		std::cout << "operator delete!" << std::endl;
		return ::operator delete(p);
	}
};

template <class T, class oneMoreT, class TT>
class myAllocator {

public:
	typedef T value_type;
    
    myAllocator() {}
    
    template<class Tp, class oneMoreTp, class TT_2> 
    myAllocator(const myAllocator<Tp, oneMoreTp, TT_2>& other) {}

    T* allocate (std::size_t n) {
    	//std::cout << typeid(T).name() << std::endl;
        std::cout << typeid(TT).name() << std::endl;        
        return reinterpret_cast<T*>(oneMoreT::operator new(n * sizeof(T)));
    
    }
    
    void deallocate (T* p, std::size_t n) {
        oneMoreT::operator delete(p, n * sizeof(T));
    }
};


int main() {
	myAllocator<A, A, A> allocator;
	auto my = std::allocate_shared<A>(allocator);
}