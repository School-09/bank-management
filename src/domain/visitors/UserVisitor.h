#ifndef _USER_VISITOR_H_
#define _USER_VISITOR_H_

class Customer;
class Admin;

class UserVisitor {
public:
    virtual ~UserVisitor() = default;
    virtual void visit(Customer& customer) = 0;
    virtual void visit(Admin& admin) = 0;
};

#endif
