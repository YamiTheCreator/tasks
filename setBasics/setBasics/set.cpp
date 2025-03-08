#include "set.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

//зоны ответственности, константы


std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primes;
    if (upperBound < 2)
    {
        return primes;
    }

    std::vector<bool> sieve(upperBound + 1, true);
//    sieve[0] = sieve[1] = false;

    for (int j = 4; j <= upperBound; j += 2)
    {
        sieve[j] = false;
    }
    for (int i = 3; i * i <= upperBound; i += 2)
    {
        if (sieve[i])
        {
            for (int j = i * i; j <= upperBound; j += 2 * i)
            {
                sieve[j] = false;
            }
        }
    }

    primes.insert(2);
    for (int i = 3; i <= upperBound; i += 2)
    {
        if (sieve[i])
        {
            primes.insert(i);
        }
    }

    return primes;
}

std::optional<int> ParseArguments(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " upperBound" << std::endl;
        return std::nullopt;
    }

    int upperBound;
    try
    {
        upperBound = std::stoi(argv[1]);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid argument: " << argv[1] << std::endl;
        return std::nullopt;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Argument out of range: " << argv[1] << std::endl;
        return std::nullopt;
    }

    if (upperBound < 0 || upperBound > 100000000)
    {
        std::cerr << "Upper bound must be between 0 and 100000000" << std::endl;
        return std::nullopt;
    }

    return upperBound;
}
