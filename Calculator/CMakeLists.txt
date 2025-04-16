cmake_minimum_required(VERSION 3.30)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Calculator main.cpp
        include/Variable.h
        src/Variable.cpp
        include/IFunction.h
        src/IFunction.cpp
        include/BinaryFunction.h
        include/UnaryFunction.h
        include/Value.h
        src/BinaryFunction.cpp
        src/UnaryFunction.cpp
        include/Calculator.h
        src/Calculator.cpp
        include/IObserver.h
        src/Value.cpp
        include/CalculatorController.h
)
