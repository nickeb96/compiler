
#ifndef VariableDefStatement_hpp
#define VariableDefStatement_hpp

#include "Statement.hpp"


class VariableDefStatement: public Statement
{
public:
    VariableDefStatement(Statement* parentStatement);
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

public: // change back to protected
    std::string m_name;
    std::string m_typeName;
    int m_size;
    int m_stackFrameOffset;
};

#endif

