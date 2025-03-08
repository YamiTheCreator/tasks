//g++ -std=c++17 \
//-I../vectorBasics \
//-I/opt/homebrew/include \
//../urlParser/url.cpp \
//tests.cpp \
//-L/opt/homebrew/lib \
//-lgtest -lgtest_main -pthread \
//-o tests && ./tests

#include <gtest/gtest.h>
#include "../urlParser/url.h"

TEST(UrlParserTest, ParseProtocolValid) {
    Protocol proto;
    
    EXPECT_TRUE(ParseProtocol("http", proto));
    EXPECT_EQ(proto, Protocol::HTTP);
    
    EXPECT_TRUE(ParseProtocol("HTTP", proto));
    EXPECT_EQ(proto, Protocol::HTTP);
    
    EXPECT_TRUE(ParseProtocol("HttPs", proto));
    EXPECT_EQ(proto, Protocol::HTTPS);
    
    EXPECT_TRUE(ParseProtocol("ftp", proto));
    EXPECT_EQ(proto, Protocol::FTP);
}

TEST(UrlParserTest, ParseProtocolInvalid) {
    Protocol proto;
    
    EXPECT_FALSE(ParseProtocol("htt", proto));
    EXPECT_FALSE(ParseProtocol("httpss", proto));
    EXPECT_FALSE(ParseProtocol("", proto));
    EXPECT_FALSE(ParseProtocol("123", proto));
}

TEST(UrlParserTest, ValidateHost) {
    EXPECT_TRUE(ValidateHost("example.com"));
    EXPECT_TRUE(ValidateHost("localhost"));
    EXPECT_FALSE(ValidateHost(""));
}

TEST(UrlParserTest, ParsePortDefault) {
    int port;
    
    EXPECT_TRUE(ParsePort("", Protocol::HTTP, port));
    EXPECT_EQ(port, 80);
    
    EXPECT_TRUE(ParsePort("", Protocol::HTTPS, port));
    EXPECT_EQ(port, 443);
    
    EXPECT_TRUE(ParsePort("", Protocol::FTP, port));
    EXPECT_EQ(port, 21);
}

TEST(UrlParserTest, ParsePortCustom) {
    int port;
    
    EXPECT_TRUE(ParsePort("8080", Protocol::HTTP, port));
    EXPECT_EQ(port, 8080);
    
    EXPECT_FALSE(ParsePort("0", Protocol::HTTP, port));
    EXPECT_FALSE(ParsePort("70000", Protocol::HTTP, port));
    EXPECT_FALSE(ParsePort("abc", Protocol::HTTP, port));
}

TEST(UrlParserTest, ProcessDocument) {
    EXPECT_EQ(ProcessDocument("/path"), "path");
    EXPECT_EQ(ProcessDocument("path"), "path");
    EXPECT_EQ(ProcessDocument(""), "");
}

TEST(UrlParserTest, FullUrlParsing) {
    struct TestCase {
        std::string url;
        bool expectedResult;
        Protocol protocol;
        int port;
        std::string host;
        std::string document;
    };

    const TestCase testCases[] = {
        {"http://example.com", true, Protocol::HTTP, 80, "example.com", ""},
        {"https://example.org:8080/path", true, Protocol::HTTPS, 8080, "example.org", "path"},
        {"ftp://localhost:21/files", true, Protocol::FTP, 21, "localhost", "files"},
        {"http://", false, Protocol::UNKNOWN, 0, "", ""},
        {"invalid://host:port", false, Protocol::UNKNOWN, 0, "", ""}
    };

}

TEST(UrlParserTest, IntegrationTests) {
    struct TestCase {
        std::string input;
        bool isValid;
        Protocol expectedProtocol;
        int expectedPort;
        std::string expectedHost;
        std::string expectedDoc;
    };

    const TestCase testCases[] = {
        {
            "http://example.com",
            true,
            Protocol::HTTP,
            80,
            "example.com",
            ""
        },
        
        {
            "htTp://example.com:8080/index.html",
            true,
            Protocol::HTTP,
            8080,
            "example.com",
            "index.html"
        },
        
        {
            "htp://example.com",
            false,
            Protocol::UNKNOWN,
            0,
            "",
            ""
        },
        
        {
            "http://www.mysite.com/docs/document1.html?page=30&lang=en#title",
            true,
            Protocol::HTTP,
            80,
            "www.mysite.com",
            "docs/document1.html?page=30&lang=en#title"
        },
        
        {
            "https://secure.site.com:443/admin",
            true,
            Protocol::HTTPS,
            443,
            "secure.site.com",
            "admin"
        },
        
        {
            "ftp://files.com:21/archive.zip",
            true,
            Protocol::FTP,
            21,
            "files.com",
            "archive.zip"
        },
        
        {
            "http://:8080/path",
            false,
            Protocol::UNKNOWN,
            0,
            "",
            ""
        }
    };

    for (const auto& tc : testCases) {
        Protocol proto;
        int port;
        std::string host, doc;
        
        bool result = ParseURL(tc.input, proto, port, host, doc);
        
        EXPECT_EQ(result, tc.isValid) << "Failed for input: " << tc.input;
        
        if (tc.isValid) {
            EXPECT_EQ(proto, tc.expectedProtocol) << "Protocol mismatch for: " << tc.input;
            EXPECT_EQ(port, tc.expectedPort) << "Port mismatch for: " << tc.input;
            EXPECT_EQ(host, tc.expectedHost) << "Host mismatch for: " << tc.input;
            EXPECT_EQ(doc, tc.expectedDoc) << "Document mismatch for: " << tc.input;
        }
    }
}

TEST(UrlParserTest, OutputFormatValidation) {
    const std::string test_url = "http://test.com:8080/path/to/doc";
    
    Protocol proto;
    int port;
    std::string host, doc;
    
    ASSERT_TRUE(ParseURL(test_url, proto, port, host, doc));
    
    std::stringstream ss;
    ss << test_url << "\n"
       << "HOST: " << host << "\n"
       << "PORT: " << port << "\n"
       << "DOC: " << doc;
    
    const std::string expected_output =
        "http://test.com:8080/path/to/doc\n"
        "HOST: test.com\n"
        "PORT: 8080\n"
        "DOC: path/to/doc";
    
    EXPECT_EQ(ss.str(), expected_output);
}

TEST(UrlParserTest, ErrorHandling) {
    const std::string invalid_url = "invalid://url";
    
    Protocol proto;
    int port;
    std::string host, doc;
    
    ASSERT_FALSE(ParseURL(invalid_url, proto, port, host, doc));
    
    std::stringstream ss;
    ss << "ERROR";
    
    EXPECT_EQ(ss.str(), "ERROR");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
