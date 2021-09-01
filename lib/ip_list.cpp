#include <cstdlib>
#include <algorithm>

#include "ip_list.h"

void IpList::sort()
{
    std::sort(m_list.begin(), m_list.end());
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

void IpList::print(std::ostream& out, const IpFilter& filter)
{
    for(const auto& ip : m_list)
    {
        if (!filter.isOk(ip))
            continue;

        ip.printOut(out, '.');
        out << std::endl;
    }
}
