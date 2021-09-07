#include <gtest/gtest.h>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

#include "lib/ip_list.h"

static const std::string resultFileName = "result.txt";

bool compareFiles(const std::string& name1, const std::string& name2)
{
    std::ifstream file1(name1, std::ifstream::in);
    std::ifstream file2(name2, std::ifstream::in);

    std::string str1;
    std::string str2;
    while (std::getline(file1, str1) && std::getline(file2, str2))
    {
        if (str1 != str2)
            return false;
    }

    return !std::getline(file2, str2) && !std::getline(file1, str1);
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
    ASSERT_TRUE(readIpList("ip_filter.tsv", ipList));

    std::ofstream outputFile;
    outputFile.open(resultFileName, std::fstream::out);
    ASSERT_TRUE(outputFile.is_open());
    ipList.print(outputFile, filter);
    outputFile.close();

    ASSERT_TRUE(compareFiles(testResultFileName, resultFileName));
}

TEST(SortTest, simple)
{
    IpList ipList{};
    ASSERT_TRUE(readIpList("ip_filter.tsv", ipList));

    std::ofstream outputFile;
    outputFile.open(resultFileName, std::fstream::out);
    ASSERT_TRUE(outputFile.is_open());

    ipList.sort();
    ipList.print(outputFile, IpFilter{});
    ASSERT_TRUE(compareFiles("sort_test_result.txt", resultFileName));
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
