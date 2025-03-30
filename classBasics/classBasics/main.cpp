#include "CarController.h"

int main()
{
    CarController controller(std::cin, std::cout);
    std::string line;
    
    while(std::getline(std::cin, line))
    {
        try
        {
            controller.HandleInput(line);
        }
        catch(std::exception& e)
        {
            std::cout << e.what();
        }
    }
    
    return EXIT_SUCCESS;
}
