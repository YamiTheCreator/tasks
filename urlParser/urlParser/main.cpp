#include "url.h"
#include <iostream>

int main()
{
    std::string url;
    std::getline(std::cin, url);

    Protocol proto;
    int port;
    std::string host, doc;

    if (!ParseURL(url, proto, port, host, doc))
    {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    std::cout << url << "\nHOST: " << host << "\nPORT: " << port << "\nDOC: " << doc << std::endl;
    
    return 0;
}
