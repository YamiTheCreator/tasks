//g++ -std=c++17 \
//-I../include \
//-I/opt/homebrew/include \
//../setBasics/set.cpp tests.cpp \
//-L/opt/homebrew/lib \
//-lgtest -lgtest_main -pthread \
//-o tests && ./tests

#include "../setBasics/set.h"
#include <gtest/gtest.h>
#include <set>
#include <optional>

TEST(GeneratePrimeNumbersSetTest, HandlesSmallNumbers) {
    EXPECT_EQ(GeneratePrimeNumbersSet(0), (std::set<int>{}));
    EXPECT_EQ(GeneratePrimeNumbersSet(1), (std::set<int>{}));
    EXPECT_EQ(GeneratePrimeNumbersSet(2), (std::set<int>{2}));
}

TEST(GeneratePrimeNumbersSetTest, HandlesEvenNumbers) {
    EXPECT_EQ(GeneratePrimeNumbersSet(10), (std::set<int>{2, 3, 5, 7}));
    EXPECT_EQ(GeneratePrimeNumbersSet(20), (std::set<int>{2, 3, 5, 7, 11, 13, 17, 19}));
}

TEST(GeneratePrimeNumbersSetTest, HandlesOddNumbers) {
    EXPECT_EQ(GeneratePrimeNumbersSet(11), (std::set<int>{2, 3, 5, 7, 11}));
    EXPECT_EQ(GeneratePrimeNumbersSet(21), (std::set<int>{2, 3, 5, 7, 11, 13, 17, 19}));
}

TEST(GeneratePrimeNumbersSetTest, HandlesLargeValues) {
    auto primes = GeneratePrimeNumbersSet(100);
    EXPECT_EQ(primes.size(), 25);
    EXPECT_TRUE(primes.count(97));
    EXPECT_FALSE(primes.count(1));
    EXPECT_FALSE(primes.count(99));
}

TEST(ParseArgumentsTest, ValidInput) {
    char* argv[] = {(char*)"./program", (char*)"100"};
    auto result = ParseArguments(2, argv);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 100);
}

TEST(ParseArgumentsTest, InvalidInput) {
    char* argv[] = {(char*)"./program"};
    EXPECT_FALSE(ParseArguments(1, argv).has_value());

    // Некорректный тип аргумента
    char* argv2[] = {(char*)"./program", (char*)"abc"};
    EXPECT_FALSE(ParseArguments(2, argv2).has_value());

    // Число вне диапазона
    char* argv3[] = {(char*)"./program", (char*)"-5"};
    EXPECT_FALSE(ParseArguments(2, argv3).has_value());

    // Слишком большое число
    char* argv4[] = {(char*)"./program", (char*)"100000001"};
    EXPECT_FALSE(ParseArguments(2, argv4).has_value());
}

TEST(ParseArgumentsTest, EdgeCases) {
    char* argv[] = {(char*)"./program", (char*)"0"};
    EXPECT_TRUE(ParseArguments(2, argv).has_value());

    char* argv2[] = {(char*)"./program", (char*)"100000000"};
    EXPECT_TRUE(ParseArguments(2, argv2).has_value());
}

TEST(IntegrationTest, FullPipeline) {
    char* argv[] = {(char*)"./program", (char*)"30"};
    auto upperBound = ParseArguments(2, argv);
    ASSERT_TRUE(upperBound.has_value());
    
    auto primes = GeneratePrimeNumbersSet(upperBound.value());
    std::set<int> expected{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    EXPECT_EQ(primes, expected);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
