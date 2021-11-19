#include <iostream>

class TRandomNumberGenerator {
public:
    //virtual ~TRandomNumberGenerator();
    virtual double Generate() const = 0;
};

class TPoissonGenerator : public TRandomNumberGenerator {
public:
    //virtual ~TPoissonGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TPoissonGenerator " << std::endl; 
        return 0; 
    }
};

class TBernoulliGenerator : public TRandomNumberGenerator{
public:
    //virtual ~TBernoulliGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TBernoulliGenerator " << std::endl;
        return 0;  
    }
};

class TGeometricGenerator : public TRandomNumberGenerator{
public:
    //virtual ~TGeometricGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TGeometricGenerator " << std::endl; 
        return 0; 
    }
};

class TFiniteGenerator : public TRandomNumberGenerator{
public:
    //virtual ~TFiniteGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TFiniteGenerator " << std::endl;
        return 0;  
    }
};
