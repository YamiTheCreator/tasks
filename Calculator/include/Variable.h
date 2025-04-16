#pragma once

#include "Value.h"

class Variable final : public Value
{
public:
    Variable();
    explicit Variable(double value = 0.0);
    ~Variable() override = default;

    void setValue(double value);
    [[nodiscard]] double getValue() const override;

private:
    double m_value;
};