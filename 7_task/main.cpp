#include <cmath>
#include <cassert>
#include "factory.h"

int N = 1000;

void TestPoisson (TFactory & factory, double lambda)
{
	auto curGenerator = factory.CreateGenerator("poisson", std::make_unique<TPoissonOptions>(lambda));
	double sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		sum += curGenerator->Generate();
	}
	std::cout << "\nPoisson" << std::endl;
	std::cout << "Эмипирическое среднее: " << sum / N << std::endl;
	std::cout << "Теоретическое среднее: " << lambda << std::endl;
	std::cout << "Разница: " << std::abs((double)sum / N - lambda) << std::endl;
	return;
}


void TestBernoulli (TFactory & factory, double p)
{
	auto curGenerator = factory.CreateGenerator("bernoulli", std::make_unique<TBernoulliOptions>(p));
	double sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		sum += curGenerator->Generate();
	}
	std::cout << "\nBernoulli" << std::endl;
	std::cout << "Эмипирическое среднее: " << sum / N << std::endl;
	std::cout << "Теоретическое среднее: " << p << std::endl;
	std::cout << "Разница: " << std::abs((double)sum / N - p) << std::endl;
	return;
}


void TestGeometric (TFactory & factory, double p)
{
	auto curGenerator = factory.CreateGenerator("geometric", std::make_unique<TGeometricOptions>(p));
	double sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		sum += curGenerator->Generate();
	}
	std::cout << "\nGeometric" << std::endl;
	std::cout << "Эмипирическое среднее: " << sum / N << std::endl;
	std::cout << "Теоретическое среднее: " << (1 - p) / p << std::endl;
	std::cout << "Разница: " << std::abs((double)sum / N - (double)(1 - p) / p) << std::endl;
	return;
}

void TestFinite (TFactory & factory, std::vector<double> x, std::vector<double> p)
{
	auto curGenerator = factory.CreateGenerator("finite", std::make_unique<TFiniteOptions>(x, p));
	double sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		sum += curGenerator->Generate();
	}
	
	double av = 0.0;
	
	for (size_t i = 0; i < p.size(); i++) {
		av += p[i] * x[i];
	}

	std::cout << "\nFinite" << std::endl;
	std::cout << "Эмипирическое среднее: " << sum / N << std::endl;
	std::cout << "Теоретическое среднее: " << av << std::endl;
	std::cout << "Разница: " << std::abs((double)sum / N - av) << std::endl;
	return;
}

int main() {
	TFactory factory;
	auto generators = factory.GetAvailableGenerators();
	for (const auto& gen : generators) {
		std::cout << gen << std::endl;
	}
	TestPoisson(factory, 0.1);
    TestPoisson(factory, 1);
    TestPoisson(factory, 5);
    TestBernoulli(factory, 0.1);
    TestBernoulli(factory, 0.9);
    TestBernoulli(factory, 0.5);
    TestGeometric(factory, 0.1);
    TestGeometric(factory, 0.9);
    TestGeometric(factory, 0.5);
    TestFinite(
        factory,
        {0, 1, 2, 3, 4, 5},
        {0.1, 0.1, 0.1, 0.2, 0.3, 0.2}
    );
    TestFinite(
        factory,
        {-50, -100, 0, 1},
        {0.4, 0.4, 0.1, 0.1}  
    );
    TestFinite(
        factory,
        {-10000, 10000},
        {0.1, 0.9}
    );
	

	auto badArg1 = factory.CreateGenerator("poisson", std::make_unique<TPoissonOptions>(-10));
    assert(!badArg1);
    auto badArgd2 = factory.CreateGenerator("bernoulli", std::make_unique<TBernoulliOptions>(-2));
    assert(!badArgd2);
    auto badArg3 = factory.CreateGenerator("geometric", std::make_unique<TGeometricOptions>(2));
    assert(!badArg3);
    auto badArgd4 = factory.CreateGenerator("finite", std::make_unique<TFiniteOptions>(std::vector<double>{1, 2}, std::vector<double>{0.6, 0.6}));
    assert(!badArgd4);
	
	return 0;
}