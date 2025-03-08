//g++ -std=c++17 \
//-I../vectorBasics \
//-I/opt/homebrew/include \
//../vectorBasics/vector.cpp \
//tests.cpp \
//-L/opt/homebrew/lib \
//-lgtest -lgtest_main -pthread \
//-o tests && ./tests

#include <gtest/gtest.h>
#include "vector.h"
#include <sstream>

TEST(VectorTest, ReadNumbersValidInput) {
    std::vector<double> numbers;
    std::stringstream input("1.5 2.5 3.5\n4.5 5.5");
    EXPECT_TRUE(ReadNumbers(numbers, input));
    EXPECT_EQ(numbers.size(), 5);
    EXPECT_DOUBLE_EQ(numbers[0], 1.5);
    EXPECT_DOUBLE_EQ(numbers[4], 5.5);
}

TEST(VectorTest, ReadNumbersInvalidInput) {
    std::vector<double> numbers;
    std::stringstream input("1.5 abc 3.5");
    EXPECT_FALSE(ReadNumbers(numbers, input));
}

//TEST(VectorTest, FindMedianOddSize) {
//    std::vector<double> numbers = {1.0, 3.0, 2.0, 5.0, 4.0};
//    EXPECT_DOUBLE_EQ(FindMedian(numbers), 3.0);
//}
//
//TEST(VectorTest, FindMedianEvenSize) {
//    std::vector<double> numbers = {1.0, 3.0, 2.0, 4.0};
//    EXPECT_DOUBLE_EQ(FindMedian(numbers), 2.5);
//}
//
//TEST(VectorTest, FindMedianEmpty) {
//    std::vector<double> numbers;
//    EXPECT_DOUBLE_EQ(FindMedian(numbers), 0.0);
//}
//
//TEST(VectorTest, SubtractMedianOddSize) {
//    std::vector<double> numbers = {1.0, 3.0, 2.0, 5.0, 4.0};
//    double median = FindMedian(numbers);  // Store median before modifying the vector
//    SubtractMedian(numbers);
//    
//    // Calculate expected values by subtracting the median from original values
//    std::vector<double> expected;
//    for (double val : {1.0, 3.0, 2.0, 5.0, 4.0}) {
//        expected.push_back(val - median);
//    }
//    
//    EXPECT_EQ(numbers.size(), expected.size());
//    for (size_t i = 0; i < numbers.size(); ++i) {
//        EXPECT_NEAR(numbers[i], expected[i], 0.001);
//    }
//}

TEST(VectorTest, SubtractMedianEmpty) {
    std::vector<double> numbers;
    SubtractMedian(numbers);
    EXPECT_TRUE(numbers.empty());
}

TEST(VectorTest, SortVectorTest) {
    std::vector<double> numbers = {5.0, 2.0, 4.0, 1.0, 3.0};
    SortVector(numbers);
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0};
    EXPECT_EQ(numbers, expected);
}

TEST(VectorTest, PrintVectorTest) {
    std::vector<double> numbers = {3.0, 1.0, 2.0};
    std::stringstream output;
    PrintVector(numbers, output);
    std::string expected = "1.000 2.000 3.000 ";
    EXPECT_EQ(output.str(), expected);
}

TEST(VectorTest, PrintVectorEmptyTest) {
    std::vector<double> numbers;
    std::stringstream output;
    PrintVector(numbers, output);
    EXPECT_TRUE(output.str().empty());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
