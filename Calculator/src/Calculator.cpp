#include "../include/Calculator.h"

void Calculator::addVariable(const std::string& name, double value)
{
    m_variables[name] = std::make_shared<Variable>(value);
}

void Calculator::addBinaryFunction(const std::string& name, const std::string& arg1, const std::string& arg2, BinaryFunctionType op)
{
    if (m_variables.contains(name) || m_functions.contains(name))
    {
        throw std::invalid_argument("Variable \"" + name + "\" already exists");
    }

    const auto left = getValuePtr(arg1);
    const auto right = getValuePtr(arg2);

    m_functions[name] = BinaryFunction::create(op, left, right);
}

void Calculator::addUnaryFunction(const std::string& name, const std::string& arg, UnaryFunctionType op)
{
    if (m_variables.contains(name) || m_functions.contains(name))
    {
        throw std::invalid_argument("Variable \"" + name + "\" already exists");
    }

    const auto right = getValuePtr(arg);

    m_functions[name] = UnaryFunction::create(op, right);
}

void Calculator::setVariableValue(const std::string& name, const double value)
{
    const auto it = m_variables.find(name);
    if (it == m_variables.end())
    {
        throw std::invalid_argument("Variable not found");
    }

    return it -> second -> setValue(value);
}

[[nodiscard]] double Calculator::getFunctionValue(const std::string& name)
{
    const auto it = m_functions.find(name);
    if (it == m_functions.end())
    {
        throw std::runtime_error("Function \"" + name + "\" already exists");
    }

    return it -> second -> getValue();
}

[[nodiscard]] double Calculator::getVariableValue(const std:: string& name)
{
    const auto it = m_variables.find(name);
    if (it == m_variables.end())
    {
        throw std::runtime_error("Variable \"" + name + "\" already exists");
    }

    return it -> second -> getValue();
}

[[nodiscard]] std::vector<std::string> Calculator::getVariablesIdentifiers()
{
    std::vector<std::string> identifiers;
    identifiers.reserve(Calculator::m_variables.size());

    for (const auto& [key, _] : Calculator::m_variables)
    {
        identifiers.push_back(key);
    }

    return identifiers;
}

[[nodiscard]] std::vector<std::string> Calculator::getFunctionsIdentifiers()
{
    std::vector<std::string> identifiers;
    identifiers.reserve(Calculator::m_functions.size());

    for (const auto& [key, _] : Calculator::m_functions)
    {
        identifiers.push_back(key);
    }


    return identifiers;
}

std::shared_ptr<Value> Calculator::getValuePtr(const std::string& name)
{
    if (const auto var_it = m_variables.find(name); var_it != m_variables.end())
    {
        return var_it->second;
    }

    if (const auto func_it = m_functions.find(name); func_it != m_functions.end())
    {
        return func_it->second;
    }

    throw std::invalid_argument("Identifier not found: " + name);
}