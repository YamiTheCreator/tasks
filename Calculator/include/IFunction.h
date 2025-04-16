#pragma once

#include <optional>
#include "Value.h"
#include "IObserver.h"

class IFunction : public Value, public IObserver
{
public:
    IFunction() = default;
    ~IFunction() override = default;

    [[nodiscard]] double getValue() const override;

    void update() override;
protected:
    mutable std::optional<double> m_cachedValue;
    [[nodiscard]] virtual double calculate() const = 0;
};