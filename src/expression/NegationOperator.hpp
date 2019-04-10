
#ifndef NegationOperator_hpp
#define NegationOperator_hpp

#include "UnaryOperator.hpp"


class NegationOperator: public UnaryOperator, public RValue
{
public:
    NegationOperator(Expression* p_right = nullptr):
    UnaryOperator("-")
    {
        m_right = p_right;
    }

    virtual ~NegationOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

