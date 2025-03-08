#include "vector.h"
#include <iostream>

int main(int argc, const char * argv[])
{
    std::vector<double> numbers, result;
    
    
    if (!ReadNumbers(numbers, std::cin))
    {
        return EXIT_FAILURE;
    }
    
    if (numbers.size() == 0)
    {
        return EXIT_SUCCESS;
    }
    
    SubtractMedian(numbers);
    SortVector(result);
    PrintVector(result, std::cout);
    
    return EXIT_SUCCESS;
}

