/*
 *  Implmentation of templated heap methods
 *  The class Container must satisfy the cpp standard sequence container requirements
 *  The class Compare must be a valid comparator. If none is passed, std::less is used
 *  Written by Zach Schrag
*/

#pragma once
#include <functional>

// helper method which percolates down from the passed index. (for heapify and delete_min)
template<class Container, class Compare = std::less<typename Container::value_type>>
void percolate_down(Container* container, size_t hole, Compare comparator = std::less<typename Container::value_type>{}) {
    // promised valid input

    // some things which may prove useful later
    typename Container::value_type hole_value = container->at(hole);
    typename Container::value_type min_child;
    size_t index_to_move_hole;

    while (hole * 2 < container->size()) {   // if true then there is a left child (note there cannot be right child without left child)
        if (hole * 2 + 1 < container->size()) { // if true then there is a right child
            // determine which child to move up
            if (comparator(container->at(hole * 2), container->at(hole * 2 + 1)) ) { // left child is winner
                min_child = container->at(hole * 2);
                index_to_move_hole = hole * 2;
            }
            else { // right child is winner
                min_child = container->at(hole * 2 + 1);
                index_to_move_hole = hole * 2 + 1;
            }
        }
        else { // no right child
            min_child = container->at(hole * 2);
            index_to_move_hole = hole * 2;
        }

        if (comparator(min_child, hole_value)) { // if true then winning child needs to move up
            container->at(hole) = min_child;
            hole = index_to_move_hole;
        }
        else { // hole no longer less than min child, stop moving down
            break;
        }
    }
    container->at(hole) = hole_value; // placed the saved value back into the heap
}


// helper method to percolate up from passed index (for insert)
template<class Container, class Compare = std::less<typename Container::value_type>>
void percolate_up(Container* container, const typename Container::value_type& value, 
                  size_t index, Compare comparator = std::less<typename Container::value_type>{}) {
    // promised valid input
    
    // some things which may prove useful in the near future
    size_t hole = index;
    bool push_parent = false; 
    typename Container::value_type parent = container->at(hole / 2); // in case we need for later (exception handling)

    while (hole > 1) {
        if ( !(comparator(value, container->at(hole / 2))) ) break; // comparator no longer satisified, value should not move any further up

        // avoid causing an exception by preventing .at(size()) on first iteration. save the value to add later 
        if (hole == container->size()) {
            push_parent = true;
        }
        else {
            container->at(hole) = container->at(hole / 2); // fill hole with parent (or skip to add later if check above is true)
        }
        hole /= 2; // move hole to old parent's index
    }
    // insert the value into its correct location
    if (hole == container->size()) // edge case of inserting a maximum value (one that should not move anywhere) - avoids causing an exception
        container->push_back(value);
    else
        container->at(hole) = value;

    if (push_parent) container->push_back(parent); // push value we skipped on the first iteration; this should also increment the heap size
}


// heap methods
template <class Container, class Compare = std::less<typename Container::value_type>>
void heapify(Container* container, Compare comparator = std::less<typename Container::value_type>{}) {
    // move everything over as heap should begin at index 1
    container->insert(container->begin(), typename Container::value_type());

    // percolate down from index n/2 to 1
    for (size_t i = container->size() / 2; i >= 1; i--) {
        percolate_down(container, i, comparator);
    }

}

template <class Container, class Compare = std::less<typename Container::value_type>>
void heap_insert(Container* container, const typename Container::value_type& value, Compare comparator = std::less<typename Container::value_type>{}) {
    // create the heap if the user passes an empty container
    if (container->size() < 2) {
        container->resize(2);
        container->at(1) = value;
        return;
    }
    // otherwise perform typical heap_insert by "digging" a hole at the end of the array,
    // but save operations and do not insert the value yet otherwise we'll just have to swap them
    percolate_up(container, value, container->size(), comparator);
}


template <class Container>
const typename Container::value_type& heap_get_min(const Container& container) { 
    if (container.size() < 2)
        throw std::invalid_argument("Heap is empty");

    return container.at(1);
}


template <class Container, class Compare = std::less<typename Container::value_type>>
void heap_delete_min(Container* container, Compare comparator = std::less<typename Container::value_type>{}) {
    if (container->size() < 2)
        throw std::invalid_argument("Heap is empty");

    container->at(1) = container->at(container->size() - 1); // place last element of heap into root
    container->pop_back(); // decrement the size before we begin
    if (container->size() < 2) return; // safeguard reaching out of bounds with the helper function. if this is true then the heap is now empty so just return
    percolate_down(container, 1, comparator); // percolate down from the root
}
