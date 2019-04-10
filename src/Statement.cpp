
#include <iostream>

#include "statement/all.hpp"




// Statement

Statement::Statement(Statement* parentStatement)
{
    m_parentStatement = parentStatement;
}

Statement* Statement::getParentStatement() const
{
    return m_parentStatement;
}



// SingleStatement

SingleStatement::SingleStatement(Statement* parentStatement)
:Statement(parentStatement)
{
}

SingleStatement::~SingleStatement()
{
    delete m_expression;
}

std::string SingleStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += m_expression->toString(false) + ";\n";

    return rtn;
}

void SingleStatement::setExpression(Expression* expression)
{
    m_expression = expression;
}



// BlockStatement

BlockStatement::BlockStatement(Statement* parentStatement)
:Statement(parentStatement)
{
    BlockStatement* blockStatement;
    FunctionDefStatement* functionDef;

    if (blockStatement = dynamic_cast<BlockStatement*>(parentStatement))
    {
        m_startingStackSize = blockStatement->m_startingStackSize;

        for (auto iter = blockStatement->m_statements.rbegin(); iter != blockStatement->m_statements.rend(); ++iter)
        {
            VariableDefStatement* variableDef = dynamic_cast<VariableDefStatement*>(*iter);
            if (variableDef)
            {
                m_startingStackSize += variableDef->m_size;
            }
        }
    }
    else if (functionDef = dynamic_cast<FunctionDefStatement*>(parentStatement))
    {
        m_startingStackSize = 0;

        for (VariableDefStatement* parameter : functionDef->m_parameters)
        {
            m_startingStackSize += parameter->m_size;
        }
    }
}

BlockStatement::~BlockStatement()
{
    for (Statement* statement : m_statements)
    {
        delete statement;
    }
}

std::string BlockStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "{\n";

    for (auto statement : m_statements)
        rtn.append(statement->toString(depth + 1));

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn.append("}\n");

    return rtn;
}

std::vector<Statement*> const& BlockStatement::getStatementList() const
{
    return m_statements;
}

void BlockStatement::appendStatement(Statement* p_statement)
{
    m_statements.push_back(p_statement);
}



// ControlStatement

ControlStatement::ControlStatement(Statement* parentStatement)
:Statement(parentStatement)
{
    m_condition = nullptr;

    Statement* statement = parentStatement;
    while (statement)
    {
        std::cerr << "****" << statement << " | " << typeid(*statement).name() << std::endl;
        FunctionDefStatement* function = dynamic_cast<FunctionDefStatement*>(statement);
        if (function)
        {
            std::cerr << "####" << function->m_sourceFile << std::endl;
            m_sourceFile = function->m_sourceFile;
            break;
        }
        statement = statement->getParentStatement();
    }

    if (!m_sourceFile)
    {
        std::cerr << "ControlStatement::m_sourceFile is null" << std::endl;
    }
}

ControlStatement::~ControlStatement()
{
    delete m_condition;
}

void ControlStatement::setCondition(Expression* expression)
{
    m_condition = expression;
}



// BreakStatement

BreakStatement::BreakStatement(Statement* parentStatement)
:Statement(parentStatement)
{
    Statement* statement = parentStatement;
    while (statement)
    {
        std::cerr << "****" << statement << " | " << typeid(*statement).name() << std::endl;
        FunctionDefStatement* function = dynamic_cast<FunctionDefStatement*>(statement);
        if (function)
        {
            std::cerr << "####" << function->m_sourceFile << std::endl;
            m_sourceFile = function->m_sourceFile;
            break;
        }
        statement = statement->getParentStatement();
    }
}

BreakStatement::~BreakStatement()
{
}

std::string BreakStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "break;\n";

    return rtn;
}



// ContinueStatement

ContinueStatement::ContinueStatement(Statement* parentStatement)
:Statement(parentStatement)
{
    Statement* statement = parentStatement;
    while (statement)
    {
        std::cerr << "****" << statement << " | " << typeid(*statement).name() << std::endl;
        FunctionDefStatement* function = dynamic_cast<FunctionDefStatement*>(statement);
        if (function)
        {
            std::cerr << "####" << function->m_sourceFile << std::endl;
            m_sourceFile = function->m_sourceFile;
            break;
        }
        statement = statement->getParentStatement();
    }
}

ContinueStatement::~ContinueStatement()
{
}

std::string ContinueStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "continue;\n";

    return rtn;
}



// FunctionDefStatement

FunctionDefStatement::FunctionDefStatement()
:Statement(nullptr)
{
    m_body = nullptr;
}

FunctionDefStatement::~FunctionDefStatement()
{
    delete m_body;
}

std::string FunctionDefStatement::toString(int depth) const
{
    std::string rtn = "void " + m_name + "(";

    bool firstPass = true;
    for (VariableDefStatement* parameter : m_parameters)
    {
        if (!firstPass)
            rtn += ", ";
        rtn += parameter->m_typeName + " " + parameter->m_name;
        firstPass = false;
    }

    rtn += ")\n";

    rtn += m_body->toString(depth);

    return rtn;
}

void FunctionDefStatement::setBody(Statement* body)
{
    m_body = dynamic_cast<BlockStatement*>(body);
}



// IfElseStatement

IfElseStatement::IfElseStatement(Statement* parentStatement)
:ControlStatement(parentStatement)
{
    m_ifBody = nullptr;
    m_elseBody = nullptr;
}

IfElseStatement::~IfElseStatement()
{
    delete m_ifBody;
    delete m_elseBody;
}

std::string IfElseStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "if (" + m_condition->toString(false) + ")\n";
    if (dynamic_cast<BlockStatement*>(m_ifBody))
        rtn += m_ifBody->toString(depth);
    else
        rtn += m_ifBody->toString(depth + 1);

    if (!dynamic_cast<NopStatement*>(m_elseBody))
    {
        for (int i = 0; i < depth; ++i)
            rtn += "    ";
        rtn += "else\n";

        if (dynamic_cast<BlockStatement*>(m_elseBody))
            rtn += m_elseBody->toString(depth);
        else
            rtn += m_elseBody->toString(depth + 1);
    }

    return rtn;
}

void IfElseStatement::setIfBody(Statement* body)
{
    m_ifBody = body;
}

void IfElseStatement::setElseBody(Statement* body)
{
    m_elseBody = body;
}



// WhileStatement

WhileStatement::WhileStatement(Statement* parentStatement)
:ControlStatement(parentStatement)
{
    m_loopBody = nullptr;
}

WhileStatement::~WhileStatement()
{
    delete m_loopBody;
}

std::string WhileStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "while (" + m_condition->toString(false) + ")\n";
    if (dynamic_cast<BlockStatement*>(m_loopBody))
        rtn += m_loopBody->toString(depth);
    else
        rtn += m_loopBody->toString(depth + 1);

    return rtn;
}

void WhileStatement::setLoopBody(Statement* body)
{
    m_loopBody = body;
}



// NopStatement

NopStatement::NopStatement(Statement* parentStatement)
:Statement(parentStatement)
{
}

std::string NopStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; ++i)
        rtn += "    ";

    rtn += "{}\n";

    return rtn;
}



// VariableDefStatement

VariableDefStatement::VariableDefStatement(Statement* parentStatement)
:Statement(parentStatement)
{
    BlockStatement* blockStatement;
    FunctionDefStatement* functionDef;

    m_typeName = "quad";
    m_size = 8;

    if (blockStatement = dynamic_cast<BlockStatement*>(parentStatement))
    {
        m_stackFrameOffset = blockStatement->m_startingStackSize;

        for (auto iter = blockStatement->getStatementList().rbegin(); iter != blockStatement->getStatementList().rend(); ++iter)
        {
            VariableDefStatement* variableDef = dynamic_cast<VariableDefStatement*>(*iter);
            if (variableDef)
            {
                m_stackFrameOffset += variableDef->m_size;
            }
        }

        m_stackFrameOffset += m_size; // this may or may not be needed
    }
    else if (functionDef = dynamic_cast<FunctionDefStatement*>(parentStatement))
    {
        m_stackFrameOffset = 0;

        for (auto iter = functionDef->m_parameters.rbegin(); iter != functionDef->m_parameters.rend(); ++iter)
        {
            m_stackFrameOffset += (*iter)->m_size;
        }

        m_stackFrameOffset += m_size;
    }
    else
    {
        std::cerr << "parentStatement is not a block statement or a function def" << std::endl;
    }
}

std::string VariableDefStatement::toString(int depth) const
{
    std::string rtn;

    for (int i = 0; i < depth; i++)
    {
        rtn += "    ";
    }

    rtn += m_typeName;
    rtn += " ";
    rtn += m_name;
    rtn += ";\n";

    return rtn;
}



