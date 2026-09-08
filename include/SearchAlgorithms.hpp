/**
 * @file SearchAlgorithms.hpp
 * @author A01648827
 * @brief Library that defines sequential and binary search algorithms
 * @date 2026-09-05
 */

#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

#include <vector>

/**
 * @brief Value that the function returns when the searched value is not found
 */
inline constexpr int NOT_FOUND = -1;

/**
 * @brief Searches for a value within the vector using sequential search.
 * Complexity: O(n)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> (the search space)
 * @param target value of type T to search for
 * @return int the index where the value is found, or NOT_FOUND if it is not located
 *
 * @pre The vector<T> must contain the n values
 */
template <typename T>
int sequentialSearch(const std::vector<T>& arr, const T& target) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == target)
            return i;

    return NOT_FOUND;
}

/**
 * @brief Searches for a value within the vector using binary search.
 * Complexity: O(logn)
 *
 * @tparam T any comparable data type
 * @param arr a sorted vector<T> (the search space)
 * @param target value of type T to search for
 * @return int the index where the value is found, or NOT_FOUND if it is not located
 *
 * @pre The vector<T> must contain the n values sorted in ascending order
 */
template <typename T>
int binarySearch(const std::vector<T>& arr, const T& target) {
    int l = 0;
    int r = arr.size() - 1;
    int mid = 0;

    while (l <= r) {
        mid = (l + r) / 2;
        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return NOT_FOUND;
}

#endif  // SEARCH_ALGORITHMS_HPP
