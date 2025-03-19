#include "CarController.h"
#include <sstream>

//конструтор-инициализатор
CarController::CarController(std::ostream& output)
: m_output(output)
{
}

void CarController::ProcessCommand(const std::string& commandLine)
{
    std::istringstream iss(commandLine);
    std::string command;
    iss >> command;
    
    if (command == "Info")
    {
        PrintInfo();
    }
    else if (command == "EngineOn")
    {
        ProcessEngineOn();
    }
    else if (command == "EngineOff")
    {
        ProcessEngineOff();
    }
    else if (command == "SetGear")
    {
        std::string arg;
        iss >> arg;
        ProcessSetGear(arg);
    }
    else if (command == "SetSpeed")
    {
        std::string arg;
        iss >> arg;
        ProcessSetSpeed(arg);
    }
    else
    {
        m_output << "Unknown command" << std::endl;
    }
}

void CarController::PrintInfo() const
{
    m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl;
    m_output << "Direction: " << m_car.GetDirection() << std::endl;
    m_output << "Speed: " << m_car.GetSpeed() << std::endl;
    m_output << "Gear: " << m_car.GetGear() << std::endl;
}

void CarController::ProcessEngineOn()
{
    m_car.TurnOnEngine();
}

void CarController::ProcessEngineOff()
{
    if (!m_car.TurnOffEngine())
    {
        m_output << "Car must be stopped and in neutral gear" << std::endl;
    }
}

void CarController::ProcessSetGear(const std::string& arg)
{
    try
    {
        int gear = std::stoi(arg);
        
        if (gear < -1 || gear > 5)
        {
            m_output << "Invalid gear" << std::endl;
            return;
        }
        
        if (!m_car.IsTurnedOn() && gear != 0)
        {
            m_output << "Cannot set gear while engine is off" << std::endl;
            return;
        }
        
        if (gear == -1 && m_car.GetSpeed() != 0)
        {
            m_output << "Cannot reverse while moving" << std::endl;
            return;
        }
        
        if (!m_car.SetGear(gear))
        {
            m_output << "Unsuitable current speed" << std::endl;
        }
    }
    catch (const std::exception&)
    {
        m_output << "Invalid command argument" << std::endl;
    }
}

void CarController::ProcessSetSpeed(const std::string& arg)
{
    try
    {
        int speed = std::stoi(arg);
        
        if (speed < 0)
        {
            m_output << "Speed cannot be negative" << std::endl;
            return;
        }
        
        if (!m_car.IsTurnedOn())
        {
            m_output << "Cannot set speed while engine is off" << std::endl;
            return;
        }
        
        if (m_car.GetGear() == 0 && speed > m_car.GetSpeed())
        {
            m_output << "Cannot accelerate on neutral" << std::endl;
            return;
        }
        
        if (!m_car.SetSpeed(speed))
        {
            m_output << "Speed is out of gear range" << std::endl;
        }
    }
    catch (const std::exception&)
    {
        m_output << "Invalid command argument" << std::endl;
    }
}
