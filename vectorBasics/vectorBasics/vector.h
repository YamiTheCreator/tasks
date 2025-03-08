#pragma once

#include <vector>
#include <string>
bool ReadNumbers(std::vector<double>& numbers, std::istream& input);
void SubtractMedian(std::vector<double>& numbers);
void SortVector(std::vector<double>& numbers);
void PrintVector(const std::vector<double>& numbers, std::ostream& output);
