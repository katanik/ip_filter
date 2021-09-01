#include <cassert>
#include <iostream>
#include <fstream>

#include "lib/ip_list.h"

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

        // Read ip list
        IpList ipList{};
        ipList.inputData(inputFile);

        // Print sorted ip list
        ipList.sort();
        ipList.print(outputFile, IpFilter{});

        // Print if the first bite is 1
        IpFilter ipFilter1{ [](const IpData& ip) { return stoi(ip.at(0)) == 1; }};
        ipList.print(outputFile, ipFilter1);

        // Print if the first bite is 46, the second is 70
        IpFilter ipFilter2{ 
            [](const IpData& ip)
            {
                return stoi(ip.at(0)) == 46 && stoi(ip.at(1)) == 70;
            }};
        ipList.print(outputFile, ipFilter2);

        // Print if any bite is 46
        IpFilter ipFilter3{ 
            [](const IpData& ip)
            {
                for (int i = 0; i < 4; ++i)
                {
                    if (stoi(ip.at(i)) == 46)
                        return true;
                }
                return false;
            }};
        ipList.print(outputFile, ipFilter3);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
