#include "set.h"
#include <iostream>

int main(int argc, char* argv[])
{
    auto upperBound = ParseArguments(argc, argv);
    
    if (!upperBound)
    {
        return 1;
    }

    std::set<int> primes = GeneratePrimeNumbersSet(*upperBound);
    
    std::cout << primes.size() << std::endl;
    return 0;
}
