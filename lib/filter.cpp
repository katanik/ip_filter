#include "filter.h"

IpFilter::IpFilter(const CheckFunction& func)
    : m_checkFunction(func)
{}

bool IpFilter::isOk(const IpData& ip) const
{
    return m_checkFunction == nullptr ? true : m_checkFunction(ip);
}
