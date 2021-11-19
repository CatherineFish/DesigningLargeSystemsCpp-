#include "factory.h"


class TFactory::TImpl {
	class ICreator {
	public:
		virtual ~ICreator(){}
		virtual std::unique_ptr<TRandomNumbercerator> Create() const = 0;
	};

	using TCreatorPtr = std::shared_ptr<ICreator>;
	using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
	TRegisteredCreators RegisteredCreators;

public:
	template <class TCurrentGenerator>
	class TCreator : public ICreator {
		std::unique_ptr<TRandomNumbercerator> Create() const override{
			return std::make_unique<TCurrentObject>();
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
        RegisterCreator<TSuperObject>("bernoulli");
        RegisterCreator<TSuperObject>("geometric");
        RegisterCreator<TSuperObject>("finite");    
    }

    std::unique_ptr<IObject> CreateObject(const std::string& n) const {
    auto creator = RegisteredCreators.find(n);
    if (creator == RegisteredCreators.end()) {
    return nullptr;
    }
    return creator->second->Create();
}