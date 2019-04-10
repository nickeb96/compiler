
#ifndef DereferenceOperator_hpp
#define DereferenceOperator_hpp

#include "UnaryOperator.hpp"


class DereferenceOperator: public UnaryOperator, public LValue
{
public:
    DereferenceOperator(Expression* p_right = nullptr):
    UnaryOperator("*")
    {
        m_right = p_right;
    }

    virtual ~DereferenceOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

