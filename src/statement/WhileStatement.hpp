
#ifndef WhileStatement_hpp
#define WhileStatement_hpp

#include "ControlStatement.hpp"


class WhileStatement: public ControlStatement
{
public:
    WhileStatement(Statement* parentStatement);
    virtual ~WhileStatement();
    virtual std::string toString(int depth = 0) const;
    virtual void assembly(std::ostream& os) const;

    void setLoopBody(Statement* body);

protected:
    Statement* m_loopBody;
};

#endif

