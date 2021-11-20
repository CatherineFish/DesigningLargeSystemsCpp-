#include "factory.h"

int main() {
	TFactory factory;
	auto generators = factory.GetAvailableGenerators();
	for (const auto& gen : generators) {
		std::cout << gen << std::endl;
	}
	//for (const auto& genName : {"poisson", "bernoulli", "geometric", "finite"}) {
	//	factory.CreateGenerator(genName)->Generate();
	//}

	//for (const auto& [genName, arguments]: view::zip({"poisson", "bernoulli", "geometric"}, {5.0, 0.5, 0.7})) {
	//	factory.CreateGenerator(genName, arguments)->Generate();
	//}

	factory.CreateGenerator("poisson", std::make_unique<TPoissonOptions>(5.0))->Generate();
	return 0;
}