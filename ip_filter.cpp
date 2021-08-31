#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using StringVector = std::vector<std::string>;

StringVector split(const std::string& str, char delim)
{
    StringVector result;
    std::stringstream ss;
    ss<<str;

    for(std::string ipPart; std::getline(ss, ipPart, delim);)
    {
        result.push_back(ipPart);
    }

    return result;
}

void sortIpPool(std::vector<StringVector>& ipPool)
{
    auto filter = [](const auto& ip1, const auto& ip2)
    {
        auto it1 = ip1.begin(), it2 = ip2.begin();
        for (; it1 != ip1.end() && it2 != ip2.end(); ++it1, ++it2)
        {
            auto ipPart1 = stoi(*it1);
            auto ipPart2 = stoi(*it2);
            if (ipPart1 == ipPart2)
                continue;

            return ipPart1 > ipPart2;    
        }

        return ip1.size() < ip2.size(); 
    };

    std::sort(ipPool.begin(), ipPool.end(), filter);
}

std::vector<StringVector> inputData(std::istream& in)
{
    std::vector<StringVector> ipPool;
    for(std::string line; std::getline(in, line);)
    {
        std::vector<std::string> pureIp = split(line, '\t');
        ipPool.push_back(split(pureIp.at(0), '.'));
    }
    return ipPool;
}

void printOut(StringVector ip, char delim, std::ostream& out)
{
    if (ip.empty())
        return;

    auto lastIpPart = ip.back();
    ip.pop_back();

    for(auto ipPart : ip)
    {
        out << ipPart << delim;
    }

    out << lastIpPart;
}

void printResult(const std::vector<StringVector>& ipPool, std::ostream& out)
{
    for(const auto& ip : ipPool)
    {
        printOut(std::move(ip), '.', out);
        out << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::fstream inputFile("ip_filter.tsv");
        if (!inputFile.is_open())
        {
            std::cout << "failed to open " << '\n';
            return 1;
        }

        std::ofstream outputFile;
        outputFile.open("result.txt", std::fstream::out);
        if (!outputFile.is_open())
        {
            std::cout << "failed to create file " << '\n';
            return 1;
        }

        auto ipPool = inputData(inputFile);
        sortIpPool(ipPool);
        printResult(ipPool, outputFile);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
