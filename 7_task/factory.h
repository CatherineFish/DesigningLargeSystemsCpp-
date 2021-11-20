#include <memory>
#include <vector>
#include "generators.h"

class TFactory {
	class TImpl;
	std::unique_ptr<const TImpl> Impl;
//	using OptionForFinite = std::tuple<std::vector<double>, std::vector<double>>;
public:
  	//using TGeneratorOptions = std::unique_ptr<TOptions>;

	TFactory();
	~TFactory();
	std::unique_ptr<TRandomNumberGenerator> CreateGenerator(
		const std::string& type,
		std::unique_ptr<TOptions>&& opts) const;
	std::vector<std::string> GetAvailableGenerators() const;
};