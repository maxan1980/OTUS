#pragma once

#include <string>
#include <vector>
#include <set>



class IpAddresses {
public:
    
IpAddresses ()= default;

void add_address(const std::string& line);
std::vector<std::string> find(int i1) const;
std::vector<std::string> find(int i1,int i2) const;
std::vector<std::string> find_any(int val) const;
std::vector<std::string> get_addresses_any(int adr1) const;
std::string get_addr_line() const ;
std::vector<std::string> get_addr_base () const;


const std::vector<int>& get_address() const ;

private:
    struct Ip {
        Ip() { addr.reserve(4); } 
        std::vector<int> addr;
        bool operator<(const Ip& other) const;
        std::string get_string_addr() const;
    };
    std::multiset<Ip> base;
};


