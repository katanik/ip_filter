#include <sstream>

#include "ip_data.h"

void IpData::add(const IpPart& ipPart)
{
    m_data.push_back(ipPart);
}

IpPart IpData::at(size_t index) const
{
    return  m_data[index];
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

bool IpData::operator<(const IpData& ip) const
{
    auto it1 = m_data.begin();
    auto it2 = ip.m_data.begin();
    for (; it1 != m_data.end() && it2 != ip.m_data.end(); ++it1, ++it2)
    {
        const auto& ipPart1 = *it1;
        const auto& ipPart2 = *it2;
        if (ipPart1 == ipPart2)
            continue;

        return ipPart1 > ipPart2;    
    }

    return m_data.size() < ip.m_data.size(); 
}

IpData split(const std::string& str, char delim)
{
    IpData result;
    std::stringstream ss;
    ss<<str;

    for(std::string ipPartStr; std::getline(ss, ipPartStr, delim);)
    {
        result.add(stoi(ipPartStr));
    }

    return result;
}
