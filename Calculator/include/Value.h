#pragma once

#include <vector>
#include "IObserver.h"

class Value
{
public:
    Value() = default;
    virtual ~Value() = default;
    [[nodiscard]] virtual double getValue() const = 0;

    void addObserver(const std::shared_ptr<IObserver>& observer);

protected:
    void notify() const;

private:
    std::vector<std::weak_ptr<IObserver>> m_observers;
};