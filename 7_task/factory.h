#include <memory>
#include <vector>
#include "generators.h"

class TFactory {
	class TImpl;
	std::unique_ptr<const TImpl> Impl;
public:
	TFactory();
	~TFactory();
	std::unique_ptr<TRandomNumberGenerator> CreateGenerator(
	const std::string& type
	/*, const TOptions opts*/ ) const;
	std::vector<std::string> GetAvailableGenerators() const;
};