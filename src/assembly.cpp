
#include <iostream>

#include "expression/all.hpp"
#include "statement/all.hpp"
#include "SourceFile.hpp"


// Expression


void IntegerLiteral::assembly(std::ostream& os) const
{
    os << "movq $" << m_str << ", %rax" << std::endl;
}


void IdentifierExpression::assembly(std::ostream& os) const
{
    //os << "movq %rbp, %rax" << std::endl;
    //os << "subq $" << m_offset << ", %rax" << std::endl;

    os << "leaq -" << m_offset << "(%rbp), %rax" << "  #" << m_name << std::endl;
}


void AdditionOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rdx" << std::endl;
    os << "popq %rax" << std::endl;
    os << "addq %rdx, %rax" << std::endl;
}


void SubtractionOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rdx" << std::endl;
    os << "popq %rax" << std::endl;
    os << "subq %rdx, %rax" << std::endl;
}


void MultiplicationOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rdx" << std::endl;
    os << "popq %rax" << std::endl;
    os << "imulq %rdx, %rax" << std::endl;
}


void DivisionOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rax" << std::endl;
    os << "cqto" << std::endl;
    os << "idivq %rcx" << std::endl;
}


void ModuloOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rax" << std::endl;
    os << "cqto" << std::endl;
    os << "idivq %rcx" << std::endl;
    os << "movq %rdx, %rax" << std::endl;
}


void AssignmentOperator::assembly(std::ostream& os) const
{
    LValue* left = dynamic_cast<LValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *right;
    os << "pushq %rax" << std::endl;
    os << *left;
    os << "popq %rdx" << std::endl;
    os << "movq %rdx, (%rax)" << std::endl;
    os << "movq %rdx, %rax" << std::endl;
}


void NegationOperator::assembly(std::ostream& os) const
{
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *right;
    os << "negq %rax" << std::endl;
}


void AddressOfOperator::assembly(std::ostream& os) const
{
    LValue* right = dynamic_cast<LValue*>(m_right);

    os << *right;
}


void DereferenceOperator::assembly(std::ostream& os) const
{
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *right;
}


void LessThanOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "setl %al" << std::endl;
}


void GreaterThanOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "setg %al" << std::endl;
}


void LessThanEqualOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "setle %al" << std::endl;
}


void GreaterThanEqualOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "setge %al" << std::endl;
}


void EqualityOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "sete %al" << std::endl;
}


void InequalityOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *left;
    os << "pushq %rax" << std::endl;
    os << *right;
    os << "movq %rax, %rcx" << std::endl;
    os << "popq %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "cmpq %rcx, %rdx" << std::endl;
    os << "setne %al" << std::endl;
}


void AndOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);
    std::string labelEnd = m_sourceFile->getNewLabel();

    os << *left;
    os << "testq %rax, %rax" << std::endl;
    os << "jz " << labelEnd << std::endl;
    os << *right;
    os << labelEnd << ":" << std::endl;
}


void OrOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* right = dynamic_cast<RValue*>(m_right);
    std::string labelEnd = m_sourceFile->getNewLabel();

    os << *left;
    os << "testq %rax, %rax" << std::endl;
    os << "jnz " << labelEnd << std::endl;
    os << *right;
    os << labelEnd << ":" << std::endl;
}


void NotOperator::assembly(std::ostream& os) const
{
    RValue* right = dynamic_cast<RValue*>(m_right);

    os << *right;
    os << "movq %rax, %rdx" << std::endl;
    os << "xorq %rax, %rax" << std::endl;
    os << "testq %rdx, %rdx" << std::endl;
    os << "setz %al" << std::endl;
}


void SubscriptOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* index = dynamic_cast<RValue*>(m_index);

    os << *index;
    os << "imulq $" << 8 << ", %rax" << std::endl;
    os << "pushq %rax" << std::endl;
    os << *left;
    os << "popq %rdx" << std::endl;
    os << "addq %rdx, %rax" << std::endl;
}


void FunctionCallOperator::assembly(std::ostream& os) const
{
    RValue* left = dynamic_cast<RValue*>(m_left);
    RValue* arg;

    for (auto iter = m_arguments.rbegin(); iter != m_arguments.rend(); ++iter)
    {
        arg = dynamic_cast<RValue*>(*iter);
        os << *arg;
        os << "pushq %rax" << std::endl;
    }

    std::vector<std::string> registers = {"rdi", "rsi", "rdx", "rcx"};

    for (int i = 0; i < m_arguments.size() && i < registers.size(); i++) // 4 is the number of arguments that can fit in registers
    {
        os << "popq %" << registers[i] << std::endl;
    }

    os << "pushq %rbx" << std::endl;
    os << "movq %rsp, %rbx" << std::endl;
    os << "andq $-16, %rsp" << std::endl;
    os << "callq _" << dynamic_cast<IdentifierExpression*>(m_left)->m_name << std::endl;;
    os << "movq %rbx, %rsp" << std::endl;
    os << "popq %rbx" << std::endl;
}



// Statement


void NopStatement::assembly(std::ostream& os) const
{
    os << "nop" << std::endl;
}


void VariableDefStatement::assembly(std::ostream& os) const
{
    os << "subq $" << m_size << ", %rsp" << "#" << m_name << std::endl;
}


void SingleStatement::assembly(std::ostream& os) const
{
    RValue* expression = dynamic_cast<RValue*>(m_expression);

    os << *expression;
}


void BlockStatement::assembly(std::ostream& os) const
{
    for (auto statement : m_statements)
    {
        statement->assembly(os);
    }

    int stackSize = 0;
    for (auto statement : m_statements)
    {
        VariableDefStatement* variableDef = dynamic_cast<VariableDefStatement*>(statement);
        if (variableDef)
        {
            stackSize += variableDef->m_size;
        }
    }

    if (stackSize > 0)
    {
        os << "addq $" << stackSize << ", %rsp" << std::endl;
    }
}


void IfElseStatement::assembly(std::ostream& os) const
{
    RValue* condition = dynamic_cast<RValue*>(m_condition);
    std::string labelElse = m_sourceFile->getNewLabel();
    std::string labelEnd = m_sourceFile->getNewLabel();

    os << *condition;
    os << "testq %rax, %rax" << std::endl;
    os << "jz " << labelElse << std::endl;
    m_ifBody->assembly(os);

    if (!dynamic_cast<NopStatement*>(m_elseBody))
    {
        os << "jmp " << labelEnd << std::endl;
    }

    os << labelElse << ":" << std::endl;

    if (!dynamic_cast<NopStatement*>(m_elseBody))
    {
        m_elseBody->assembly(os);
        os << labelEnd << ":" << std::endl;
    }
}


void WhileStatement::assembly(std::ostream& os) const
{
    RValue* condition = dynamic_cast<RValue*>(m_condition);
    std::string labelStart = m_sourceFile->getNewLabel();
    std::string labelEnd = m_sourceFile->getNewLabel();

    m_sourceFile->m_breakLabels.push(labelEnd);
    m_sourceFile->m_continueLabels.push(labelStart);

    os << labelStart << ":" << std::endl;
    os << *condition;
    os << "testq %rax, %rax" << std::endl;
    os << "jz " << labelEnd << std::endl;
    m_loopBody->assembly(os);
    os << "jmp " << labelStart << std::endl;
    os << labelEnd << ":" << std::endl;

    m_sourceFile->m_breakLabels.pop();
    m_sourceFile->m_continueLabels.pop();
}

#if 0
void DoWhileStatement::assembly(std::ostream& os) const
{
    RValue* condition = dynamic_cast<RValue*>(m_condition);
    std::string labelStart = m_sourceFile->getNewLabel();

    os << labelStart << ":" << std::endl;
    m_loopBody->assembly(os);
    os << *condition;
    os << "testq %rax, %rax" << std::endl;
    os << "jnz " << labelStart << std::endl;
}
#endif

void BreakStatement::assembly(std::ostream& os) const
{
    os << "jmp " << m_sourceFile->m_breakLabels.top() << std::endl;
}


void ContinueStatement::assembly(std::ostream& os) const
{
    os << "jmp " << m_sourceFile->m_continueLabels.top() << std::endl;
}


void FunctionDefStatement::assembly(std::ostream& os) const
{
    os << ".global _" << m_name << std::endl;
    os << "_" << m_name << ":" << std::endl;
    os << "pushq %rbp" << std::endl;
    os << "movq %rsp, %rbp" << std::endl;

    std::vector<std::string> registers = {"rdi", "rsi", "rdx", "rcx"};

    for (int i = 0; i < m_parameters.size() && i < registers.size(); i++) /* put all of the parameters onto the stack */
    {
        os << "pushq %" << registers[i] << std::endl;
    }

    m_body->assembly(os);

    //if (!dynamic_cast<ReturnStatement*>(m_body->getStatementList().back())) /* if last statement is not return statement, generate default return */
    {
        os << "movq %rbp, %rsp" << std::endl;
        os << "popq %rbp" << std::endl;
        os << "retq" << std::endl;
    }
}

#if 0
void ReturnStatement::assembly(std::ostream& os) const
{
    RValue* expression = dynamic_cast<RValue*>(m_expression);

    os << *expression;
    os << "movq %rbp, %rsp" << std::endl;
    os << "popq %rbp" << std::endl;
    os << "retq" << std::endl;
}
#endif

void SourceFile::assembly(std::ostream& os) const
{
    for (auto func : m_functions)
    {
        os << std::endl;
        func->assembly(os);
        os << std::endl;
    }
}


