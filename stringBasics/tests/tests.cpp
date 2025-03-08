//g++ -std=c++17 \
//-I../include \
//-I/opt/homebrew/include \
//../stringBasics/string.cpp tests.cpp \
//-L/opt/homebrew/lib \
//-lgtest -lgtest_main -pthread \
//-o tests && ./tests

#include <gtest/gtest.h>
#include "../stringBasics/decoder.h"

TEST(HtmlDecodeTest, HandlesBasicEntities) {
    EXPECT_EQ(HtmlDecode("&quot;"), "\"");
    EXPECT_EQ(HtmlDecode("&apos;"), "'");
    EXPECT_EQ(HtmlDecode("&lt;"), "<");
    EXPECT_EQ(HtmlDecode("&gt;"), ">");
    EXPECT_EQ(HtmlDecode("&amp;"), "&");
}

TEST(HtmlDecodeTest, HandlesMultipleEntities) {
    EXPECT_EQ(HtmlDecode("&lt;&gt;&amp;&quot;&apos;"), "<>&\"'");
    EXPECT_EQ(HtmlDecode("&amp;amp;"), "&amp;");
    EXPECT_EQ(HtmlDecode("&amp;lt;"), "&lt;");
}

TEST(HtmlDecodeTest, HandlesMixedContent) {
    EXPECT_EQ(HtmlDecode("Hello&lt;World&gt;!"), "Hello<World>!");
    EXPECT_EQ(HtmlDecode("a&amp;b&amp;c"), "a&b&c");
    EXPECT_EQ(HtmlDecode("&quot;Test&apos;s&quot;"), "\"Test's\"");
}

TEST(HtmlDecodeTest, HandlesEdgeCases) {
    EXPECT_EQ(HtmlDecode(""), "");
    EXPECT_EQ(HtmlDecode("&"), "&");
    EXPECT_EQ(HtmlDecode("&&&&"), "&&&&");
}

TEST(HtmlDecodeTest, HandlesIncompleteEntities) {
    EXPECT_EQ(HtmlDecode("&amp"), "&amp");
    EXPECT_EQ(HtmlDecode("&quot"), "&quot");
    EXPECT_EQ(HtmlDecode("&lt"), "&lt");
    EXPECT_EQ(HtmlDecode("&gt"), "&gt");
    EXPECT_EQ(HtmlDecode("&apos"), "&apos");
}

TEST(HtmlDecodeTest, HandlesInvalidEntities) {
    EXPECT_EQ(HtmlDecode("&unknown;"), "&unknown;");
    EXPECT_EQ(HtmlDecode("&123;"), "&123;");
    EXPECT_EQ(HtmlDecode("&nbsp"), "&nbsp");
}

TEST(HtmlDecodeTest, HandlesNestedEntities) {
    EXPECT_EQ(HtmlDecode("&amp;amp;"), "&amp;");
    EXPECT_EQ(HtmlDecode("&amp;quot;"), "&quot;");
    EXPECT_EQ(HtmlDecode("&amp;amp;amp;"), "&amp;amp;");
}

TEST(HtmlDecodeTest, HandlesSpecialCases) {
    EXPECT_EQ(HtmlDecode("&&amp;;"), "&&;");
    EXPECT_EQ(HtmlDecode("&amp;&"), "&&");
    EXPECT_EQ(HtmlDecode("&amp;&quot;&"), "&\"&");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
