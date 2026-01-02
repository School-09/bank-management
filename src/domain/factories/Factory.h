#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <mutex>

template<typename Base, typename... Args>
class Factory {
public:
    using Creator = std::function<std::shared_ptr<Base>(Args...)>;

    // Singleton access
    static Factory& instance() {
        static Factory inst;
        return inst;
    }

    // Register type
    void registerType(const std::string& key, Creator creator) {
        std::lock_guard<std::mutex> lock(_mtx);
        _creators[key] = std::move(creator);
    }

    // Create object
    std::shared_ptr<Base> create(const std::string& key, Args... args) {
        std::lock_guard<std::mutex> lock(_mtx);
        auto it = _creators.find(key);
        if (it == _creators.end()) {std::cout << "ko co key\n"; return nullptr;}
        return (it->second)(std::forward<Args>(args)...);
    }

    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

private:
    Factory() = default;

    std::map<std::string, Creator> _creators;
    std::mutex _mtx;
};

#endif
