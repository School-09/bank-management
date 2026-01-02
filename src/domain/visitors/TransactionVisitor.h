#ifndef _TRANSACTION_VISITOR_H_
#define _TRANSACTION_VISITOR_H_

class Deposit;
class Withdraw;
class Transfer;

class TransactionVisitor {
public:
    virtual ~TransactionVisitor() = default;
    virtual void visit(Deposit& deposit) = 0;
    virtual void visit(Withdraw& withdraw) = 0;
    virtual void visit(Transfer& transfer) = 0;
};

#endif
