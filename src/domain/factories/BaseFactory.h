#ifndef _BASE_FACTORY_H_
#define _BASE_FACTORY_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <stdexcept>

// T là Base Class (VD: Account, Card)
template <typename T>
class BaseFactory {
public:
    // Định nghĩa kiểu hàm tạo: Input là string -> Output là shared_ptr<T>
    using CreatorFunc = std::function<std::shared_ptr<T>(const std::string&)>;

    // Singleton Instance
    static BaseFactory& instance() {
        static BaseFactory inst;
        return inst;
    }

    // Đăng ký class con
    void registerType(const std::string& key, CreatorFunc creator, const std::vector<std::string>& fields) {
        _creators[key] = creator;
        _fields[key] = fields;
    }

    // Tạo object
    std::shared_ptr<T> create(const std::string& key, const std::string& data) {
        if (_creators.find(key) != _creators.end()) {
            return _creators[key](data);
        }
        throw std::runtime_error("Type not registered: " + key);
    }

    // Lấy danh sách field cần nhập
    std::vector<std::string> getFields(const std::string& key) {
        if (_fields.find(key) != _fields.end()) {
            return _fields[key];
        }
        throw std::runtime_error("Type not registered: " + key);
    }

private:
    BaseFactory() = default;
    BaseFactory(const BaseFactory&) = delete;
    BaseFactory& operator=(const BaseFactory&) = delete;
    BaseFactory(BaseFactory&&) = delete;
    BaseFactory& operator=(BaseFactory&&) = delete;

    std::map<std::string, CreatorFunc> _creators;
    std::map<std::string, std::vector<std::string>> _fields;
};

#endif
