class TFactory {
	class TImpl;
	std::unique_ptr<const TImpl> Impl;
public:
	TFactory();
	~TFactory();
	std::unique_ptr<TRandomNumberGenerator> CreateObject(
	const std::string& type
	/*, const TOptions opts*/ ) const;
	std::vector<std::string> GetAvailableObjects() const;
};