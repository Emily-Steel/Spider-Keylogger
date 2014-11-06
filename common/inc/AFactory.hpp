#ifndef AFACTORY_H
#define AFACTORY_H

#include <string>
#include <memory>
#include <iostream>
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

    template<typename... Args>
    std::unique_ptr<BaseType> create(const IDKey& key, Args&&... args) const
    {
        return (_registerTypes.at(key))(std::forward<Args>(args)...);
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
        std::cout << "Registering: " << key << std::endl;
        AFactory<BaseType>::instance().registerNewClass(key, &instancier);
    };

    ~AFactoryRegistration() = default;
    AFactoryRegistration(const AFactoryRegistration&) = delete;
    AFactoryRegistration& operator=(const AFactoryRegistration&) = delete;

    static std::unique_ptr<BaseType> instancier()
    {
        return std::unique_ptr<BaseType>(new RealType());
    };
};

#endif