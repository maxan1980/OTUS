#include "ip_filter.h"
 #include <sstream>
 #include <tuple>

void IpAddresses::add_address(const std::string& line) {
    int start_pos = line.find_first_not_of(' ');
    int end_pos = line.find_first_of('\t',start_pos);

    std::string add = line.substr(start_pos,end_pos-start_pos);
    Ip ip;
    std::istringstream str(add);
    bool status = true;
    for (int i=0; i < 4; ++i) {
        int var = -1;
        str >> var;
        if ((var >= 0) && (var <=255)) {
            ip.addr.push_back(var);
            str.ignore(1);
        } else {
            status = false;
            break;
        }    
    }
    if (status) 
        base.insert(ip);
}

std::vector<std::string> IpAddresses::get_addr_base () const {
    std::vector<std::string> ret;
    ret.reserve(base.size());
    for (auto it = base.rbegin(); it != base.rend();++it) {
        ret.push_back(it->get_string_addr());
    }
    return ret;
}

std::vector<std::string> IpAddresses::find(int i1) const {
    std::vector<std::string> ret;
    Ip ip_start;
    Ip ip_finish;
    for (int i=0; i < 4; ++i) {
        if (i==0) {
            ip_start.addr.push_back(i1);
            ip_finish.addr.push_back(i1);
        } else {
           ip_start.addr.push_back(0);
           ip_finish.addr.push_back(255);
        } 
    }
    auto start_it = base.lower_bound(ip_start);
    auto finish_it = base.lower_bound(ip_finish);

    while (start_it != finish_it) {
        ret.push_back((--finish_it)->get_string_addr());
    }
    return ret;
}

std::vector<std::string> IpAddresses::find(int i1,int i2) const {
    std::vector<std::string> ret;
    Ip ip_start;
    Ip ip_finish;
    for (int i=0; i < 4; ++i) {
        if (i==0) {
            ip_start.addr.push_back(i1);
            ip_finish.addr.push_back(i1);
        } else if (i == 1) {
            ip_start.addr.push_back(i2);
            ip_finish.addr.push_back(i2);
        } else {
           ip_start.addr.push_back(0);
           ip_finish.addr.push_back(255);
        } 
    }
    auto start_it = base.lower_bound(ip_start);
    auto finish_it = base.lower_bound(ip_finish);

    while (start_it != finish_it) {
        ret.push_back((--finish_it)->get_string_addr());
    }
    return ret;
}

std::vector<std::string> IpAddresses::find_any(int val) const {
    std::vector<std::string> ret;
    for (auto start = base.rbegin(); start!= base.rend(); ++start) {
        bool status = false;
        for (auto & id: start->addr) {
            if (id == val) {
                status = true;
                break;
            }
        }
        if (status)
            ret.push_back(start->get_string_addr());
    }
    return ret;
}

bool IpAddresses::Ip::operator<(const IpAddresses::Ip& other) const {
    return std::make_tuple(addr[0],addr[1],addr[2],addr[3]) < 
           std::make_tuple(other.addr[0],other.addr[1],other.addr[2],other.addr[3]);
}

std::string IpAddresses::Ip::get_string_addr() const {
    std::string str;
    for (int i=0; i < 4; ++i) {
        str += std::to_string(addr[i]);
        if (i < 3)
            str +="."; 
    }
    return str;
}

