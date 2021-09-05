#pragma once

#include <iostream>
#include <string>
#include <vector>

using IpPart = short int;

class IpData
{
public:
    IpData() = default;
    ~IpData() = default;

    void add(const IpPart& ipPart);
    IpPart at(size_t index) const;

    void printOut(std::ostream& out, char delim) const;
    bool operator<(const IpData& ip) const;

private:
    std::vector<IpPart> m_data;
};

IpData split(const std::string& str, char delim);
