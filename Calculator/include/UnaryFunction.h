#pragma once

#include "IFunction.h"
#include "Value.h"

enum class UnaryFunctionType
{
    SQUARE,
    MINUS,
    IDENTITY,
};

class UnaryFunction final : public IFunction
{
public:
    UnaryFunction(UnaryFunctionType op, std::shared_ptr<Value> arg);
    ~UnaryFunction() override = default;

    static std::shared_ptr<UnaryFunction> create(UnaryFunctionType op, const std::shared_ptr<Value>& arg)
    {
        auto ptr = std::make_shared<UnaryFunction>(op, arg);
        arg->addObserver(ptr);
        return ptr;
    }

private:
    UnaryFunctionType m_op;
    std::shared_ptr<Value> m_arg;
    [[nodiscard]] double calculate() const override;
};