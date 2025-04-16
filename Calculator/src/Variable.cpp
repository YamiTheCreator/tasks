#include "../include/Variable.h"

Variable::Variable() : m_value(std::numeric_limits<double>::quiet_NaN()) {}

Variable::Variable(const double value) : m_value(value) {}

double Variable::getValue() const
{
    return m_value;
}

void Variable::setValue(const double value)
{
    if (m_value != value)
    {
        m_value = value;
        notify();
    }
}



