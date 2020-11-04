cmake_minimum_required(VERSION 3.2)

project(allocator C CXX)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.100)
endif()


find_package(Threads REQUIRED)

find_package(GTest REQUIRED)

set(PThreadLib -pthread)

configure_file(version.h.in version.h)

add_executable(allocator main.cpp)
add_executable(alloc_test alloc_test.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_STANDARD 17)

target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(
    alloc_test PRIVATE
    ${GTEST_INCLUE__DIRS}
)

target_link_libraries(
    alloc_test PRIVATE
    ${GTEST_BOTH_LIBRARIES}
    pthread
)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(alloc_test PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(alloc_test PRIVATE
        -Wall -Wextra -pedantic
    )
endif()



install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(aloc_test aloc_test)

