
#ifndef Type_hpp
#define Type_hpp

#include <string>
#include <vector>

// TODO: move function bodies to .cpp file once interface is complete

class BaseType
{
protected:
    BaseType() = default;

public:
    virtual ~BaseType() = default;

    virtual std::string toString() const = 0;

    virtual int getSize() const
    {
        return 0;
    }
};

class PrimitiveType: public BaseType
{
public:
    PrimitiveType(std::string const& typeName)
    {
        m_typeName = typeName;
    }

    virtual ~PrimitiveType() = default;

    virtual std::string toString() const
    {
        return m_typeName;
    }

    virtual int getSize() const
    {
        return m_size;
    }

protected:
    std::string m_typeName;
    int m_size;
};

class PointerType: public BaseType
{
public:
    PointerType(BaseType* typePointedTo)
    {
        m_typePointedTo = typePointedTo;
    }

    virtual ~PointerType()
    {
        delete m_typePointedTo;
    }

    virtual std::string toString() const
    {
        return m_typePointedTo->toString() + "*";
    }

    virtual int getSize() const
    {
        return 8;
    }

protected:
    BaseType* m_typePointedTo;
};

class StructType: public BaseType
{
public:
    virtual ~StructType()
    {
        for (auto& field : m_fields)
        {
            delete field.second;
        }
    }
    
    // TODO: add fields and brackets
    virtual std::string toString() const
    {
        return "struct " + m_typeName;
    }

    // TODO: account for padding
    virtual int getSize() const
    {
        int size = 0;

        for (auto& field : m_fields)
        {
            size += field.second->getSize();
        }

        return size;
    }

    void appendField(std::string const& name, BaseType* type)
    {
        m_fields.push_back(std::make_pair(name, type));
    }

    BaseType* getFieldType(std::string const& name) const
    {
        for (auto& field : m_fields)
        {
            if (field.first == name)
                return field.second;
        }

        return nullptr;
    }

    // TODO: account for padding
    int getFieldOffset(std::string const& name) const
    {
        int offset = 0;

        for (auto& field : m_fields)
        {
            if (field.first == name)
                break;
            offset += field.second->getSize();
        }

        return offset;
    }

protected:
    std::string m_structName;
    std::vector<std::pair<std::string, BaseType*>> m_fields;
};

class ArrayType: public BaseType
{
public:
    ArrayType(BaseType* elementType, int length)
    {
        m_elementType = elementType;
        m_length = length;
    }

    virtual ~ArrayType()
    {
        delete m_elementType;
    }

    virtual std::string toString() const
    {
        return m_elementType->toString() + "[" + std::to_string(m_length) + "]";
    }

    virtual int getSize() const
    {
        return m_elementType->getSize() * m_length;
    }

protected:
    BaseType* m_elementType;
    int m_length;
};

class TypedefType: public BaseType
{
public:
    TypedefType(BaseType* type, std::string const& name)
    {
        m_type = type;
        m_name = name;
    }

    virtual ~TypedefType()
    {
        delete m_type;
    }

    virtual std::string toString() const
    {
        return m_name;
    }

    virtual int getSize() const
    {
        return m_type->getSize();
    }

protected:
    BaseType* m_type;
    std::string m_name;
};

#endif

