#pragma once
#include <map>
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    explicit CHttpUrl(std::string const& url);

    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    [[nodiscard]] std::string GetURL()const;

    [[nodiscard]] std::string GetDomain()const;

    [[nodiscard]] std::string GetDocument()const;

    [[nodiscard]] Protocol GetProtocol()const;

    [[nodiscard]] unsigned short GetPort()const;


private:
    void ParseURL(const std::string& url);
    static Protocol ParseProtocol(const std::string& protocolStr);
    static unsigned short ParsePort(const std::string& portStr, Protocol protocol);
    static std::string ProtocolToString(Protocol protocol);
    static unsigned short GetDefaultPort(Protocol protocol);
    static std::string ToLower(const std::string& str);
    static void ValidateDomain(const std::string& domain);
    static void ValidatePort(unsigned short port);

    std::string m_domain, m_document;
    Protocol m_protocol = Protocol::HTTP;
    unsigned short m_port = static_cast<unsigned short>(-1);
};
