#include "../incude/CHttpUrl.h"

#include <regex>

#include "../incude/CUrlParsingError.h"

namespace Constants
{
    const std::string PREFIX = "://";
    const std::string HTTP_PROTOCOL = "http";
    const std::string HTTPS_PROTOCOL = "https";
    constexpr unsigned short HTTP_DEFAULT_PORT = 80;
    constexpr unsigned short HTTPS_DEFAULT_PORT = 443;
    constexpr unsigned short MIN_PORT = 1;
    constexpr unsigned short MAX_PORT = 65535;
    const std::regex PATTERN(R"(^([\w]+)://([^/:?#]+)(?::(\d+))?(/?.*)?$)", std::regex::icase);
    static const std::map<std::string, Protocol> PROTOCOL_MAP =
    {
        {HTTP_PROTOCOL, Protocol::HTTP},
        {HTTPS_PROTOCOL, Protocol::HTTPS}
    };
}

CHttpUrl::CHttpUrl(const std::string& url)
{
    ParseURL(url);
}

CHttpUrl::CHttpUrl(
    const std::string& domain,
    const std::string& document,
    const Protocol protocol) : CHttpUrl(domain, document, protocol, GetDefaultPort(protocol)) {}

CHttpUrl::CHttpUrl(
    const std::string& domain,
    const std::string& document,
    const Protocol protocol,
    const unsigned short port) : m_protocol(protocol), m_port(port)
{
    ValidateDomain(domain);
    ValidatePort(port);

    m_domain = domain;
    m_document = (document.empty() || document[0] != '/')? '/' + document : document;
}

std::string CHttpUrl::GetURL() const
{
    std::string url = ProtocolToString(m_protocol) + Constants::PREFIX + m_domain;

    if (m_port != GetDefaultPort(m_protocol))
    {
        url += ':' + std::to_string(m_port);
    }

    url += m_document;

    return url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

void CHttpUrl::ParseURL(const std::string& url)
{
    std::smatch matches;
    if (!std::regex_match(url, matches, Constants::PATTERN))
    {
        throw CUrlParsingError("Invalid URL format");
    }

    m_protocol = ParseProtocol(matches[1].str());
    m_domain = matches[2].str();

    if (matches[3].matched)
    {
        m_port = ParsePort(matches[3].str(), m_protocol);
    }
    else
    {
        m_port = GetDefaultPort(m_protocol);
    }

    m_document = matches[4].matched? matches[4].str() : "/";
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocolStr)
{
    const std::string protocol = ToLower(protocolStr);
    const auto it = Constants::PROTOCOL_MAP.find(protocol);
    if (it == Constants::PROTOCOL_MAP.end())
    {
        throw CUrlParsingError("Invalid protocol: " + protocolStr);
    }

    return it->second;
}

unsigned short CHttpUrl::ParsePort(const std::string &portStr, const Protocol protocol)
{
    if (portStr.empty())
    {
        return GetDefaultPort(protocol);
    }

    try
    {
        const int port = std::stoi(portStr);
        ValidatePort(port);
        return static_cast<unsigned short>(port);
    }
    catch (const std::exception&)
    {
        throw CUrlParsingError("Invalid port: " + portStr);
    }
}

std::string CHttpUrl::ProtocolToString(Protocol protocol)
{
    switch (protocol)
    {
        case Protocol::HTTP:
            return Constants::HTTP_PROTOCOL;
        case Protocol::HTTPS:
            return Constants::HTTPS_PROTOCOL;
        default:
            throw std::invalid_argument("Invalid protocol");
    }
}

unsigned short CHttpUrl::GetDefaultPort(const Protocol protocol)
{
    switch (protocol)
    {
        case Protocol::HTTP:
            return Constants::HTTP_DEFAULT_PORT;
        case Protocol::HTTPS:
            return Constants::HTTPS_DEFAULT_PORT;
        default:
            throw std::invalid_argument("Invalid protocol");
    }
}

std::string CHttpUrl::ToLower(const std::string& str)
{
    std::string result = str;
    std::ranges::transform(result, result.begin(), [](const unsigned char c) { return std::tolower(c); });
    return result;
}

void CHttpUrl::ValidatePort(unsigned short port)
{
    if (port < Constants::MIN_PORT || port > Constants::MAX_PORT)
    {
        throw CUrlParsingError("Port is out of range");
    }
}

void CHttpUrl::ValidateDomain(const std::string& domain)
{
    if (domain.empty())
    {
        throw CUrlParsingError("Domain cannot be empty");
    }

    for (const char c : domain)
    {
        if (!isalnum(c) && c != '.' && c != '-')
        {
            throw CUrlParsingError(std::string("Invalid character in domain: ") + c);
        }
    }
}