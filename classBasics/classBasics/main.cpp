#include "CarController.h"
#include <iostream>
#include <string>

int main()
{
    CarController controller;
    std::string commandLine;
    
    while (std::getline(std::cin, commandLine))
    {
        if (commandLine == "Exit")
        {
            break;
        }
        
        controller.ProcessCommand(commandLine);
    }
    
    return 0;
}
