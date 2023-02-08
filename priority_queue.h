/*
 *  Implmentation of a templated priority queue using my heap methods from "heap.h"
 *  The class Comparable must be comparable for the operator passed to Compare. E.g., the < operator.
 *  The class Container must satisfy the cpp standard sequence container requirements. If none is passed, std::vector is used.
 *  The class Compare must be a valid comparator. If none is passed, std::less is used.
 *  Written by Zach Schrag
*/

#pragma once

#include <functional>
#include <vector> // default container if none is passed
#include <iostream> // for print_queue
#include "heap.h" // heap methods

template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<typename Container::value_type>>
class PriorityQueue {
    Compare compare;
    Container container;

    public:
        // constructors
        PriorityQueue() : compare{}, container{} {}
        explicit PriorityQueue(const Compare& comparator) : compare{comparator}, container{} {}
        explicit PriorityQueue(const Container& container) : compare{}, container{container} { heapify(&(this->container), compare); }
        PriorityQueue(const Compare& comparator, const Container& container) : compare{comparator}, container{container} { heapify(&(this->container), compare); }

        // access
        typename Container::const_reference top() const { return heap_get_min(container); }

        // capacity
        bool empty() const { return container.size() < 2; }
        size_t size() const { return container.size() < 2 ? 0 : container.size() - 1; }

        // modifiers
        void make_empty() { container = Container{}; }
        void push(const typename Container::value_type& value) { heap_insert(&container, value, compare); }
        void pop() { 
            if (empty()) return; // Decided to do nothing (instead of throwing an exception) if pop() is called on an empty priority queue 
            heap_delete_min(&container, compare); // heap_delete_min will throw an exception on an empty heap!
        }

        // visualization
        void print_queue(std::ostream& os = std::cout) const {
            if (empty()) os << "<empty>";
            for (size_t i = 1; i < container.size(); i++) {
                if (i == container.size() - 1) os << container.at(i);
                else os << container.at(i) << ", ";
            }
            os << std::endl;
        }

};
