/**
 * @file SortingAlgorithms.hpp
 * @author Team 1
 * @brief Library that defines different algorithms for sorting values
 * @date 2026-09-21
 */

#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

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
 * @param arr a vector<T> with the n values to sort
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

// Merge Sort
/**
 * @brief Function that implements the merge logic of Merge sort algorithm
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 * @param lo an int parameter that specifies the lowest index of the current window
 * @param hi an int parameter that specifies the highest index of the current window
 * @param mid an int parameter that specifies the mid point of the current window
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void merge(std::vector<T>& arr, int lo, int hi, int mid) {
    std::vector<T> temp;

    // Merge the elements
    int i = lo;
    int j = mid + 1;
    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Add the remaining elements of the firt half
    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    // Add the remaining elements of the second half
    while (j <= hi) {
        temp.push_back(arr[j]);
        j++;
    }

    // Reassign the sorted elements from temp vector
    for (int i = lo; i <= hi; i++) {
        arr[i] = temp[i - lo];
    }
}

/**
 * @brief Sorts the data in ascending order using the Merge sort method.
 * Complexity: O(nlogn)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 * @param lo an int parameter that specifies the lowest index of the current window
 * @param hi an int parameter that specifies the highest index of the current window
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void mergeSort(std::vector<T>& arr, int lo, int hi) {
    // Already sorted
    if (lo >= hi)
        return;

    // Split the array
    int mid = (lo + hi) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);

    // Merge the arrays
    merge(arr, lo, hi, mid);
}

/**
 * @brief Sorts the data in ascending order using the Merge sort method.
 * Complexity: O(nlogn)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void mergeSort(std::vector<T>& arr) {
    if (!arr.size())
        return;
    mergeSort(arr, 0, arr.size() - 1);
}

// Quick Sort
/**
 * @brief Implementation of Lomuto partition algorithm with the pivot at the start.
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 * @param lo an int parameter that specifies the lowest index of the current window
 * @param hi an int parameter that specifies the highest index of the current window
 *
 * @return int the index of the current pivot
 *
 * @pre The vector<T> must contain the n values
 */
template <typename T>
int partition(std::vector<T>& arr, int lo, int hi) {
    // Lomuto with the pivot at the start
    T pivot = arr[lo];
    int i = lo + 1;

    for (int j = i; j <= hi; j++) {
        if (arr[j] <= pivot) {
            // Swap
            T temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
        }
    }

    // Swap the pivot
    arr[lo] = arr[i - 1];
    arr[i - 1] = pivot;
    return i - 1;
}

/**
 * @brief Sorts the data in ascending order using the Quick sort method.
 * Complexity: O(nlogn) or in the worst case O(n^2)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 * @param lo an int parameter that specifies the lowest index of the current window
 * @param hi an int parameter that specifies the highest index of the current window
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void quickSort(std::vector<T>& arr, int lo, int hi) {
    // Already sorted
    if (lo >= hi)
        return;

    int p = partition(arr, lo, hi);
    quickSort(arr, lo, p - 1);
    quickSort(arr, p + 1, hi);
}

/**
 * @brief Sorts the data in ascending order using the Quick sort method.
 * Complexity: O(nlogn) or in the worst case O(n^2)
 *
 * @tparam T any comparable data type
 * @param arr a vector<T> with the n values to sort
 *
 * @pre The vector<T> must contain the n values
 * @post The vector<T> will contain the data already sorted
 */
template <typename T>
void quickSort(std::vector<T>& arr) {
    if (!arr.size())
        return;
    quickSort(arr, 0, arr.size() - 1);
}

#endif  // SORTING_ALGORITHMS_HPP