#include "vector.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

//istream ostream
bool ReadNumbers(std::vector<double>& numbers, std::istream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream stream(line);
        std::string token;
        
        while (stream >> token)
        {
            std::stringstream tokenStream(token);
            double number;
            //try catch
            if (!(tokenStream >> number) || !tokenStream.eof())
            {
                std::cerr << "ERROR" << std::endl;
                return false;
            }
            
            numbers.push_back(number);
        }
    }
    return true;
};

double FindMedian(std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return 0.0;
    }
        
    const size_t VECTOR_SIZE = numbers.size();
    double median;
    
    if ((VECTOR_SIZE % 2) == 1)
    {
        std::nth_element(numbers.begin(), numbers.begin() + VECTOR_SIZE / 2, numbers.end());
        median = numbers[VECTOR_SIZE / 2];
    }
    else
    {
        std::nth_element(numbers.begin(), numbers.begin() + VECTOR_SIZE / 2 - 1, numbers.end());
        double left = numbers[VECTOR_SIZE / 2 - 1];
        
        std::nth_element(numbers.begin(), numbers.begin() + VECTOR_SIZE / 2, numbers.end());
        double right = numbers[VECTOR_SIZE / 2];
        
        median = (left + right) / 2.0;
    }
    
    return median;
}

void SubtractMedian(std::vector<double>& numbers)
{
    if (numbers.empty()) return;
        
    double median = FindMedian(numbers);
    
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [median](double n){ return n - median; });
};

void SortVector(std::vector<double>& numbers)
{
    std::sort(numbers.begin(), numbers.end());
}

void PrintVector(const std::vector<double>& numbers, std::ostream& output)
{
    if (numbers.empty())
    {
        return;
    }
    std::vector<double> sorted = numbers;
    SortVector(sorted);

    for (const double& num : sorted)
    {
        output << std::fixed << std::setprecision(3) << num << " ";
    }
    
    std::cout << std::endl;
}
