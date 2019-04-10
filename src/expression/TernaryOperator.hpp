
#ifndef TernaryOperator_hpp
#define TernaryOperator_hpp

#include "OperatorExpression.hpp"


class TernaryOperator: public OperatorExpression
{
public:
    TernaryOperator()
    {
    }

    virtual ~TernaryOperator() = default;

protected:
    Expression* m_condition;
    Expression* m_first;
    Expression* m_second;
};

#endif

