
#ifndef OrOperator_hpp
#define OrOperator_hpp

#include "BinaryOperator.hpp"
#include "../SourceFile.hpp"


class OrOperator: public BinaryOperator, public RValue
{
public:
    OrOperator(Expression* p_left = nullptr, Expression* p_right = nullptr):
    BinaryOperator("||")
    {
        m_left = p_left;
        m_right = p_right;
    }

    virtual ~OrOperator() = default;

    virtual void assembly(std::ostream& os) const;

    void setParentStatement(Statement* parentStatement)
    {
        Statement* statement = parentStatement;

        while (statement)
        {
            FunctionDefStatement* functionDef = dynamic_cast<FunctionDefStatement*>(statement);
            if (functionDef)
            {
                m_sourceFile = functionDef->m_sourceFile;
                break;
            }
            statement = statement->getParentStatement();
        }
    }

protected:
    const SourceFile* m_sourceFile;
};

#endif

