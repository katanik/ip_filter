#pragma once

#include <functional>

#include "ip_data.h"

using CheckFunction = std::function<bool(const IpData&)>;

class IpFilter
{
public:
    IpFilter() = default;
    ~IpFilter() = default;

    template<typename T>
    void addCheckFunctions(T func)
    {
        m_aCheckFunctions.push_back(func);
    }

    template<typename T, typename... Args>
    void addCheckFunctions(T func, Args... args)
    {
        addCheckFunctions(func);
        addCheckFunctions(args...);
    }

    template<>
    void addCheckFunctions(CheckFunction func);

    bool isOk(const IpData& ip) const;

private:
    std::vector<CheckFunction> m_aCheckFunctions;
};
