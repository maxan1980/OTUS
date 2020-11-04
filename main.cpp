#include "custom_allocator.h"
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <list>
#include "container.h"

int factorial(int i) {
    int res = 1;
    while (i) {
        res*=i--;
    }
    return res;
}

int main(void) {
    auto std_map_alloc = std::map<int,int>{}; 
    for ( int i=0; i < 10; ++i ) {
        std_map_alloc.insert({i,factorial(i)});
    }

    auto custom_map_alloc = std::map<int,int,std::less<int>,custom_allocator<std::pair<const int,int>,10>>{}; 
    for ( int i=0; i < 10; ++i ) {
        custom_map_alloc.insert({i,factorial(i)});
    }

    for (auto& x : std_map_alloc) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << std::endl;

    for (auto& x : custom_map_alloc) {
        std::cout << x.first << " " << x.second << std::endl;
    }

    std::cout << std::endl;

    auto mas = MContainer<int>{};
    for ( int i=0; i < 10; ++i ) {
        mas.push_back(i);
    }

    for (auto& v: mas) {
        std::cout << v << std::endl;
    }

    std::cout << std::endl;

    auto mac = MContainer<int,custom_allocator<Node<int>,10>>();
    for ( int i=0; i < 10; ++i ) {
        mac.push_back(i);
    }

    for (auto& v: mac) {
        std::cout << v << std::endl;
    }
    return 0;
}