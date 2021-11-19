#include "factory.h"

int main() {
	TFactory factory;
	auto generators = factory.GetAvailableGenerators();
	for (const auto& gen : generators) {
		std::cout << gen << std::endl;
	}
	for (const auto& genName : {"poisson", "bernoulli", "geometric", "finite"}) {
		factory.CreateGenerator(genName)->Generate();
	}
	return 0;
}