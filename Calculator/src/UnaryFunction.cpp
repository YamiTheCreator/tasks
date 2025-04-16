#include "../include/UnaryFunction.h"

UnaryFunction::UnaryFunction(const UnaryFunctionType op, std::shared_ptr<Value> arg)
        : m_op(op), m_arg(std::move(arg)) {}

[[nodiscard]] double UnaryFunction::calculate() const
{
    const double x = m_arg -> getValue();

    switch (m_op)
    {
        case UnaryFunctionType::MINUS:
            return -x;
        case UnaryFunctionType::SQUARE:
            return x * x;
        case UnaryFunctionType::IDENTITY:
            return x;
        default:
            throw std::invalid_argument("UnaryFunction::calculate: invalid UnaryFunction type");
    }
}
