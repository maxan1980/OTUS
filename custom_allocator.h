#pragma once
#include <iostream>

//#define VERBOSE

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

template <typename T,size_t elm = 1>
struct custom_allocator {
    using value_type = T;

    size_t elements = elm;

    template <typename U>
    struct rebind {
        using other = custom_allocator<U,elm>;
    };
    
    T* allocate( std::size_t n ) {
#ifdef VERBOSE
            std::cout << __PRETTY_FUNCTION__ << "allocate memory [" << n*elements << "]" << std::endl;
#endif
        if (!base) {
            base = malloc( n * sizeof(T) * elements ); 
            if ( !base ) {
                throw std::bad_alloc();
            }
        } else {
            if (el_count >= elements) {
                throw std::bad_alloc();
            }
        }
        return reinterpret_cast< T* > (base) + el_count ;
    }

    void deallocate(T* p, std::size_t n) {
        if (--el_count) {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << "skeep freeing memory n: ["<< n << "]" << " count : " << el_count << std::endl;
#endif
        } else {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << " free memory  n: ["<< n <<"]" << std::endl;
#endif
            if ( base ) {
                std::free( base );
                base = nullptr;
            }
        }
    }

    template< typename U, typename... Args>
    void construct(U* p,Args && ...args) {
#ifdef VERBOSE
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new( p ) U( std::forward<Args>(args)... );
        ++el_count;
    }

    void destroy (T* p) {
#ifdef VERBOSE
        std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }

private:
    void* base = nullptr;
    size_t el_count = 0;
};