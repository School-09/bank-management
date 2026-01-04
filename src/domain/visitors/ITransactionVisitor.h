#ifndef _I_TRANSACTION_VISITOR_H_
#define _I_TRANSACTION_VISITOR_H_

class Deposit;
class Withdraw;
class Transfer;

class ITransactionVisitor {
public:
    virtual ~ITransactionVisitor() = default;
    virtual void visit(Deposit& deposit) = 0;
    virtual void visit(Withdraw& withdraw) = 0;
    virtual void visit(Transfer& transfer) = 0;
};

#endif
