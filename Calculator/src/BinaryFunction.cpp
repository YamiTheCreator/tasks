#include "../include/BinaryFunction.h"

BinaryFunction::BinaryFunction(const BinaryFunctionType op, std::shared_ptr<Value> left, std::shared_ptr<Value> right)
        : m_op(op), m_arg1(std::move(left)), m_arg2(std::move(right)) {}

[[nodiscard]] double BinaryFunction::calculate() const
{
    const double a = m_arg1 -> getValue();
    const double b = m_arg2 -> getValue();

    switch (m_op)
    {
        case BinaryFunctionType::ADD:
            return a + b;
        case BinaryFunctionType::SUBTRACT:
            return a - b;
        case BinaryFunctionType::MULTIPLY:
            return a * b;
        case BinaryFunctionType::DIVISION:
            if (b == 0 || isnan(a) || isnan(b) )
                return std::numeric_limits<double>::quiet_NaN();
        default:
            throw std::invalid_argument("BinaryFunction::calculate: invalid BinaryFunction type");
    }
}