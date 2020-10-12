#include <iostream>
#include <string>
#include "ip_filter.h"

int main(void) {
    IpAddresses ip_addr;
    std::string line;
    while (std::getline(std::cin, line)) {
        ip_addr.add_address(std::move(line));
    }

    auto base = ip_addr.get_addr_base();
    for (auto& i : base) {
        std::cout << i << std::endl;
    }

    auto res_1 = ip_addr.find(1);
    for (auto& i : res_1) {
        std::cout << i << std::endl;
    }

    auto res_2 = ip_addr.find(46,70);
    for (auto& i : res_2) {
        std::cout << i << std::endl;
    }

    auto res_any = ip_addr.find_any(46);
    for (auto& i : res_any) {
        std::cout << i << std::endl;
    }
}