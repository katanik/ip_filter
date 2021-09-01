#pragma once

#include <iostream>
#include <string>
#include <vector>

class IpData
{
public:
    void add(const std::string& ipPart);
    std::string at(size_t index) const;

    void printOut(std::ostream& out, char delim) const;
    bool operator<(const IpData& ip);

private:
    std::vector<std::string> m_data;
};

class IpList
{
public:
    void inputData(std::istream& in);
    void print(std::ostream& out);
    void sort();

private:
    std::vector<IpData> m_list;
};
