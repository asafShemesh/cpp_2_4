// asaf0604@gmail.com   325362457
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "my_container.hpp"
#include <stdexcept>
#include <vector>

using namespace ariel;

/**
 * Test basic add and remove functionality.
 * Verifies that elements are added correctly,
 * removed correctly, and that removing a non-existent
 * element throws an exception.
 */
TEST_CASE("Add and remove elements")
{
    MyContainer<int> c;
    CHECK(c.size() == 0);

    c.addElement(5);
    c.addElement(10);
    c.addElement(15);
    CHECK(c.size() == 3);

    c.removeElement(10);
    CHECK(c.size() == 2);

    // Expect exception when removing a non-existent value
    CHECK_THROWS(c.removeElement(999));
}

/**
 * Test that iterating over an empty container behaves correctly.
 * Specifically, begin and end should be equal.
 */
TEST_CASE("Iterators on empty container")
{
    MyContainer<int> c;
    auto begin = c.begin_ascending_order();
    auto end = c.end_ascending_order();
    CHECK(begin == end);
}

/**
 * Test ascending order iteration.
 * Adds elements in a shuffled order and expects them
 * to be returned in increasing numeric order.
 */
TEST_CASE("Ascending Order")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(2);

    std::vector<int> expected = {1, 2, 3};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it)
        CHECK(*it == expected[i++]);
}

/**
 * Test descending order iteration.
 * Elements should be returned from largest to smallest.
 */
TEST_CASE("Descending Order")
{
    MyContainer<int> c;
    c.addElement(3);
    c.addElement(1);
    c.addElement(2);

    std::vector<int> expected = {3, 2, 1};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it)
        CHECK(*it == expected[i++]);
}

/**
 * Test side-cross iteration.
 * Should return elements by alternating from min and max
 * toward the center of the sorted list.
 * Example: [1, 2, 6, 7, 15] → 1, 15, 2, 7, 6
 */
TEST_CASE("Side Cross Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(15);
    c.addElement(6);
    c.addElement(1);
    c.addElement(2);

    std::vector<int> expected = {1, 15, 2, 7, 6};
    size_t i = 0;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it)
        CHECK(*it == expected[i++]);
}

/**
 * Test reverse order iteration.
 * Should return elements in the reverse of insertion order.
 */
TEST_CASE("Reverse Order")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);

    std::vector<int> expected = {3, 2, 1};
    size_t i = 0;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it)
        CHECK(*it == expected[i++]);
}

/**
 * Test original insertion order iteration.
 * Elements should be returned in the same order they were added.
 */
TEST_CASE("Original Order")
{
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(3);

    std::vector<int> expected = {1, 2, 3};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it)
        CHECK(*it == expected[i++]);
}

/**
 * Test middle-out iteration.
 * Should start from the middle of the sorted list and expand outwards.
 * Example sorted: [1, 2, 6, 7, 15]
 * Expected: 6 (middle), 15 (outer right), 1 (outer left), 7, 2
 */
TEST_CASE("Middle Out Order")
{
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(15);
    c.addElement(6);
    c.addElement(1);
    c.addElement(2);

    std::vector<int> expected = {6, 15, 1, 7, 2};
    size_t i = 0;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it)
        CHECK(*it == expected[i++]);
}
/**
 * Test the get_data() function.
 * This function should return a reference to the internal data vector.
 * We check that the content matches what was inserted.
 */
TEST_CASE("Get Data")
{
    MyContainer<int> c;
    c.addElement(5);
    c.addElement(10);
    c.addElement(15);

    const std::vector<int> &internal = c.get_data();
    CHECK(internal.size() == 3);
    CHECK(internal[0] == 5);
    CHECK(internal[1] == 10);
    CHECK(internal[2] == 15);
}
