#pragma once

#include <iostream>
#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class IpList
{
public:
    void inputData(std::istream& in); 
    void printResult(std::ostream& out);
    void sort();

private:
    std::vector<StringVector> m_list;
};
