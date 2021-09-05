#include <cassert>
#include <iostream>
#include <fstream>
#include <ios>

#include "lib/ip_list.h"

void runFilters(std::ostream& out, IpList& ipList)
{
    // Print sorted ip list
    ipList.sort();
    ipList.print(out, IpFilter{});

    // Print if the first bite is 1
    IpFilter ipFilter1{ [](const IpData& ip) { return ip.at(0) == 1; }};
    ipList.print(out, ipFilter1);

    // Print if the first bite is 46, the second is 70
    IpFilter ipFilter2{ 
        [](const IpData& ip)
        {
            return ip.at(0) == 46 && ip.at(1) == 70;
        }};
    ipList.print(out, ipFilter2);

    // Print if any bite is 46
    IpFilter ipFilter3{ 
        [](const IpData& ip)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (ip.at(i) == 46)
                    return true;
            }
            return false;
        }};
    ipList.print(out, ipFilter3);
}

int main(int argc, char const *argv[])
{
    try
    {
        /*
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
        */

        // Read ip list
        IpList ipList{};
        ipList.inputData(std::cin);

        runFilters(std::cout, ipList);
    }
    catch(const std::range_error& e)
    {
        std::cerr << "Range error: " << e.what() << std::endl;
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << "Error in input/output: " << e.what() << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << "Something was wrong:" << e.what() << std::endl;
    }

    return 0;
}
