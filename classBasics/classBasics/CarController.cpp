#include "CarController.h"
#include <sstream>

CarController::CarController(std::istream& input, std::ostream& output)
    : m_input(input),
    m_output(output),
    m_actionMap({
        { "Info", [this](std::istream& input) { Info(); } },
        { "EngineOn", [this](std::istream& input) { EngineOn(); } },
        { "EngineOff", [this](std::istream& input) { EngineOff(); } },
        { "SetGear", [this](std::istream& input) { return SetGear(input); } },
        { "SetSpeed", [this](std::istream& input) { return SetSpeed(input); } }
    }) {  }

void CarController::HandleInput(const std::string& line)
{
    std::istringstream str(line);
    std::string command;
    
    str >> command;
    auto it = m_actionMap.find(command);
    
    if (it == m_actionMap.end())
        throw std::runtime_error("Unknown command\n");
    
    it->second(str);
}

void CarController::Info() const
{
    m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << "\n"
             << "Direction: " << OutputDirection(m_car.GetDirection()) << "\n"
             << "Speed: " << m_car.GetSpeed() << "\n"
             << "Gear: " << static_cast<int>(m_car.GetGear()) << std::endl;
}

void CarController::EngineOn()
{
    return m_car.TurnOnEngine();
}

void CarController::EngineOff()
{
    return m_car.TurnOffEngine();
}

int ParseInt(const std::string& s)
{
    size_t pos = 0;
    int value = 0;
    
    try
    {
        value = std::stoi(s, &pos);
    }
    catch (...)
    {
        throw std::invalid_argument("Invalid command argument\n");
    }
    
    if (pos != s.size())
        throw std::invalid_argument("Invalid command argument\n");
    
    return value;
}

void CarController::SetGear(std::istream &input)
{
    std::string arg;
    input >> arg;
    
    try
    {
        int gear = ParseInt(arg);
        return m_car.SetGear(gear);
    }
    catch (const std::exception& e)
    {
        m_output << e.what();
    }
}

void CarController::SetSpeed(std::istream &input)
{
    std::string arg;
    input >> arg;
    
    try
    {
        int speed = ParseInt(arg);
        return m_car.SetSpeed(speed);
    }
    catch (const std::exception& e)
    {
        m_output << e.what();
    }
}

std::string CarController::OutputDirection(const Direction &direction) const
{
    switch (direction)
    {
    case Direction::backward:
        return "backward";
    case Direction::standing:
        return "standing still";
    case Direction::forward:
        return "forward";
//    default:
//        throw std::logic_error("Unknown direction");
    }
}
