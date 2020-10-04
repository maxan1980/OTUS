#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <sstream>
#include <algorithm>


class IpAddress {
public:
    
IpAddress ()= default;

void add_address(std::string line);
std::vector<std::string> find(int i1);
std::vector<std::string> find(int i1,int i2);
std::vector<std::string> find_any(int val);
std::vector<std::string> get_addresses_any(int adr1);
std::string get_addr_line() const ;
std::vector<std::string> get_addr_base ();


const std::vector<int>& get_address() const ;

private:
    struct Ip {
        Ip() = default; 
        std::vector<int> addr;
        bool operator<(const Ip& other) const;
        std::string get_string_addr() const;
    };
    std::set<Ip> base;
};


