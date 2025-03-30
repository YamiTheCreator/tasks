#include "Car.h"

#include <sstream>
#include <stdexcept>
#include <utility>
#include <unordered_map>

using SpeedLimits = std::pair<int, int>;

const std::unordered_map<int, SpeedLimits> MATCHING_GEAR_AND_SPEED =
{
    { static_cast<int>(Gear::ReverseGear), { 0, 20 } },
    { static_cast<int>(Gear::NeutralGear), { 0, INT_MAX } },
    { static_cast<int>(Gear::FirstGear), { 0, 30 } },
    { static_cast<int>(Gear::SecondGear), { 20, 50 } },
    { static_cast<int>(Gear::ThirdGear), { 30, 60 } },
    { static_cast<int>(Gear::FourthGear), { 40, 90 } },
    { static_cast<int>(Gear::FifthGear), { 50, 150 } }
};

bool IsSpeedInLimit (int speed, int min_speed, int max_speed)
{
    return ( speed >= min_speed ) && ( speed <= max_speed );
}

bool Car::IsTurnedOn() const
{
    return m_engineOn;
}

Direction Car::GetDirection() const
{
    if (m_speed > 0 && m_gear > Gear::NeutralGear)
        return Direction::forward;
    
    if (m_speed < 0 && m_gear == Gear::ReverseGear)
        return Direction::backward;
    
    return Direction::standing;
}

Gear Car::GetGear() const
{
    return m_gear;
}

int Car::GetSpeed() const
{
    return std::abs(m_speed);
}

void Car::TurnOnEngine()
{
    if (m_engineOn)
        throw std::runtime_error("Engine is already turned on\n");
    
    m_engineOn = true;
    m_gear = Gear::NeutralGear;
    m_speed = 0;
}

void Car::TurnOffEngine()
{
    if (m_gear != Gear::NeutralGear || m_speed != 0)
        throw std::runtime_error("Car must be stopped and in neutral gear\n");
    
    m_engineOn = false;
}

void Car::SetGear(int gear)
{
    if (gear < static_cast<int>(Gear::ReverseGear) || gear > static_cast<int>(Gear::FifthGear))
        throw std::runtime_error("Invalid gear\n");
    
    if (!m_engineOn)
    {
        if (gear == static_cast<int>(Gear::NeutralGear))
        {
            m_gear = Gear::NeutralGear;
            return;
        }
        
        throw std::runtime_error("Сannot set gear while engine is off\n");
    }
    
    if (gear == static_cast<int>(Gear::ReverseGear) && m_speed != 0)
        throw std::runtime_error("Cannot reverse while moving\n");
        
    if ((m_gear == Gear::ReverseGear && gear > 0 && m_speed != 0) || (static_cast<int>(m_gear) > 0 &&
        gear == static_cast<int>(Gear::ReverseGear) && m_speed != 0))
        throw std::runtime_error("Unsuitable current speed\n");
    
    ChangeGear(gear);
}
//TODO: есть дублирование кода в нижних функциях, спросить, критично ли это
void Car::SetSpeed(int speed)
{
    if (speed < 0)
            throw std::runtime_error("Speed cannot be negative\n");
    
    if (!m_engineOn)
        throw std::runtime_error("Cannot set speed while engine is off\n");
    
    const auto [min_speed, max_speed] = MATCHING_GEAR_AND_SPEED.at(static_cast<int>(m_gear));
    
    if (m_gear == Gear::NeutralGear)
    {
        if (speed > std::abs(m_speed))
            throw std::runtime_error("Cannot accelerate on neutral\n");
        
        m_speed = (m_speed < 0) ? -speed : speed;
        return;
    }
    
    if (!IsSpeedInLimit(speed, min_speed, max_speed))
        throw std::runtime_error("Speed is out of gear range\n");
    
    m_speed = (m_gear == Gear::ReverseGear) ? -speed : speed;
}

void Car::ChangeGear(int gear)
{
    if (gear == static_cast<int>(Gear::NeutralGear))
    {
        m_gear = Gear::NeutralGear;
        return;
    }
    
    if (gear == static_cast<int>(Gear::ReverseGear))
    {
        if (!(m_speed == 0))
            throw std::runtime_error("Cannot reverse while moving\n");
        
        m_gear = Gear::ReverseGear;
        return;
    }
    
    const auto [min_speed, max_speed] = MATCHING_GEAR_AND_SPEED.at(gear);
    
    if (!IsSpeedInLimit(m_speed, min_speed, max_speed))
        throw std::runtime_error("Unsuitable current speed\n");
    
    m_gear = static_cast<Gear>(gear);
}
