//g++ -std=c++17 \
//-I../include \
//-I/opt/homebrew/include \
//../mapBasics/map.cpp tests.cpp \
//-L/opt/homebrew/lib \
//-lgtest -lgtest_main -pthread \
//-o tests && ./tests

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "../mapBasics/map.h"

class DictionaryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем временный файл словаря
        std::ofstream file("dictionary.txt");
        file << "apple\tяблоко\n";
        file << "DOG\tсобака\n";
        file.close();
    }

    void TearDown() override {
        // Удаляем временный файл после тестов
        remove("dictionary.txt");
    }
};

TEST_F(DictionaryTest, ToLowerCaseConvertsToLowerCase) {
    EXPECT_EQ(ToLowerCase("Hello World"), "hello world");
    EXPECT_EQ(ToLowerCase("DOG"), "dog");
    EXPECT_EQ(ToLowerCase("123Test!"), "123test!");
    EXPECT_EQ(ToLowerCase(""), "");
}

TEST_F(DictionaryTest, LoadDictionaryLoadsCorrectly) {
    Dictionary dict;
    LoadDictionary(dict);
    
    EXPECT_EQ(dict.size(), 2);
    EXPECT_EQ(dict["apple"], "яблоко");
    EXPECT_EQ(dict["dog"], "собака"); // Проверка lower case
}

TEST_F(DictionaryTest, SaveDictionarySavesCorrectly) {
    Dictionary dict;
    dict["test"] = "тест";
    
    ASSERT_TRUE(SaveDictionary(dict));
    
    std::ifstream file("dictionary.txt");
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "test\tтест");
}

TEST_F(DictionaryTest, ProcessInputHandlesExistingWord) {
    Dictionary dict;
    LoadDictionary(dict);
    
    std::istringstream input("apple");
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());
    
    bool modified = ProcessInput("apple", dict);
    
    EXPECT_FALSE(modified);
    EXPECT_TRUE(output.str().find("яблоко") != std::string::npos);
    
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
}

TEST_F(DictionaryTest, ProcessInputHandlesNewWord) {
    Dictionary dict;
    LoadDictionary(dict);
    
    std::istringstream input("тест\n");
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());
    
    bool modified = ProcessInput("test", dict);
    
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
    
    EXPECT_TRUE(modified);
    EXPECT_EQ(dict["test"], "тест");
    EXPECT_TRUE(output.str().find("сохранено") != std::string::npos);
}

TEST_F(DictionaryTest, HandleExitSavesWhenNeeded) {
    Dictionary dict;
    std::istringstream input("y\n");
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());
    
    HandleExit(true, dict);
    
    EXPECT_TRUE(output.str().find("сохранены") != std::string::npos);
    
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
}

TEST(RunDictionaryTest, FullWorkflow) {
    Dictionary dict;
    std::istringstream input("CAT\nкот\n...\ny\n");
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    
    std::ostringstream output;
    std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());
    
    RunDictionaryLoop(dict);
    
    EXPECT_EQ(dict["cat"], "кот");
    EXPECT_TRUE(output.str().find("сохранено") != std::string::npos);
    EXPECT_TRUE(output.str().find("До свидания") != std::string::npos);
    
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
