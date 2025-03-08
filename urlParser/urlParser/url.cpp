#include "url.h"
#include <iostream>
#include <string>
#include <regex>
#include <cctype>
#include <algorithm>

// ^                # Якорь начала строки
// ([a-zA-Z]+)      # Протокол (1+ букв)
// ://              # Разделитель протокола
// ([^/:?#]+)       # Хост (все символы кроме : / ? #)
// (?::(\d+))?      # Опциональный порт (после :)
// (/?.*)?          # Опциональный документ (после /)
// $                # Якорь конца строки

bool ParseProtocol(const std::string& str, Protocol& protocol)
{
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    
    if (lower == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (lower == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (lower == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else return false;
    
    return true;
}

bool ValidateHost(const std::string& host)
{
    return !host.empty();
}

bool ParsePort(const std::string& portStr, Protocol protocol, int& port)
{
    if (portStr.empty())
    {
        switch(protocol)
        {
            case Protocol::HTTP:
                port = 80;
                break;
            case Protocol::HTTPS:
                port = 443;
                break;
            case Protocol::FTP:
                port = 21;
                break;
            default:
                return false;
        }
        return true;
    }
    
    try
    {
        port = std::stoi(portStr);
        
        return (port > 0 && port <= 65535);
    }
    catch(...)
    {
        return false;
    }
}

std::string ProcessDocument(const std::string& docStr)
{
    if (!docStr.empty() && docStr[0] == '/')
    {
        return docStr.substr(1);
    }
    return docStr;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    std::regex pattern(R"(^([\w]+)://([^/:?#]+)(?::(\d+))?(/?.*)?$)", std::regex::icase);
    
    std::smatch matches;
    if (!std::regex_match(url, matches, pattern))
    {
        return false;
    }

    if (!ParseProtocol(matches[1].str(), protocol))
    {
        return false;
    }
    
    host = matches[2].str();
    
    if (!ValidateHost(host))
    {
        return false;
    }
    
    if (!ParsePort(matches[3].str(), protocol, port))
    {
        return false;
    }
    
    document = ProcessDocument(matches[4].str());

    return true;
}
