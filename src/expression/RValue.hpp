
#ifndef RValue_hpp
#define RValue_hpp

#include <ostream>

// Implemented by all expressions that can act as r-values

class RValue
{
public:
    virtual ~RValue() = 0;

    friend std::ostream& operator <<(std::ostream& os, RValue const& rvalue);

protected:
    virtual void rValueGenCode(std::ostream& os) const;
};

#endif

