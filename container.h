#pragma once
#include <memory>
#include <cstring>

template<class TT>
struct Node {
    Node(TT& val, Node* addr) : value(val),next(addr) {}
    TT value;
    Node* next;
};

template<class I>
struct Iterator {
    Node<I>* iter;
    Iterator():iter( nullptr ) {}
    Iterator(Node<I>* iter) : iter(iter) {}

    Iterator& operator++() { 
        iter = iter->next; 
        return *this;
    }
    Iterator& operator++(int) { 
        iter = iter->next; 
        return *this;
    }

    I& operator*() { return iter->value ;}
    I& operator->() { return this ;}  
    bool operator!=(const Iterator& it) {
        return iter != it.iter;
    }  
};

template<typename T,typename Alloc = std::allocator<Node<T>>>
class MContainer {
public:
    MContainer() : alloc(Alloc()) {
        p_begin.iter = nullptr;  
        p_end.iter = nullptr;
        p_prev.iter = nullptr; 
    }
    ~MContainer() {
        auto start = p_begin;
        while ( start != p_end ) {
            auto temp = start.iter->next;
            alloc.deallocate(start.iter,1);
            start = temp;
        }
    }

    Iterator<T> begin() {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        return p_begin;
    }

    Iterator<T> end() {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        return p_end;
    }

    const Iterator<T> cbegin() const {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        return p_begin;
    }
    
    const Iterator<T> cend() const {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        return p_end;
    }

    size_t size() const{
        return current_size;
    }

    bool empty() {
        return !current_size;
    }

    void push_back(T val) {
#ifdef VERBOSE
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
#endif
        Node<T>* p = alloc.allocate(1);
        alloc.construct( p, Node<T> (val,nullptr) );

        if (!p_begin.iter) {
            p_begin.iter = p_prev.iter = p;
        } else {
            p_prev.iter->next = p;
            p_prev.iter = p;
        }

        current_size++;
    }

private:
    Iterator<T> p_begin;
    Iterator<T> p_end;
    Iterator<T> p_prev;

    Alloc alloc;
    size_t current_size = 0;
};
