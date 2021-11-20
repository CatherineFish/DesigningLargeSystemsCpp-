#include <iostream>
#include <numeric>
#include <algorithm>

class TOptions {
public:
    virtual ~TOptions();
    virtual bool IsValid() const = 0;
};

class TPoissonOptions : public TOptions {
    double lambda;
public:
    TPoissonOptions(double lambda_): lambda(lambda_) {}
    bool IsValid() const override {
        return lambda > 0.0;
    }
};

class TBernoulliOptions : public TOptions {
    double p;
public:
    TBernoulliOptions(double p_): p(p_) {}
    bool IsValid() const override {
        return p >= 0.0 && p <= 1.0;
    }
};

class TGeometricOptions : public TOptions {
    double p;
public:
    TGeometricOptions(double p_): p(p_) {}
    bool IsValid() const override {
        return p >= 0.0 && p <= 1.0;
    }
};

class TFiniteOptions : public TOptions {
    std::vector<double> x;
    std::vector<double> p;
public:
    TFiniteOptions(std::vector<double> x_, std::vector<double> p_): x(x_), p(p_) {}
    
    bool IsValid() const override {
        if (x.size() != p.size()) {
            return false;
        }
        double sum = std::accumulate(p.begin(), p.end(), 0.0);
        return std::all_of (p.begin(), p.end(), [](double i) {return i >= 0.0 && i <= 1.0;}) && (sum == 1);
    }
};

class TRandomNumberGenerator {
public:
    //virtual ~TRandomNumberGenerator();
    virtual double Generate() const = 0;
};

class TPoissonGenerator : public TRandomNumberGenerator {
public:
    using TOpt = TPoissonOptions;
    //virtual ~TPoissonGenerator() override = default;
     
    virtual double Generate() const override{
        std::cout << "TPoissonGenerator " << std::endl; 
        return 0; 
    }
private:
    std::unique_ptr<TOpt> lambda;
};

class TBernoulliGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TBernoulliOptions;
    
    //virtual ~TBernoulliGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TBernoulliGenerator " << std::endl;
        return 0;  
    }
private:
    std::unique_ptr<TOpt> p;
};

class TGeometricGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TGeometricOptions;

    //virtual ~TGeometricGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TGeometricGenerator " << std::endl; 
        return 0; 
    }
private:
    std::unique_ptr<TOpt> p;
};

class TFiniteGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TFiniteOptions;

    //virtual ~TFiniteGenerator() override = default;
    virtual double Generate() const override{
        std::cout << "TFiniteGenerator " << std::endl;
        return 0;  
    }
private:
    std::unique_ptr<TOpt> vectors;

};
