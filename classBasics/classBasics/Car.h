#pragma once

enum class Direction
{
    standing,
    forward,
    backward
};

enum class Gear
{
    ReverseGear = -1,
    NeutralGear,
    FirstGear,
    SecondGear,
    ThirdGear,
    FourthGear,
    FifthGear
};

class Car
{
public:
    Car() = default;
    
    bool IsTurnedOn() const;
    
    Gear GetGear() const;
    int GetSpeed() const;
    Direction GetDirection() const;
    
    void TurnOnEngine();
    void TurnOffEngine();
    
    void SetGear(int gear);
    void SetSpeed(int speed);
    
private:
    bool m_engineOn = false;
    Gear m_gear = Gear::NeutralGear;
    int m_speed = 0;

    void ChangeGear(int gear);
};
