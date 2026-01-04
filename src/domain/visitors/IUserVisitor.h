#ifndef _I_USER_VISITOR_H_
#define _I_USER_VISITOR_H_

class Customer;
class Admin;

class IUserVisitor {
public:
    virtual ~IUserVisitor() = default;
    virtual void visit(Customer& customer) = 0;
    virtual void visit(Admin& admin) = 0;
};

#endif
