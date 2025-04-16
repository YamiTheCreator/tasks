#include "../include/Value.h"

void Value::addObserver(const std::shared_ptr<IObserver>& observer)
{
    m_observers.push_back(observer);
}

void Value::notify() const
{
    for (const auto& weak_observer : m_observers)
    {
        if (const auto observer = weak_observer.lock())
        {

        }
    }
}