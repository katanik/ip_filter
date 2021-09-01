#pragma once

#include <functional>

#include "ip_data.h"

using CheckFunction = std::function<bool(const IpData&)>;

class IpFilter
{
public:
    IpFilter() = default;
    IpFilter(const CheckFunction& func);

    ~IpFilter() = default;
    
    bool isOk(const IpData& ip) const;

private:
    CheckFunction m_checkFunction = nullptr;
};
