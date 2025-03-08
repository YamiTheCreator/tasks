#pragma once

#include <optional>
#include <set>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
std::optional<int> ParseArguments(int argc, char* argv[]);
