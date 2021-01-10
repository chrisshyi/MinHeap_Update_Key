#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MinHeap.h"
#include <random>
#include <algorithm>
#include <functional>

class MyClass {
    public:
        int x1;
        int x2;
        
        MyClass(int x1, int x2) : x1{x1}, x2{x2} {};

        friend bool operator<(const MyClass&, const MyClass&);
        friend bool operator==(const MyClass&, const MyClass&);
};

// custom specialization of std::hash can be injected in namespace std
namespace std
{
    template<> struct hash<MyClass>
    {
        std::size_t operator()(const MyClass& s) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(s.x1);
            std::size_t h2 = std::hash<int>{}(s.x2);
            return h1 ^ (h2 << 1);
        }
    };
}



bool operator<(const MyClass& obj1, const MyClass& obj2) {
    std::less<int> less_than;
    return less_than(obj1.x1 + obj1.x2, obj2.x1 + obj2.x2);
}

bool operator==(const MyClass& obj1, const MyClass& obj2) {
    std::equal_to<int> eq;
    return eq(obj1.x1, obj2.x1) && eq(obj1.x2, obj2.x2);
}


TEST_CASE("Min heap of integers") {
    MinHeap<int> heap;

    REQUIRE(heap.size() == 0);

    SECTION("Can push and remove single element") {
        heap.push(10);
        REQUIRE(heap.size() == 1);
        REQUIRE(heap.peek() == 10);
        auto min_elem = heap.extract_min();
        REQUIRE(min_elem.has_value());
        REQUIRE(min_elem.value() == 10);
        REQUIRE(heap.size() == 0);
    }

    SECTION("Can push and pop multiple elements") {
        std::vector<int> heap_sort; 
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution uniform_int(1, 150);
        for (int i = 0; i < 50; i++) {
            heap.push(uniform_int(gen)); 
        }
        for (int j = 0; j < 25; j++) {
            heap_sort.push_back(heap.extract_min().value());
        }
        REQUIRE(std::is_sorted(heap_sort.begin(), heap_sort.end()));
        for (int j = 0; j < 25; j++) {
            heap_sort.push_back(heap.extract_min().value()); 
        }
        REQUIRE(std::is_sorted(heap_sort.begin(), heap_sort.end()));
        REQUIRE(heap.size() == 0);
    }
}

TEST_CASE("Min heap of MyClass objects") {
    MinHeap<MyClass> heap; 


    SECTION("Can push and remove single element") {
        heap.push(MyClass(5, 10));
        REQUIRE(heap.size() == 1);
        auto min_elem = heap.extract_min().value();
        REQUIRE(min_elem.x1 == 5);
        REQUIRE(min_elem.x2 == 10);
    }

    SECTION("Can push and remove multiple elements") {
        std::vector<MyClass> heap_sort;  
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution uniform_int(1, 150);
        
        for (int i = 0; i < 50; i++) {
            heap.push(MyClass(uniform_int(gen), uniform_int(gen))); 
        }
        for (int j = 0; j < 25; j++) {
            heap_sort.push_back(heap.extract_min().value());
        }
        REQUIRE(std::is_sorted(heap_sort.begin(), heap_sort.end()));
        for (int j = 0; j < 25; j++) {
            heap_sort.push_back(heap.extract_min().value()); 
        }
        REQUIRE(std::is_sorted(heap_sort.begin(), heap_sort.end()));
        REQUIRE(heap.size() == 0);
    }
}