#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <type_traits>
#include <utility>
/**
 * danieldaniel2468@gmail.com
 */


using namespace ariel;

TEST_CASE("addElement and size") {
    MyContainer<int> cont;
    CHECK(cont.size() == 0);
    cont.addElement(5);
    cont.addElement(10);
    CHECK(cont.size() == 2);
}

TEST_CASE("removeElement existing and exception") {
    MyContainer<int> cont;
    cont.addElement(1);
    cont.addElement(2);
    cont.addElement(1);
    CHECK(cont.size() == 3);
    cont.removeElement(1);
    CHECK(cont.size() == 1); // both 1s removed
    CHECK_THROWS_AS(cont.removeElement(42), std::runtime_error);
}

TEST_CASE("removeElement on empty container throws") {
    MyContainer<int> cont;
    CHECK_THROWS_AS(cont.removeElement(99), std::runtime_error);
}

// Helper to collect elements from any iterator range
template<typename Iter>
static std::vector<std::decay_t<decltype(*std::declval<Iter>())>>
collect(Iter b, Iter e) {
    using ValueType = std::decay_t<decltype(*b)>;
    std::vector<ValueType> v;
    for (; b != e; ++b) {
        v.push_back(*b);
    }
    return v;
}

// Custom struct defined at global scope for testing
struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

// Stream output for Point declared at global scope
std::ostream& operator<<(std::ostream& os, const Point& p) { 
    return os << '(' << p.x << ',' << p.y << ')';
}

TEST_CASE("AscendingIterator ordering") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_ascending_order(), cont.end_ascending_order());
    std::vector<int> expected{1,2,6,7,15};
    CHECK(v == expected);
}

TEST_CASE("DescendingIterator ordering") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_descending_order(), cont.end_descending_order());
    std::vector<int> expected{15,7,6,2,1};
    CHECK(v == expected);
}

TEST_CASE("SideCrossIterator ordering") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_side_cross_order(), cont.end_side_cross_order());
    std::vector<int> expected{1,15,2,7,6};
    CHECK(v == expected);
}

TEST_CASE("ReverseIterator ordering") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_reverse_order(), cont.end_reverse_order());
    std::vector<int> expected{2,1,6,15,7};
    CHECK(v == expected);
}

TEST_CASE("OrderIterator (insertion) ordering") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_order(), cont.end_order());
    std::vector<int> expected{7,15,6,1,2};
    CHECK(v == expected);
}

TEST_CASE("MiddleOutIterator ordering odd count") {
    MyContainer<int> cont;
    for (int x : {7,15,6,1,2}) cont.addElement(x);
    auto v = collect(cont.begin_middle_out_order(), cont.end_middle_out_order());
    std::vector<int> expected{6,15,1,7,2};
    CHECK(v == expected);
}

TEST_CASE("MiddleOutIterator ordering even count") {
    MyContainer<int> cont;
    for (int x : {1,2,3,4}) cont.addElement(x);
    auto v = collect(cont.begin_middle_out_order(), cont.end_middle_out_order());
    std::vector<int> expected{3,2,4,1};
    CHECK(v == expected);
}

TEST_CASE("Empty container iterators") {
    MyContainer<int> cont;
    CHECK(cont.begin_order() == cont.end_order());
    CHECK(cont.begin_ascending_order() == cont.end_ascending_order());
    CHECK(cont.begin_descending_order() == cont.end_descending_order());
    CHECK(cont.begin_side_cross_order() == cont.end_side_cross_order());
    CHECK(cont.begin_reverse_order() == cont.end_reverse_order());
    CHECK(cont.begin_middle_out_order() == cont.end_middle_out_order());
}

TEST_CASE("Operator<< prints correctly") {
    MyContainer<std::string> cont;
    cont.addElement("a");
    cont.addElement("bb");
    std::ostringstream oss;
    oss << cont;
    CHECK(oss.str() == "[ a bb ]");

    // empty container
    MyContainer<int> empty;
    std::ostringstream oss2;
    oss2 << empty;
    CHECK(oss2.str() == "[ ]");
}

TEST_CASE("Iterator comparison across containers") {
    MyContainer<int> c1, c2;
    for (int x : {1,2,3}) { c1.addElement(x); c2.addElement(x); }
    auto it1 = c1.begin_ascending_order();
    auto it2 = c1.begin_ascending_order();
    auto it3 = c2.begin_ascending_order();
    CHECK(it1 == it2);
    CHECK_FALSE(it1 != it2);
    CHECK_FALSE(it1 == it3);
    CHECK(it1 != it3);
}

TEST_CASE("Container works with doubles and strings") {
    MyContainer<double> cd;
    cd.addElement(3.14);
    cd.addElement(2.71);
    auto vd = collect(cd.begin_ascending_order(), cd.end_ascending_order());
    std::vector<double> expected_d{2.71,3.14};
    CHECK(vd == expected_d);

    MyContainer<std::string> cs;
    cs.addElement("apple");
    cs.addElement("banana");
    auto vs = collect(cs.begin_descending_order(), cs.end_descending_order());
    std::vector<std::string> expected_s{"banana","apple"};
    CHECK(vs == expected_s);
}

TEST_CASE("Iterator lengths equal container size") {
    MyContainer<int> cont;
    for (int x : {9,3,5,3}) cont.addElement(x);
    size_t n = cont.size();
    CHECK(collect(cont.begin_order(), cont.end_order()).size() == n);
    CHECK(collect(cont.begin_ascending_order(), cont.end_ascending_order()).size() == n);
    CHECK(collect(cont.begin_descending_order(), cont.end_descending_order()).size() == n);
    CHECK(collect(cont.begin_side_cross_order(), cont.end_side_cross_order()).size() == n);
    CHECK(collect(cont.begin_reverse_order(), cont.end_reverse_order()).size() == n);
    CHECK(collect(cont.begin_middle_out_order(), cont.end_middle_out_order()).size() == n);
}

TEST_CASE("Operations after removal reflect correct order") {
    MyContainer<int> cont;
    for (int x : {3,1,4,1,5}) cont.addElement(x);
    cont.removeElement(1);
    auto v = collect(cont.begin_ascending_order(), cont.end_ascending_order());
    std::vector<int> expected{3,4,5};
    CHECK(v == expected);
}

TEST_CASE("Container works with custom struct") {
    MyContainer<Point> pc;
    pc.addElement({2,2});
    pc.addElement({1,3});
    pc.addElement({2,1});
    auto vp = collect(pc.begin_ascending_order(), pc.end_ascending_order());
    std::vector<Point> expected{{1,3},{2,1},{2,2}};
    CHECK(vp == expected);
}

TEST_CASE("Single-element container") {
    MyContainer<int> c;
    c.addElement(42);
    CHECK(c.size() == 1);
    // every iterator should produce exactly [42]
    auto asc = collect(c.begin_ascending_order(), c.end_ascending_order());
    auto desc = collect(c.begin_descending_order(), c.end_descending_order());
    auto cross = collect(c.begin_side_cross_order(), c.end_side_cross_order());
    auto rev = collect(c.begin_reverse_order(), c.end_reverse_order());
    auto ins = collect(c.begin_order(), c.end_order());
    auto mid = collect(c.begin_middle_out_order(), c.end_middle_out_order());
    std::vector<int> expect{42};
    CHECK(asc  == expect);
    CHECK(desc == expect);
    CHECK(cross== expect);
    CHECK(rev  == expect);
    CHECK(ins  == expect);
    CHECK(mid  == expect);
}

TEST_CASE("Two-element container middle-out & side-cross") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    // insertion: [10,20]
    // ascending: [10,20], descending: [20,10]
    // side-cross: smallest, largest: [10,20]
    // middle-out: mid=1 (index1), then 0 → [20,10]
    CHECK( collect(c.begin_order(), c.end_order())            == std::vector<int>{10,20} );
    CHECK( collect(c.begin_ascending_order(), c.end_ascending_order())   == std::vector<int>{10,20} );
    CHECK( collect(c.begin_descending_order(), c.end_descending_order()) == std::vector<int>{20,10} );
    CHECK( collect(c.begin_side_cross_order(), c.end_side_cross_order()) == std::vector<int>{10,20} );
    CHECK( collect(c.begin_middle_out_order(), c.end_middle_out_order()) == std::vector<int>{20,10} );
}

TEST_CASE("Duplicates in container ordering") {
    MyContainer<int> c;
    for (int x : {3,1,3,2,1}) c.addElement(x);
    // ascending: [1,1,2,3,3]
    CHECK( collect(c.begin_ascending_order(), c.end_ascending_order())
           == std::vector<int>{1,1,2,3,3} );
    // side-cross: [1,3,1,3,2]
    CHECK( collect(c.begin_side_cross_order(), c.end_side_cross_order())
           == std::vector<int>{1,3,1,3,2} );
}

TEST_CASE("Iterator copy semantics") {
    MyContainer<int> c;
    for (int x : {5,4,3}) c.addElement(x);
    auto itA = c.begin_ascending_order();
    auto itB = itA;        // copy
    CHECK(*itA == 3);
    CHECK(*itB == 3);
    ++itA;
    CHECK(*itA == 4);
    // itB still at original
    CHECK(*itB == 3);
}

TEST_CASE("Container copy independence") {
    MyContainer<int> a;
    a.addElement(1);
    a.addElement(2);
    MyContainer<int> b = a;        // copy
    b.removeElement(1);
    // 'a' must remain unchanged
    CHECK( a.size() == 2 );
    CHECK( b.size() == 1 );
    CHECK( collect(a.begin_order(), a.end_order()) == std::vector<int>{1,2} );
}

TEST_CASE("Streaming large ints") {
    MyContainer<long> c;
    for (long x : {1000000000L, -42L}) c.addElement(x);
    std::ostringstream os;
    os << c;
    // prints "[ 1000000000 -42 ]"
    CHECK( os.str() == "[ 1000000000 -42 ]" );
}

TEST_CASE("3-element container ordering") {
    MyContainer<int> c;
    for (int x : {9,3,5}) c.addElement(x);

    // insertion
    CHECK( collect(c.begin_order(), c.end_order()) ==
           std::vector<int>{9,3,5} );

    // ascending / descending
    CHECK( collect(c.begin_ascending_order(), c.end_ascending_order()) ==
           std::vector<int>{3,5,9} );
    CHECK( collect(c.begin_descending_order(), c.end_descending_order()) ==
           std::vector<int>{9,5,3} );

    // side-cross: smallest, largest, middle
    CHECK( collect(c.begin_side_cross_order(), c.end_side_cross_order()) ==
           std::vector<int>{3,9,5} );

    // reverse
    CHECK( collect(c.begin_reverse_order(), c.end_reverse_order()) ==
           std::vector<int>{5,3,9} );

    // middle-out (odd): middle index 1, then left, then right
    CHECK( collect(c.begin_middle_out_order(), c.end_middle_out_order()) ==
           std::vector<int>{3,9,5} );
}

TEST_CASE("6-element container ordering") {
    MyContainer<int> c;
    for (int x : {10,20,30,40,50,60}) c.addElement(x);

    // insertion & ascending (already sorted)
    std::vector<int> ins{10,20,30,40,50,60};
    CHECK( collect(c.begin_order(),   c.end_order())   == ins );
    CHECK( collect(c.begin_ascending_order(), c.end_ascending_order()) == ins );

    // descending
    CHECK( collect(c.begin_descending_order(), c.end_descending_order()) ==
           std::vector<int>{60,50,40,30,20,10} );

    // side-cross
    CHECK( collect(c.begin_side_cross_order(), c.end_side_cross_order()) ==
           std::vector<int>{10,60,20,50,30,40} );

    // reverse
    CHECK( collect(c.begin_reverse_order(), c.end_reverse_order()) ==
           std::vector<int>{60,50,40,30,20,10} );

    // middle-out (even): mid index = 3
    CHECK( collect(c.begin_middle_out_order(), c.end_middle_out_order()) ==
           std::vector<int>{40,30,50,20,60,10} );
}

TEST_CASE("Dynamic add/remove affects all iterators") {
    MyContainer<int> c;
    c.addElement(5);
    c.addElement(1);
    c.addElement(3);
    // after first adds
    CHECK( collect(c.begin_ascending_order(), c.end_ascending_order()) ==
           std::vector<int>{1,3,5} );

    // remove middle element
    c.removeElement(3);
    CHECK( collect(c.begin_order(), c.end_order()) ==
           std::vector<int>{5,1} );

    // add another
    c.addElement(2);
    CHECK(c.size() == 3);
    CHECK( collect(c.begin_descending_order(), c.end_descending_order()) ==
           std::vector<int>{5,2,1} );
}

TEST_CASE("Iterator increment to end") {
    MyContainer<int> c;
    c.addElement(42);
    auto it = c.begin_order();
    CHECK(*it == 42);
    ++it;
    CHECK(it == c.end_order());
}
TEST_CASE("Boolean container ordering") {
    MyContainer<bool> cb;
    cb.addElement(true);
    cb.addElement(false);
    cb.addElement(true);
    // insertion: [true,false,true]
    CHECK( collect(cb.begin_order(), cb.end_order()) ==
           std::vector<bool>{true,false,true} );
    // ascending: false before true
    CHECK( collect(cb.begin_ascending_order(), cb.end_ascending_order()) ==
           std::vector<bool>{false,true,true} );
    // descending: true before false
    CHECK( collect(cb.begin_descending_order(), cb.end_descending_order()) ==
           std::vector<bool>{true,true,false} );
}

TEST_CASE("Dereference end() throws out_of_range") {
    MyContainer<int> c; 
    c.addElement(1);
    auto it = c.begin_order();
    ++it; // now it == end_order()
    CHECK(it == c.end_order());
    // operator* uses at(), so dereferencing end() should throw
    CHECK_THROWS_AS((*it), std::out_of_range);

    // test for another iterator type
    auto sit = c.begin_side_cross_order();
    ++sit;
    CHECK(sit == c.end_side_cross_order());
    CHECK_THROWS_AS((*sit), std::out_of_range);
}

TEST_CASE("Floating‐point precision ordering") {
    MyContainer<double> cf;
    cf.addElement(1.0000001);
    cf.addElement(1.0);
    cf.addElement(0.9999999);
    // ascending: smallest first
    auto vf = collect(cf.begin_ascending_order(), cf.end_ascending_order());
    std::vector<double> expf{0.9999999,1.0,1.0000001};
    CHECK(vf == expf);
}

TEST_CASE("Lexicographical string stress‐test") {
    MyContainer<std::string> cs;
    std::vector<std::string> words = {
        "apple","apricot","banana","banana","cherry","date","elderberry"
    };
    for (auto &w : words) cs.addElement(w);
    // ascending = sorted lex (duplicates too)
    auto vs = collect(cs.begin_ascending_order(), cs.end_ascending_order());
    std::sort(words.begin(), words.end());
    CHECK(vs == words);
}

TEST_CASE("Random‐data consistency check") {
    MyContainer<int> cr;
    std::vector<int> rnd;
    for(int i=0; i<100; ++i) {
        int x = std::rand() % 1000;
        cr.addElement(x);
        rnd.push_back(x);
    }
    auto sorted = rnd;
    std::sort(sorted.begin(), sorted.end());
    auto vr = collect(cr.begin_ascending_order(), cr.end_ascending_order());
    CHECK(vr == sorted);
}

TEST_CASE("Range‐based for loops") {
    MyContainer<int> c;
    for (int i = 5; i > 0; --i) c.addElement(i);
    // emulate range‐based for over ascending iterator
    std::vector<int> got;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        got.push_back(*it);
    }
    std::vector<int> exp{1,2,3,4,5};
    CHECK(got == exp);
}

TEST_CASE("Container copy remains independent") {
    MyContainer<int> a;
    for(int i: {1,2,3}) a.addElement(i);
    MyContainer<int> b = a;      // shallow copy of data vector
    b.removeElement(2);
    // a still has 2, b doesn’t
    CHECK( collect(a.begin_order(), a.end_order()) == std::vector<int>{1,2,3} );
    CHECK( collect(b.begin_order(), b.end_order()) == std::vector<int>{1,3} );
}