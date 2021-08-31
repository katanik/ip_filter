#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "ip_filter.h"

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

        IpList ipList{};
        ipList.inputData(inputFile);
        ipList.sort();
        ipList.printResult(outputFile);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
