#include "incude/CHttpUrl.h"
#include "incude/CUrlParsingError.h"
#include <iostream>
#include <string>

void PrintUrlInfo(const CHttpUrl& url)
{
    std::cout << "URL: " << url.GetURL() << "\n"
              << "Protocol: " << (url.GetProtocol() == Protocol::HTTP ? "http" : "https") << "\n"
              << "Domain: " << url.GetDomain() << "\n"
              << "Port: " << url.GetPort() << "\n"
              << "Document: " << url.GetDocument() << "\n"
              << std::endl;
}

int main()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        try
        {
            CHttpUrl url(input);
            PrintUrlInfo(url);
        }
        catch (const CUrlParsingError& e)
        {
            std::cerr << "URL parsing error: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what()  << std::endl;
        }
    }

    return 0;
}