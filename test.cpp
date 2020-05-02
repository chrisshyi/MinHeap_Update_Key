#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MinHeap.h"
#include <random>
#include <algorithm>

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