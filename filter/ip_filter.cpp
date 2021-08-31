#include <cstdlib>
#include <algorithm>
#include <vector>

#include "ip_filter.h"

struct IpData
{
    void add(const std::string& ipPart)
    {
        m_data.push_back(ipPart);
    }

    void printOut(std::ostream& out, char delim) const
    {
        if (m_data.empty())
            return;

        for (size_t idx = 0; idx + 1 < m_data.size(); ++idx)
        {
            out << m_data[idx] << delim;            
        }

        out << m_data.back();
    }

    bool operator<(const IpData& ip)    
    {
        auto it1 = m_data.begin();
        auto it2 = ip.m_data.begin();
        for (; it1 != m_data.end() && it2 != ip.m_data.end(); ++it1, ++it2)
        {
            auto ipPart1 = stoi(*it1);
            auto ipPart2 = stoi(*it2);
            if (ipPart1 == ipPart2)
                continue;

            return ipPart1 > ipPart2;    
        }

        return m_data.size() < ip.m_data.size(); 
    }

    std::vector<std::string> m_data;
};

void IpList::printResult(std::ostream& out)
{
    for(const auto& ip : m_list)
    {
        ip.printOut(out, '.');
        out << std::endl;
    }
}

void IpList::sort()
{
    std::sort(m_list.begin(), m_list.end());
}

static IpData split(const std::string& str, char delim)
{
    IpData result;
    std::stringstream ss;
    ss<<str;

    for(std::string ipPart; std::getline(ss, ipPart, delim);)
    {
        result.add(ipPart);
    }

    return result;
}

void IpList::inputData(std::istream& in)
{
    std::vector<StringVector> ipPool;
    for(std::string line; std::getline(in, line);)
    {
        std::vector<std::string> ip = split(line, '\t');
        ipPool.push_back(split(ip.at(0), '.'));
    }
    return ipPool;
}

void IpList::printResult(std::ostream& out)
{
    for(const auto& ip : ipPool)
    {
        printOut(std::move(ip), '.', out);
        out << std::endl;
    }
}
