#pragma once

#include <iostream>
#include <string>
#include <vector>

class IpData
{
public:
    IpData() = default;
    ~IpData() = default;

    void add(const std::string& ipPart);
    std::string at(size_t index) const;

    void printOut(std::ostream& out, char delim) const;
    bool operator<(const IpData& ip) const;

private:
    std::vector<std::string> m_data;
};

IpData split(const std::string& str, char delim);
