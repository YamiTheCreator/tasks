#include "Car.h"
#include <string>
#include <cmath>

//конструктор-инициализатор
Car::Car()
    : m_engineOn(false)
    , m_gear(0)
    , m_speed(0)
{
}

bool Car::IsTurnedOn() const
{
    return m_engineOn;
}

std::string Car::GetDirection() const
{
    if (m_speed == 0)
    {
        return "standing still";
    }
    return (m_gear == -1 || (m_gear == 0 && m_speed < 0)) ? "backward" : "forward";
}

int Car::GetSpeed() const
{
    return std::abs(m_speed);
}

int Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    m_engineOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (!m_engineOn)
    {
        return true;
    }
    
    if (m_speed != 0 || m_gear != 0)
    {
        return false;
    }
    
    m_engineOn = false;
    return true;
}

bool Car::IsSpeedInGearRange(int gear, int speed) const
{
    speed = std::abs(speed);
    
    switch (gear)
    {
        case -1: return speed >= 0 && speed <= 20;
        case 0: return true; // No restrictions for neutral
        case 1: return speed >= 0 && speed <= 30;
        case 2: return speed >= 20 && speed <= 50;
        case 3: return speed >= 30 && speed <= 60;
        case 4: return speed >= 40 && speed <= 90;
        case 5: return speed >= 50 && speed <= 150;
        default: return false;
    }
}

bool Car::CanSwitchToGear(int gear) const
{
    if (!m_engineOn && gear != 0)
    {
        return false;
    }
    
    if (gear < -1 || gear > 5)
    {
        return false;
    }
    
    if (!IsSpeedInGearRange(gear, m_speed))
    {
        return false;
    }
    
    if (gear == -1 && m_speed != 0)
    {
        return false;
    }
    
    if ((m_gear == -1 && gear > 0 && m_speed != 0) ||
        (m_gear > 0 && gear == -1 && m_speed != 0))
    {
        return false;
    }
    
    if (m_gear == 0 && m_speed < 0 && gear > 0)
    {
        return false;
    }
    
    return true;
}

bool Car::SetGear(int gear)
{
    if (!CanSwitchToGear(gear))
    {
        return false;
    }
    
    m_gear = gear;
    return true;
}

bool Car::SetSpeed(int speed)
{
    if (speed < 0) {
        return false;
    }
    
    if (!m_engineOn)
    {
        return false;
    }
    
    if (m_gear == 0)
    {
        if (m_speed > 0 && speed > m_speed)
        {
            return false;
        }
        if (m_speed < 0 && speed > std::abs(m_speed))
        {
            return false;
        }
    }
    
    if (!IsSpeedInGearRange(m_gear, speed))
    {
        return false;
    }
    
    if (m_gear == -1)
    {
        m_speed = -speed;
    }
    else if (m_gear == 0)
    {
        if (m_speed < 0)
        {
            m_speed = -speed;
        }
        else
        {
            m_speed = speed;
        }
    }
    else
    {
        m_speed = speed;
    }
    
    return true;
}
