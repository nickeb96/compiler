
#ifndef Statement_hpp
#define Statement_hpp

#include <ostream>
#include <string>
#include <vector>
#include <memory>


class Statement
{
public:
    Statement(Statement* parentStatement);
    virtual ~Statement() = default;
    virtual std::string toString(int depth = 0) const = 0;
    virtual void assembly(std::ostream& os) const = 0;

    Statement* getParentStatement() const;

protected:
    Statement* m_parentStatement;
};

#endif

