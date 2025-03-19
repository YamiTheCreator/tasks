#pragma once
#include <string>

class Car
{
public:
    Car();
    
    //методы действий
    bool IsTurnedOn() const;
    std::string GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;
    
    //сеттеры
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    
private:
    //m_ - member, приватный член класса
    bool m_engineOn;
    int m_gear;
    int m_speed;
    
    bool IsSpeedInGearRange(int gear, int speed) const;
    bool CanSwitchToGear(int gear) const;
};
