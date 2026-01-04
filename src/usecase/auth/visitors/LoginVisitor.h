#ifndef _LOGIN_VISITOR_H_
#define _LOGIN_VISITOR_H_

#include "../../../domain/visitors/IUserVisitor.h"
#include <string>
using std::string;

class LoginVisitor : public IUserVisitor {
private:
    string _results;

public:
    void visit(Admin& admin) override {
        _results = "Admin";
    }

    void visit(Customer& customer) override {
        _results = "Customer";
    }

    const string getResults() const { 
        return _results;
    }
};

#endif
