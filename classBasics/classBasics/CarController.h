#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include "Car.h"

class CarController
{
public:
    CarController(std::istream& m_input, std::ostream& m_output);
    void HandleInput(const std::string& line);

private:
    std::istream& m_input;
    std::ostream& m_output;
    
    Car m_car;
    
    using Handler = std::function<void(std::istream&)>;
    using ActionMap = std::unordered_map<std::string, Handler>;
    const ActionMap m_actionMap;
    
    void Info() const;
    void EngineOn();
    void EngineOff();
    void SetSpeed(std::istream& input);
    void SetGear(std::istream& input);

    std::string OutputDirection(const Direction& direction) const;
};
