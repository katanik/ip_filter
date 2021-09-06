#include <gtest/gtest.h>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "lib/ip_list.h"

static const std::string resultFileName = "result.txt";

bool compareFiles(const std::string& name1, const std::string& name2)
{
    std::ifstream f1(name1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(name2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail())
        return false; //file problem

    if (f1.tellg() != f2.tellg())
        return false; //size mismatch

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

bool readIpList(const std::string& fileName, IpList& ipList)
{    
    std::fstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        std::cout << "failed to open " << '\n';
        return false;
    }

    // Read ip list
    ipList.inputData(inputFile);
    return true;
}

void runTestTemplate(const std::string testResultFileName,
                     const IpFilter& filter)
{
    IpList ipList{};
    auto res = readIpList("ip_filter.tsv", ipList);
    ASSERT_EQ(res, true);

    std::ofstream outputFile;
    outputFile.open(resultFileName, std::fstream::out);
    ASSERT_EQ(outputFile.is_open(), true);

    ipList.print(outputFile, filter);
    ASSERT_EQ(compareFiles(testResultFileName, resultFileName), true);
}

TEST(SortTest, simple)
{
    IpList ipList{};
    auto res = readIpList("ip_filter.tsv", ipList);
    ASSERT_EQ(res, true);

    std::ofstream outputFile;
    outputFile.open(resultFileName, std::fstream::out);
    ASSERT_EQ(outputFile.is_open(), true);

    ipList.sort();
    ipList.print(outputFile, IpFilter{});
    ASSERT_EQ(compareFiles("sort_test_result.txt", resultFileName), true);
}

TEST(Filter1Test, simple)
{
    runTestTemplate("f1_result.txt",
        IpFilter{ [](const IpData& ip) { return ip.at(0) == 1; }});
}

TEST(Filter2Test, simple)
{
    runTestTemplate("f2_result.txt",
        IpFilter{ 
                [](const IpData& ip)
                {
                    return ip.at(0) == 46 && ip.at(1) == 70;
                }});
}

TEST(Filter3Test, simple)
{
    runTestTemplate("f3_result.txt",
        IpFilter{ 
            [](const IpData& ip)
            {
                for (int i = 0; i < 4; ++i)
                {
                    if (ip.at(i) == 46)
                        return true;
                }
                return false;
            }});
}
