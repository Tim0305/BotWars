/**
 * @file SortingAlgorithms.hpp
 * @author Team 1
 * @brief Library that defines different algorithms for sorting values
 * @date 2026-09-10
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

/**
 * @brief Helper function for QuickSort that partitions the vector around a pivot element.
 * Complexity: O(n)
 *
 * @tparam T Any comparable data type (supports operator <).
 * @param arr A vector<T> reference containing elements to partition.
 * @param low Starting index of the subarray to partition.
 * @param high Ending index of the subarray to partition (used as pivot index).
 *
 * @pre 0 <= low <= high < arr.size().
 * @post Elements smaller than the pivot are placed to its left, and larger elements to its right.
 * @return int The final index position of the pivot element.
 */
template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = high;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * @brief Helper function that handles recursive QuickSort calls over a range [low, high].
 * Complexity: Average O(n log n), Worst Case O(n^2)
 *
 * @tparam T Any comparable data type.
 * @param arr A vector<T> reference to be sorted.
 * @param low Starting index of the current subarray.
 * @param high Ending index of the current subarray.
 *
 * @pre Valid bounds 'low' and 'high' within the range [0, arr.size() - 1].
 * @post The section arr[low...high] will be sorted in ascending order.
 * @return void
 */
template <typename T>
void quickSortHelper(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

/**
 * @brief Sorts the data in ascending order using the Quick sort method.
 * Complexity: Average O(n log n), Worst Case O(n^2)
 *
 * @tparam T Any comparable data type.
 * @param arr A vector<T> reference containing the n values to sort.
 *
 * @pre The vector<T> must contain valid elements.
 * @post The vector<T> will be sorted in non-decreasing order in-place.
 * @return void
 */
template <typename T>
void quickSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

/**
 * @brief Helper function for MergeSort that merges two sorted contiguous subarrays into one.
 * Subarray 1: arr[left ... mid]
 * Subarray 2: arr[mid+1 ... right]
 * Complexity: O(n)
 *
 * @tparam T Any comparable data type (supports operator <=).
 * @param arr A vector<T> reference containing the subarrays to merge.
 * @param left Lower bound index of the first subarray.
 * @param mid Upper bound index of the first subarray.
 * @param right Upper bound index of the second subarray.
 *
 * @pre 0 <= left <= mid < right < arr.size(), and both subarrays are already sorted.
 * @post The section arr[left...right] is merged and fully sorted.
 * @return void
 */
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Helper function that performs recursive Divide and Conquer for MergeSort.
 * Complexity: O(n log n)
 *
 * @tparam T Any comparable data type.
 * @param arr A vector<T> reference to be sorted.
 * @param left Starting index of the current range.
 * @param right Ending index of the current range.
 *
 * @pre Valid bounds 'left' and 'right' within the range [0, arr.size() - 1].
 * @post The section arr[left...right] will be sorted in ascending order.
 * @return void
 */
template <typename T>
void mergeSortHelper(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/**
 * @brief Sorts the data in ascending order using the Merge sort method.
 * Complexity: O(n log n) in all cases (Worst, Average, Best)
 *
 * @tparam T Any comparable data type.
 * @param arr A vector<T> reference containing the n values to sort.
 *
 * @pre The vector<T> must contain valid elements.
 * @post The vector<T> will be sorted in non-decreasing order in-place.
 * @return void
 */
template <typename T>
void mergeSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

#endif  // SORTING_ALGORITHMS_HPP