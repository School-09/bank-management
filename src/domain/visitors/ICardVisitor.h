#ifndef _I_CARD_VISITOR_H_
#define _I_CARD_VISITOR_H_

class DebitCard;
class CreditCard;

class ICardVisitor {
public:
    virtual ~ICardVisitor() = default;
    virtual void visit(DebitCard& debitCard) = 0;
    virtual void visit(CreditCard& creditCard) = 0;
};

#endif
