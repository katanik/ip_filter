#include "filter.h"

bool IpFilter::isOk(const IpData& ip) const
{
    for (auto checkFunction : m_aCheckFunctions)
    {
        if (!checkFunction(ip))
            return false;
    }

    return true;
}
