#pragma once

#include "ip_data.h"
#include "filter.h"

class IpList
{
public:
    void inputData(std::istream& in);
    void print(std::ostream& out, const IpFilter& filter);
    void sort();

private:
    std::vector<IpData> m_list;
};
