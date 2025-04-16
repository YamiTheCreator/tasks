#pragma once
#include <map>
#include "BinaryFunction.h"
#include "IFunction.h"
#include "UnaryFunction.h"
#include "Variable.h"

class Calculator final
{
public:
    Calculator() = default;
    ~Calculator() = default;

    void addVariable(const std::string& name, double value = 0.0);
    void addBinaryFunction(const std::string& name, const std::string& arg1, const std::string& arg2, BinaryFunctionType op);
    void addUnaryFunction(const std::string& name, const std::string& arg, UnaryFunctionType op);
    void setVariableValue(const std::string& name, double value);
    [[nodiscard]] double getFunctionValue(const std::string& name);
    [[nodiscard]] double getVariableValue(const std:: string& name);
    [[nodiscard]] std::vector<std::string> getVariablesIdentifiers();
    [[nodiscard]] std::vector<std::string> getFunctionsIdentifiers();

private:
    std::map<std::string, std::shared_ptr<Variable>> m_variables;
    std::map<std::string, std::shared_ptr<IFunction>> m_functions;

    std::shared_ptr<Value> getValuePtr(const std::string& name);
};