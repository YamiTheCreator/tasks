#pragma once

#include "IFunction.h"
#include "Value.h"

enum class BinaryFunctionType
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVISION
};

class BinaryFunction final : public IFunction
{
public:
    BinaryFunction(BinaryFunctionType op, std::shared_ptr<Value> left, std::shared_ptr<Value> right);
    ~BinaryFunction() override = default;

    static std::shared_ptr<BinaryFunction> create(BinaryFunctionType op, const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right)
    {
        auto ptr = std::make_shared<BinaryFunction>(op, left, right);
        left->addObserver(ptr);
        right->addObserver(ptr);
        return ptr;
    }

private:
    BinaryFunctionType m_op;
    std::shared_ptr<Value> m_arg1;
    std::shared_ptr<Value> m_arg2;
    double calculate() const override;
};