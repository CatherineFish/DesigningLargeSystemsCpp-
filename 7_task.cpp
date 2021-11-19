#include<iostream>

class TRandomNumberGenerator {
public:
    virtual ~TRandomNumberGenerator();
    virtual double Generate() const = 0;
};

class TPoissonGenerator : TRandomNumberGenerator {
public:
    virtual ~TPoissonGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TPoissonGenerator " << std::endl; 
        return 0; 
    }
};

class TBernoulliGenerator : TRandomNumberGenerator{
public:
    virtual ~TBernoulliGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TBernoulliGenerator " << std::endl;
        return 0;  
    }
};

class TGeometricGenerator : TRandomNumberGenerator{
public:
    virtual ~TGeometricGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TGeometricGenerator " << std::endl; 
        return 0; 
    }
};

class TFiniteGenerator : TRandomNumberGenerator{
public:
    virtual ~TFiniteGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TFiniteGenerator " << std::endl;
        return 0;  
    }
};
