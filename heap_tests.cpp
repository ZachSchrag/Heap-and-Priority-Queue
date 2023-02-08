#include "heap.h"
#include <iostream>
#include <vector>

using std::cout, std::endl, std::vector;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define reset   "\033[m"

#define to_be ==
#define not_to_be !=
#define is to_be
#define is_not not_to_be

#define expect(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << std::endl;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << std::endl;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << std::endl;\
    std::abort();\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << std::endl;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << blue << #X << " threw an incorrect exception." << reset << std::endl;\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<std::endl;\
  }\
}

#define expect_no_throw(X) {\
  try { X; }\
  catch(...) {\
    std::cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << std::endl;\
  }\
}


// method to pretty print heap for visual confirmation / debugging assistance
template<class Container>
void print_heap(Container& container, std::ostream& os = std::cout, unsigned int depth = 0, unsigned int index = 1) {
    if (container.empty()) os << "<empty>" << endl;

    if ( (index * 2) + 1 < container.size()) print_heap(container, os, depth + 1, (index * 2 + 1));
    os << std::string(depth * 2, ' ') << container.at(index) << endl;
    if (index * 2 < container.size()) print_heap(container, os, depth + 1, index * 2);
}

int main() {

    // heap_get_min
    {
        vector<int> heap;

        expect_throw(heap_get_min(heap), std::invalid_argument);
        heap_insert(&heap, 12);
        expect(heap_get_min(heap) to_be 12);
        heap_insert(&heap, 11);
        expect(heap_get_min(heap) to_be 11);
        heap_insert(&heap, 10);
        expect(heap_get_min(heap) to_be 10);
        heap_insert(&heap, -9);
        expect(heap_get_min(heap) to_be -9);
        heap_insert(&heap, -8);
        expect(heap_get_min(heap) to_be -9);
        heap_insert(&heap, -10);
        expect(heap_get_min(heap) to_be -10);
        //print_heap(heap);
    }

    // more heap_get_min
    {
        vector<double> heap;

        expect_throw(heap_get_min(heap), std::invalid_argument);
        heap_insert(&heap, 12.3);
        expect(heap_get_min(heap) to_be 12.3);
        heap_insert(&heap, 11.9);
        expect(heap_get_min(heap) to_be 11.9);
        heap_insert(&heap, 10.1);
        expect(heap_get_min(heap) to_be 10.1);
        heap_insert(&heap, -9.13);
        expect(heap_get_min(heap) to_be -9.13);
        heap_insert(&heap, -9.14);
        expect(heap_get_min(heap) to_be -9.14);
        heap_insert(&heap, -9.135);
        expect(heap_get_min(heap) to_be -9.14);
        //print_heap(heap);

    }

    // insert - simple (insert 2 max and then one min)
    {
        vector<int> heap;

        heap_insert(&heap, 1);
        //print_heap(heap);
        expect(heap.capacity() to_be 2);
        expect(heap.size() to_be 2);
        expect(heap.at(1) to_be 1);

        heap_insert(&heap, 2);
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 3);
        expect(heap.at(1) to_be 1);
        expect(heap.at(2) to_be 2);

        heap_insert(&heap, 3);
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 4);
        expect(heap.at(1) to_be 1);
        expect(heap.at(2) to_be 2);
        expect(heap.at(3) to_be 3);

        heap_insert(&heap, 0);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 5);
        expect(heap.at(1) to_be 0);
        expect(heap.at(2) to_be 1);
        expect(heap.at(3) to_be 3);
        expect(heap.at(4) to_be 2);
    }

    // insert - (insert mixed. should see values stop in the middle)
    {
        vector<double> heap;

        heap_insert(&heap, 5.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 2);
        expect(heap.size() to_be 2);
        expect(heap.at(1) to_be 5.0);

        heap_insert(&heap, 7.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 3);
        expect(heap.at(1) to_be 5.0);
        expect(heap.at(2) to_be 7.0);

        heap_insert(&heap, 9.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 4);
        expect(heap.at(1) to_be 5.0);
        expect(heap.at(2) to_be 7.0);
        expect(heap.at(3) to_be 9.0);

        // expect 6.0 to not make it to root but to move up
        heap_insert(&heap, 6.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 5);
        expect(heap.at(1) to_be 5.0);
        expect(heap.at(2) to_be 6.0);
        expect(heap.at(3) to_be 9.0);
        expect(heap.at(4) to_be 7.0);

        // expect -1.0 to make it to root
        heap_insert(&heap, -1.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 6);
        expect(heap.at(1) to_be -1.0);
        expect(heap.at(2) to_be 5.0);
        expect(heap.at(3) to_be 9.0);
        expect(heap.at(4) to_be 7.0);
        expect(heap.at(5) to_be 6.0);

        // expect 20.0 to be last element 
        heap_insert(&heap, 20.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 7);
        expect(heap.at(1) to_be -1.0);
        expect(heap.at(2) to_be 5.0);
        expect(heap.at(3) to_be 9.0);
        expect(heap.at(4) to_be 7.0);
        expect(heap.at(5) to_be 6.0);
        expect(heap.at(6) to_be 20.0);

        // expect 8 to swap with 9 and not go to root
        heap_insert(&heap, 8.0);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 8);
        expect(heap.at(1) to_be -1.0);
        expect(heap.at(2) to_be 5.0);
        expect(heap.at(3) to_be 8.0);
        expect(heap.at(4) to_be 7.0);
        expect(heap.at(5) to_be 6.0);
        expect(heap.at(6) to_be 20.0);
        expect(heap.at(7) to_be 9.0);
    }

    // insert only min
    {
        vector<char> heap;

        heap_insert(&heap, 'z');
        //print_heap(heap);
        expect(heap.capacity() to_be 2);
        expect(heap.size() to_be 2);
        expect(heap.at(1) to_be 'z');

        heap_insert(&heap, 'y');
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 3);
        expect(heap.at(1) to_be 'y');
        expect(heap.at(2) to_be 'z');

        heap_insert(&heap, 'x');
        //print_heap(heap);
        expect(heap.capacity() to_be 4);
        expect(heap.size() to_be 4);
        expect(heap.at(1) to_be 'x');
        expect(heap.at(2) to_be 'z');
        expect(heap.at(3) to_be 'y');

        heap_insert(&heap, 'v');
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 5);
        expect(heap.at(1) to_be 'v');
        expect(heap.at(2) to_be 'x');
        expect(heap.at(3) to_be 'y');
        expect(heap.at(4) to_be 'z');

        heap_insert(&heap, 'u');
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 6);
        expect(heap.at(1) to_be 'u');
        expect(heap.at(2) to_be 'v');
        expect(heap.at(3) to_be 'y');
        expect(heap.at(4) to_be 'z');
        expect(heap.at(5) to_be 'x');
    }


    // heap_delete_min insert max sequence and remove until empty
    {
        vector<int> heap;
        expect_throw(heap_delete_min(&heap), std::invalid_argument);

        // verify pre condition
        heap_insert(&heap, 1);
        expect(heap.capacity() to_be 2);
        expect(heap.size() to_be 2);
        expect(heap.at(1) to_be 1);

        heap_delete_min(&heap);
        expect(heap.capacity() to_be 2);
        expect(heap.size() to_be 1);
        expect_throw(heap.at(1), std::out_of_range);

        heap_insert(&heap, 3);
        heap_insert(&heap, 4);
        heap_insert(&heap, 5);
        heap_insert(&heap, 6);
        heap_insert(&heap, 7);
        heap_insert(&heap, 8);
        heap_insert(&heap, 9);
        // confirm pre condition
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 8);
        expect(heap.at(1) to_be 3);
        expect(heap.at(2) to_be 4);
        expect(heap.at(3) to_be 5);
        expect(heap.at(4) to_be 6);
        expect(heap.at(5) to_be 7);
        expect(heap.at(6) to_be 8);
        expect(heap.at(7) to_be 9);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 7);
        expect(heap.at(1) to_be 4);
        expect(heap.at(2) to_be 6);
        expect(heap.at(3) to_be 5);
        expect(heap.at(4) to_be 9);
        expect(heap.at(5) to_be 7);
        expect(heap.at(6) to_be 8);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 6);
        expect(heap.at(1) to_be 5);
        expect(heap.at(2) to_be 6);
        expect(heap.at(3) to_be 8);
        expect(heap.at(4) to_be 9);
        expect(heap.at(5) to_be 7);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 5);
        expect(heap.at(1) to_be 6);
        expect(heap.at(2) to_be 7);
        expect(heap.at(3) to_be 8);
        expect(heap.at(4) to_be 9);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 4);
        expect(heap.at(1) to_be 7);
        expect(heap.at(2) to_be 9);
        expect(heap.at(3) to_be 8);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 3);
        expect(heap.at(1) to_be 8);
        expect(heap.at(2) to_be 9);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 2);
        expect(heap.at(1) to_be 9);

        heap_delete_min(&heap);
        //print_heap(heap);
        expect(heap.capacity() to_be 8);
        expect(heap.size() to_be 1);
    }


    // heapify
    {
        vector<int> heap{10, 6, 12, 13, 8, 1};
        /*
                10                     10                       1    
             6     12       ->       6    1          ->      6     10  
          13   8  1                13 8  12                13  8  12
        
        */
        // cout << "before: " << endl;
        // print_heap(heap);
        heapify(&heap);
        // cout << "after: " << endl;
        // print_heap(heap);

        expect(heap.capacity() to_be 12);
        expect(heap.size() to_be 7);
        expect(heap.at(1) to_be 1);
        expect(heap.at(2) to_be 6);
        expect(heap.at(3) to_be 10);
        expect(heap.at(4) to_be 13);
        expect(heap.at(5) to_be 8);
        expect(heap.at(6) to_be 12);
    }
    
    return 0;
}
