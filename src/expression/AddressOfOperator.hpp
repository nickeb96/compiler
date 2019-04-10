
#ifndef AddressOfOperator_hpp
#define AddressOfOperator_hpp

#include "UnaryOperator.hpp"


class AddressOfOperator: public UnaryOperator, public RValue
{
public:
    AddressOfOperator(Expression* right = nullptr):
    UnaryOperator("&")
    {
        m_right = right;
    }

    virtual ~AddressOfOperator() = default;

    virtual void assembly(std::ostream& os) const;
};

#endif

