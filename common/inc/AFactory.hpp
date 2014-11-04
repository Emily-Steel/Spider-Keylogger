#ifndef AFACTORY_H
#define AFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.hpp"

template<class BaseType, typename IDKey = std::string>
class AFactory : public Singleton<AFactory<BaseType, IDKey>>
{
friend class Singleton<AFactory>;

private:
    typedef std::unique_ptr<BaseType>(*typeCreator)();

public:
    AFactory() = default;
    ~AFactory() = default;

    AFactory(const AFactory&) = delete;
    AFactory& operator=(const AFactory&) = delete;

    void registerNewClass(const IDKey& key, const typeCreator& creator)
    {
        _registerTypes.insert({key, creator});
    };

    std::unique_ptr<BaseType> create(const IDKey& key) const
    {
        return (_registerTypes.at(key))();
    };

private:
    std::unordered_map<IDKey, typeCreator> _registerTypes;
};


template<class BaseType, class RealType, typename IDKey = std::string>
class AFactoryRegistration
{
public:
    AFactoryRegistration(const IDKey& key)
    {
        AFactory<BaseType>::instance().registerNewClass(key, &instancier);
    };

    ~AFactoryRegistration() = default;
    AFactoryRegistration(const AFactoryRegistration&);
    AFactoryRegistration& operator=(const AFactoryRegistration&);

    static std::unique_ptr<BaseType> instancier()
    {
        return std::unique_ptr<BaseType>(new RealType());
    };
};

#endif