#pragma once
#include "Car.h"
#include <string>
#include <iostream>

class CarController
{
public:
    CarController(std::ostream& output = std::cout);
    
    void ProcessCommand(const std::string& commandLine);
    
private:
    Car m_car;
    std::ostream& m_output;
    
    void PrintInfo() const;
    void ProcessEngineOn();
    void ProcessEngineOff();
    void ProcessSetGear(const std::string& arg);
    void ProcessSetSpeed(const std::string& arg);
};
