
#ifndef LValue_hpp
#define LValue_hpp

#include <ostream>

#include "RValue.hpp"

// Implemented by all expressions that can act as l-values

class LValue: public RValue
{
public:
    virtual ~LValue() = 0;

    friend std::ostream& operator <<(std::ostream& os, LValue const& lvalue);

protected:
    virtual void rValueGenCode(std::ostream& os) const;
};

#endif

