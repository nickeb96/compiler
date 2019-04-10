
#ifndef ModuloOperator_hpp
#define ModuloOperator_hpp

#include "BinaryOperator.hpp"


class ModuloOperator: public BinaryOperator, public RValue
{
public:
    ModuloOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("%")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~ModuloOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

