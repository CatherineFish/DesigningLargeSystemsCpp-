#include <map>
#include "factory.h"

class TFactory::TImpl {
	class ICreator {
	public:
		virtual ~ICreator(){}
		virtual std::unique_ptr<TRandomNumberGenerator> Create(std::unique_ptr<TOptions> &&opts) const = 0;
	};

	using TCreatorPtr = std::shared_ptr<ICreator>;
	using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
	TRegisteredCreators RegisteredCreators;

public:
	template <class TCurrentGenerator>
	class TCreator : public ICreator {
		std::unique_ptr<TRandomNumberGenerator> Create(std::unique_ptr<TOptions> &&opts) const override{
			auto CurrenOptions = dynamic_cast<typename TCurrentGenerator::TOpt*>(opts.get());
            opts.release();
            if (!CurrenOptions || !CurrenOptions->IsValid())
            {
                return nullptr;
            }
            return std::make_unique<TCurrentGenerator>(std::unique_ptr<typename TCurrentGenerator::TOpt>(CurrenOptions));
		}
	};
    TImpl() { 
        RegisterAll();
    }
    
    template <typename T>
    void RegisterCreator(const std::string& type) {
        RegisteredCreators[type] = std::make_shared<TCreator<T>>();
    }
    
    void RegisterAll() {
        RegisterCreator<TPoissonGenerator>("poisson");
        RegisterCreator<TBernoulliGenerator>("bernoulli");
        RegisterCreator<TGeometricGenerator>("geometric");
        RegisterCreator<TFiniteGenerator>("finite");    
    }

    std::unique_ptr<TRandomNumberGenerator> CreateGenerator(const std::string& t, std::unique_ptr<TOptions> &&opts) const {
        auto creator = RegisteredCreators.find(t);
        if (creator == RegisteredCreators.end()) {
            return nullptr;
        }
        return creator->second->Create(std::move(opts));
    }

    std::vector<std::string> GetAvailableGenerators () const {
        std::vector<std::string> result;
        for (const auto& creatorPair : RegisteredCreators) {
            result.push_back(creatorPair.first);
        }
        return result;
    }
};


std::unique_ptr<TRandomNumberGenerator> TFactory::CreateGenerator(const std::string& t, std::unique_ptr<TOptions> &&opts) const {
    return Impl->CreateGenerator(t, std::move(opts));
}

TFactory::TFactory() : Impl(std::make_unique<TFactory::TImpl>()) {}
TFactory::~TFactory(){}

std::vector<std::string> TFactory::GetAvailableGenerators() const {
    return Impl->GetAvailableGenerators();
}