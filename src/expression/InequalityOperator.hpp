
#ifndef InequalityOperator_hpp
#define InequalityOperator_hpp

#include "BinaryOperator.hpp"


class InequalityOperator: public BinaryOperator, public RValue
{
public:
    InequalityOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("!=")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~InequalityOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

