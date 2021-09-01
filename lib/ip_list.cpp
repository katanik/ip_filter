#include <cstdlib>
#include <algorithm>
#include <sstream>

#include "ip_list.h"

void IpData::add(const std::string& ipPart)
{
    m_data.push_back(ipPart);
}

std::string IpData::at(size_t index) const
{
    return index < m_data.size() ? m_data[index] : "";
}

void IpData::printOut(std::ostream& out, char delim) const
{
    if (m_data.empty())
        return;

    for (size_t idx = 0; idx + 1 < m_data.size(); ++idx)
    {
        out << m_data[idx] << delim;            
    }

    out << m_data.back();
}

bool IpData::operator<(const IpData& ip)    
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
    m_list.clear();
    for(std::string line; std::getline(in, line);)
    {
        auto ip = split(line, '\t');
        m_list.push_back(split(ip.at(0), '.'));
    }
}

void IpList::print(std::ostream& out)
{
    for(const auto& ip : m_list)
    {
        ip.printOut(out, '.');
        out << std::endl;
    }
}
