#include "priority_queue.h"
#include <iostream>
#include <sstream>

using std::cout, std::endl;

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
    std::cout << magenta << "  [help]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << magenta << #X << " threw an incorrect exception." << reset << std::endl;\
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

int main() {

    // default constructor
    {
        PriorityQueue<int> pq;
        expect(pq.empty() to_be true);
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);

        PriorityQueue<double> pq2;
        expect(pq2.empty() to_be true);
        expect(pq2.size() to_be 0);
        expect_throw(pq2.top(), std::invalid_argument);

        PriorityQueue<char> pq3;
        expect(pq3.empty() to_be true);
        expect(pq3.size() to_be 0);
        expect_throw(pq3.top(), std::invalid_argument);

        PriorityQueue<std::vector<int>> pq4;
        expect(pq4.empty() to_be true);
        expect(pq4.size() to_be 0);
        expect_throw(pq4.top(), std::invalid_argument);
    }

    // explicit constructor - container
    {
        PriorityQueue<int, std::vector<int>> pq;
        expect(pq.empty() to_be true);
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);

        PriorityQueue<double, std::vector<double>> pq2;
        expect(pq2.empty() to_be true);
        expect(pq2.size() to_be 0);
        expect_throw(pq2.top(), std::invalid_argument);

        PriorityQueue<char, std::vector<char>> pq3;
        expect(pq3.empty() to_be true);
        expect(pq3.size() to_be 0);
        expect_throw(pq3.top(), std::invalid_argument);

        PriorityQueue<std::string, std::vector<std::vector<std::string>>> pq4;
        expect(pq4.empty() to_be true);
        expect(pq4.size() to_be 0);
        expect_throw(pq4.top(), std::invalid_argument);
    }

    // explicit constructor - comparer
    {
        PriorityQueue<int, std::vector<int>, std::greater<int>> pq;
        expect(pq.empty() to_be true);
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);

        PriorityQueue<double, std::vector<double>, std::greater<double>> pq2;
        expect(pq2.empty() to_be true);
        expect(pq2.size() to_be 0);
        expect_throw(pq2.top(), std::invalid_argument);

        PriorityQueue<char, std::vector<char>, std::less_equal<char>> pq3;
        expect(pq3.empty() to_be true);
        expect(pq3.size() to_be 0);
        expect_throw(pq3.top(), std::invalid_argument);

        PriorityQueue<std::string, std::vector<std::string>, std::greater_equal<std::string>> pq4;
        expect(pq4.empty() to_be true);
        expect(pq4.size() to_be 0);
        expect_throw(pq4.top(), std::invalid_argument);
    }

    // decked out constructor
    {
        PriorityQueue<int, std::vector<int>, std::greater<int>> pq;
        expect(pq.empty() to_be true);
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);

        PriorityQueue<double, std::vector<double>, std::greater<double>> pq2;
        expect(pq2.empty() to_be true);
        expect(pq2.size() to_be 0);
        expect_throw(pq2.top(), std::invalid_argument);

        PriorityQueue<std::vector<char>, std::vector<std::vector<char>>, std::less_equal<std::vector<char>>> pq3;
        expect(pq3.empty() to_be true);
        expect(pq3.size() to_be 0);
        expect_throw(pq3.top(), std::invalid_argument);

        PriorityQueue<std::vector<std::string>, std::vector<std::vector<std::string>>, std::greater_equal<std::vector<std::string>>> pq4;
        expect(pq4.empty() to_be true);
        expect(pq4.size() to_be 0);
        expect_throw(pq4.top(), std::invalid_argument);
    }

    // top
    {
        PriorityQueue<int> pq;
        expect_throw(pq.top(), std::invalid_argument);
        pq.push(12);
        expect(pq.top() to_be 12);
        pq.push(11);
        expect(pq.top() to_be 11);
        pq.push(10);
        expect(pq.top() to_be 10);
        pq.push(-9);
        expect(pq.top() to_be -9);
        pq.push(-8);
        expect(pq.top() to_be -9);
        pq.push(-10);
        expect(pq.top() to_be -10);
        //pq.print_queue();
    }

    // pq.top() pt2
    {
        PriorityQueue<double> pq;
        expect_throw(pq.top(), std::invalid_argument);
        pq.push(12.3);
        expect(pq.top() to_be 12.3);
        pq.push(11.9);
        expect(pq.top() to_be 11.9);
        pq.push(10.1);
        expect(pq.top() to_be 10.1);
        pq.push(-9.13);
        expect(pq.top() to_be -9.13);
        pq.push(-9.14);
        expect(pq.top() to_be -9.14);
        pq.push(-9.135);
        expect(pq.top() to_be -9.14);
        //pq.print_queue();
    }

    // push - increasing order followed by a new min
    {
        PriorityQueue<int> pq;

        pq.push(1);
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 1);

        pq.push(2);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 1);

        pq.push(3);
        expect(pq.size() to_be 3);
        expect(pq.top() to_be 1);

        pq.push(4);
        expect(pq.size() to_be 4);
        expect(pq.top() to_be 1);

        pq.push(0);
        expect(pq.size() to_be 5);
        expect(pq.top() to_be 0);
    }

    // push - mixed insertion
    {
        PriorityQueue<double> pq;

        pq.push(27.4);
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 27.4);

        pq.push(19.4214);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 19.4214);

        pq.push(13.1);
        expect(pq.size() to_be 3);
        expect(pq.top() to_be 13.1);

        pq.push(17.4);
        expect(pq.size() to_be 4);
        expect(pq.top() to_be 13.1);

        pq.push(114);
        expect(pq.size() to_be 5);
        expect(pq.top() to_be 13.1);

        pq.push(0);
        expect(pq.size() to_be 6);
        expect(pq.top() to_be 0);

        pq.push(91248.1924);
        expect(pq.size() to_be 7);
        expect(pq.top() to_be 0);

        pq.push(0.01);
        expect(pq.size() to_be 8);
        expect(pq.top() to_be 0);

        pq.push(-0.01);
        expect(pq.size() to_be 9);
        expect(pq.top() to_be -0.01);
    }

    // push - increasing order
    {
        PriorityQueue<std::string, std::vector<std::string>> pq;

        pq.push("hello");
        expect(pq.size() to_be 1);
        expect(pq.top() to_be "hello");

        pq.push("hello0");
        expect(pq.size() to_be 2);
        expect(pq.top() to_be "hello");

        pq.push("hello1");
        expect(pq.size() to_be 3);
        expect(pq.top() to_be "hello");

        pq.push("hello2");
        expect(pq.size() to_be 4);
        expect(pq.top() to_be "hello");

        pq.push("hello3");
        expect(pq.size() to_be 5);
        expect(pq.top() to_be "hello");

        pq.push("hello4");
        expect(pq.size() to_be 6);
        expect(pq.top() to_be "hello");
    }

    // pop 
    {
        PriorityQueue<int> pq;

        pq.push(5);
        pq.push(4);
        pq.push(3);
        pq.push(2);
        pq.push(1);
        pq.push(0);

        // confirm initial condition
        expect(pq.size() to_be 6);
        expect(pq.top() to_be 0);

        pq.pop();
        expect(pq.size() to_be 5);
        expect(pq.top() to_be 1);

        pq.pop();
        expect(pq.size() to_be 4);
        expect(pq.top() to_be 2);

        pq.pop();
        expect(pq.size() to_be 3);
        expect(pq.top() to_be 3);

        pq.pop();
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 4);

        pq.pop();
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 5);

        pq.pop();
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);
    }

    // push and pop
    {
        PriorityQueue<double> pq;

        pq.push(38.2);
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 38.2);

        pq.pop();
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);

        pq.push(31.4);
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 31.4);

        pq.push(8541.3);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 31.4);

        pq.pop();
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 8541.3);

        pq.push(10.3);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 10.3);

        pq.push(16.7);
        expect(pq.size() to_be 3);
        expect(pq.top() to_be 10.3);

        pq.pop();
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 16.7);

        pq.pop();
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 8541.3);

        pq.push(12397.1);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 8541.3);

        pq.push(-391.1);
        expect(pq.size() to_be 3);
        expect(pq.top() to_be -391.1);

        pq.push(-57193.9128);
        expect(pq.size() to_be 4);
        expect(pq.top() to_be -57193.9128);

        pq.pop();
        expect(pq.size() to_be 3);
        expect(pq.top() to_be -391.1);

        pq.pop();
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 8541.3);

        pq.pop();
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 12397.1);

        pq.push(948173.1);
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 12397.1);

        pq.push(0);
        expect(pq.size() to_be 3);
        expect(pq.top() to_be 0);

        pq.pop();
        expect(pq.size() to_be 2);
        expect(pq.top() to_be 12397.1);

        pq.pop();
        expect(pq.size() to_be 1);
        expect(pq.top() to_be 948173.1);

        pq.pop();
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);
    }

    // make_empty
    {
        PriorityQueue<int> pq;

        pq.push(2);
        pq.push(3);
        pq.make_empty();
        expect(pq.empty() to_be true);
        expect(pq.size() to_be 0);
        expect_throw(pq.top(), std::invalid_argument);
    }

    // print_queue
    {
        PriorityQueue<int> pq;
        std::stringstream ss;
        pq.print_queue(ss);
        expect(ss.str() to_be "<empty>\n");

    }


    // print_queue
    {
        PriorityQueue<int> pq;
        pq.push(3);
        pq.push(4);
        pq.push(5);
        pq.push(6);
        std::stringstream ss;
        pq.print_queue(ss);
        std::string expected = "3, 4, 5, 6\n";
        expect(ss.str() to_be expected);

        PriorityQueue<double> pq2;
        pq2.push(3.7);
        pq2.push(4.1);
        pq2.push(1.43);
        pq2.push(0.3);
        std::stringstream ss2;
        pq2.print_queue(ss2);
        std::string expected2 = "0.3, 1.43, 3.7, 4.1\n";
        expect(ss2.str() to_be expected2);
    }

    // print queue harder
    {
        PriorityQueue<char> pq;

        pq.push('h');
        pq.push('c');
        pq.push('a');
        pq.push('b');
        pq.push('z');
        pq.push('0');

        std::stringstream ss;
        pq.print_queue(ss);
        std::string expected = "0, b, a, h, z, c\n";
        expect(ss.str() to_be expected);
    }

    // print queue even harder
    {
        PriorityQueue<std::string> pq;

        pq.push("abcdef");
        pq.push("bbcdef");
        pq.push("cccdef");
        pq.push("ddddef");
        pq.push("eeeeef");
        pq.push("ffffff");
        pq.push("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

        std::stringstream ss;
        pq.print_queue(ss);
        //pq.print_queue();
        std::string expected = "abcdef, bbcdef, cccdef, ddddef, eeeeef, ffffff, zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\n";
        expect(ss.str() to_be expected);
    }

    return 0;
}
