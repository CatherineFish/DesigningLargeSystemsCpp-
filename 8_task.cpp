#include <typeinfo>
#include <string>
#include <stdexcept>
#include <iostream>

class Any {
public:
    template <typename T>
    Any(const T& val) : curHolder_(new myHolder<T>(val)){}
    
    template<typename U>
    U get() const
    {
        if(typeid(U) != curHolder_->type_info()){
            throw std::runtime_error("Bad any cast");
        }
        return static_cast<myHolder<U>*>(curHolder_)->val_;
    }

private:
    struct baseHolder {
    public:
        virtual ~baseHolder() {}
        virtual const std::type_info& type_info() const = 0;
    };
    
    template <typename T> 
    struct myHolder : baseHolder
    {
        
    public:
        T val_;
    
        myHolder(const T& val) : val_(val){}
        
        const std::type_info& type_info() const
        {
            return typeid(val_);
        }
    };

private:
    baseHolder* curHolder_;
};

int main(){
    Any a(5);
    a.get<int>(); // 5
    std::cout << a.get<int>() << std::endl;
    a.get<std::string>(); // error
}
