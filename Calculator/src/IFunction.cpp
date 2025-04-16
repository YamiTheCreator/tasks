#include "../include/IFunction.h"

[[nodiscard]] double IFunction::getValue() const
{
    if (!m_cachedValue)
    {
        m_cachedValue = calculate();
    }

    return *m_cachedValue;
}

void IFunction::update()
{
    if (m_cachedValue)
    {
        m_cachedValue.reset();
        notify();
    }
}