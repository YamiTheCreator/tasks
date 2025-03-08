#pragma once

#include <string>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP,
    UNKNOWN
};

bool ParseProtocol(const std::string& str, Protocol& protocol);
bool ValidateHost(const std::string& host);
bool ParsePort(const std::string& portStr, Protocol protocol, int& port);
std::string ProcessDocument(const std::string& docStr);
bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);
