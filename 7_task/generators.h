#include <iostream>
#include <numeric>
#include <algorithm>
#include <memory>
#include <random>

class TOptions {
public:
    //virtual ~TOptions();
    virtual bool IsValid() const = 0;
};

class TPoissonOptions : public TOptions {
    
public:
    double Lambda;
    TPoissonOptions(double lambda_): Lambda(lambda_) {}
    virtual bool IsValid() const override {
        return Lambda > 0.0;
    }
};

class TBernoulliOptions : public TOptions {
    
public:
    double P;
    TBernoulliOptions(double p_): P(p_) {}
    virtual bool IsValid() const override {
        return P >= 0.0 && P <= 1.0;
    }
};

class TGeometricOptions : public TOptions {
    
public:
    double P;
    TGeometricOptions(double p_): P(p_) {}
    virtual bool IsValid() const override {
        return P >= 0.0 && P <= 1.0;
    }
};

class TFiniteOptions : public TOptions {
    
public:
    std::vector<double> X;
    std::vector<double> P;
    TFiniteOptions(std::vector<double> x_, std::vector<double> p_): X(x_), P(p_) {}
    
    virtual bool IsValid() const override {
        if (X.size() != P.size()) {
            return false;
        }
        double sum = std::accumulate(P.begin(), P.end(), 0.0);
        
        return std::all_of (P.begin(), P.end(), [](double i) {return i >= 0.0 && i <= 1.0;}) && (sum == 1);
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
    TPoissonGenerator(std::unique_ptr<TOpt> lambda_) : lambda(std::move(lambda_)), currentDist(lambda->Lambda) {} 
    virtual double Generate() const override{

        std::random_device rd;
        std::mt19937 gen(rd());
        return currentDist(gen);  
    }
private:
    std::unique_ptr<TOpt> lambda;
    mutable std::poisson_distribution<int> currentDist;
};

class TBernoulliGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TBernoulliOptions;
    TBernoulliGenerator(std::unique_ptr<TOpt> p_) : p(std::move(p_)), currentDist(p->P) {}
    virtual double Generate() const override{
        std::random_device rd;
        std::mt19937 gen(rd());
        return currentDist(gen);  
    }
private:
    std::unique_ptr<TOpt> p;
    mutable std::bernoulli_distribution currentDist;
};

class TGeometricGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TGeometricOptions;
    TGeometricGenerator(std::unique_ptr<TOpt> p_) : p(std::move(p_)), currentDist(p->P) {}
    virtual double Generate() const override{
        std::random_device rd;
        std::mt19937 gen(rd());
        return currentDist(gen); 
    }
private:
    std::unique_ptr<TOpt> p;
    mutable std::geometric_distribution<> currentDist;
    
};

class TFiniteGenerator : public TRandomNumberGenerator{
public:
    using TOpt = TFiniteOptions;
    TFiniteGenerator(std::unique_ptr<TOpt> vectors_) : vectors(std::move(vectors_)), currentDist(vectors->P.begin(), vectors->P.end()) {}
    virtual double Generate() const override{
        std::random_device rd;
        std::mt19937 gen(rd());
        return vectors->X[currentDist(gen)];  
    }
private:
    std::unique_ptr<TOpt> vectors;
    mutable std::discrete_distribution<> currentDist;
};
