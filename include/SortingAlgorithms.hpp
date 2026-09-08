/**
 * @file SortingAlgorithms.hpp
 * @author A01648827
 * @brief Library that defines different algorithms for sorting values
 * @date 2026-09-05
 */

#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALTORITHMS_HPP

#include <vector>

/**
 * @brief Sorts the data in ascending order using the Bubble sort method.
 * Complexity: O(n^2)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void bubbleSort(std::vector<T>& arr) {
    int size = arr.size();
    bool swapped = true;

    for (int i = 0; i < size - 1 && swapped; i++) {
        swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // swap
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
    }
}

/**
 * @brief Sorts the data in ascending order using the Selection sort method.
 * Complexity: O(n^2)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void selectionSort(std::vector<T>& arr) {
    int size = arr.size();

    for (int i = 0; i < size - 1; i++) {
        int minPos = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minPos])
                minPos = j;
        }

        // swap
        T temp = arr[i];
        arr[i] = arr[minPos];
        arr[minPos] = temp;
    }
}

/**
 * @brief Sorts the data in ascending order using the Insertion sort method.
 * Complexity: O(n^2)
 *
 * @tparam T any comparable data type
 * @param arr A vector<T> with the n values to sort
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void insertionSort(std::vector<T>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        T key = arr[i];

        int j = i - 1;
        for (; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

#endif  // SORTING_ALGORITHMS_HPP