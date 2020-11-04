#include <vector>
#include "custom_allocator.h"
#include "container.h"
#include <gtest/gtest.h>

TEST(std_vec_test_count, std_vec_test_count) {
    const int count = 3;
    std::vector<int,custom_allocator<int,10>> vec;
    for (int i=0; i < count; ++i) {
        vec.push_back(i);
    }
    ASSERT_EQ(vec.size(),count);
}

TEST(std_map_test, std_map_test) {
    const int count = 3;
    auto custom_map_alloc = std::map<int,int,std::less<int>,custom_allocator<std::pair<const int,int>,10>>{}; 
    for ( int i=0; i < count; ++i ) {
        custom_map_alloc.insert({i,i});
    }
    ASSERT_EQ(custom_map_alloc[0],0);
    ASSERT_EQ(custom_map_alloc[1],1);
    ASSERT_EQ(custom_map_alloc[2],2);
    ASSERT_EQ(custom_map_alloc.size(),count);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
