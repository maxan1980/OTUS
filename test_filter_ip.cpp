#define BOOST_TEST_MODULE test_ip
#include <vector>
#include <string>
#include "ip_filter.h"

//#include <boost/test/unit_test.hpp>
#include <gtest/gtest.h>

std::vector<std::string> input = {  "113.162.145.156	111	0",
                                    "157.39.22.224	5	6",
                                    "79.180.73.190	2	1",
                                    "179.210.145.4	22	0",
                                    "219.102.120.135	486	0",
                                    "67.232.81.208	1	0",
                                    "85.254.10.197	0	7",
                                    "23.240.215.189	6	0",
                                    "1.29.168.152	17	0",
                                    "185.69.186.168	1	3",
                                    "110.152.103.161	0	1",
                                    "185.182.81.131	1	1",
                                    "68.45.152.8	2	0",
                                    "114.221.179.117	0	1",
                                    "185.89.100.249	752	0"  };


TEST(sorted_fill, sorted_fill) {
    std::vector<std::string> result = { "219.102.120.135",
                                    "185.182.81.131",
                                    "185.89.100.249",
                                    "185.69.186.168",
                                    "179.210.145.4",
                                    "157.39.22.224",
                                    "114.221.179.117",
                                    "113.162.145.156",
                                    "110.152.103.161",
                                    "85.254.10.197",
                                    "79.180.73.190",
                                    "68.45.152.8",
                                    "67.232.81.208",
                                    "23.240.215.189",
                                    "1.29.168.152" };
    IpAddress ip;
    for (auto& v: input) {
        ip.add_address(v);
    }
    auto res = ip.get_addr_base();

    ASSERT_EQ(result,res);
}


TEST(test_valid_sorted_find1, test_valid_sorted_find1) {
    std::vector<std::string> result = { "185.182.81.131",
                                        "185.89.100.249",
                                        "185.69.186.168" };
    IpAddress ip;
    for (auto& v: input) {
        ip.add_address(v);
    }
    auto res = ip.find(185);
    ASSERT_EQ(result,res);
}

TEST(test_valid_sorted_find2, test_valid_sorted_find2) {
    std::vector<std::string> result = { "68.45.152.8" };
    IpAddress ip;
    for (auto& v: input) {
        ip.add_address(v);
    }
    auto res = ip.find(68,45);
    ASSERT_EQ(result,res);
}


TEST(test_valid_sorted_find_any, test_valid_sorted_find_any) {
    std::vector<std::string> result = { "179.210.145.4",
                                        "114.221.179.117"};
    IpAddress ip;
    for (auto& v: input) {
        ip.add_address(v);
    }
    auto res = ip.find_any(179);
    ASSERT_EQ(result,res);
}
