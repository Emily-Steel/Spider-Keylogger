#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>
#include <functional>
#include <memory>
#include <utility>

template<class SingleClass>
class Singleton
{
public:
    Singleton() = default;
    virtual ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    template<typename... Args>
    static SingleClass& instance(Args&&... args)
    {
        std::call_once(get_once_flag(), [](Args&&... arg){
        _instance.reset(new SingleClass(std::forward<Args>(arg)...));
        }, std::forward<Args>(args)...);
        return *(_instance.get());
    };

private:
    static std::unique_ptr<SingleClass> _instance;
    static std::once_flag& get_once_flag() {
        static std::once_flag once;
        return once;
    };
};

template<class T> std::unique_ptr<T> Singleton<T>::_instance = nullptr;

#endif