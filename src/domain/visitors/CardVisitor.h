#ifndef _CARD_VISITOR_H_
#define _CARD_VISITOR_H_

class DebitCard;
class CreditCard;

class CardVisitor {
public:
    virtual ~CardVisitor() = default;
    virtual void visit(DebitCard& debitCard) = 0;
    virtual void visit(CreditCard& creditCard) = 0;
};

#endif
