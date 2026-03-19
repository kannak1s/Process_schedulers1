#ifndef SORT_ALGORITHMS_HPP
#define SORT_ALGORITHMS_HPP

#include <cstdint>
#include <utility>   // for std::swap

// Forward declaration of container
template<typename T>
class row;


/* =========================
   BUBBLE SORT
   ========================= */
template<typename T>
void bubble_sort(row<T>& s)
{
    uint32_t n = s.size();

    for (uint32_t i = 0; i < n - 1; ++i)
        for (uint32_t j = 0; j < n - i - 1; ++j)
            if (s[j] > s[j + 1])
                std::swap(s[j], s[j + 1]);
}


/* =========================
   SELECTION SORT
   ========================= */
template<typename T>
void selection_sort(row<T>& s)
{
    uint32_t n = s.size();

    for (uint32_t i = 0; i < n - 1; ++i) {
        uint32_t min_idx = i;

        for (uint32_t j = i + 1; j < n; ++j)
            if (s[j] < s[min_idx])
                min_idx = j;

        std::swap(s[i], s[min_idx]);
    }
}


/* =========================
   INSERTION SORT
   ========================= */
template<typename T>
void insertion_sort(row<T>& s)
{
    uint32_t n = s.size();

    for (uint32_t i = 1; i < n; ++i) {
        T key = s[i];
        int32_t j = i - 1;

        while (j >= 0 && s[j] > key) {
            s[j + 1] = s[j];
            --j;
        }

        s[j + 1] = key;
    }
}


/* =========================
   MERGE SORT
   ========================= */

template<typename T>
void merge(row<T>& s, uint32_t left, uint32_t mid, uint32_t right)
{
    uint32_t n1 = mid - left + 1;
    uint32_t n2 = right - mid;

    T* L = new T[n1];
    T* R = new T[n2];

    for (uint32_t i = 0; i < n1; ++i)
        L[i] = s[left + i];

    for (uint32_t j = 0; j < n2; ++j)
        R[j] = s[mid + 1 + j];

    uint32_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            s[k++] = L[i++];
        else
            s[k++] = R[j++];
    }

    while (i < n1)
        s[k++] = L[i++];

    while (j < n2)
        s[k++] = R[j++];

    delete[] L;
    delete[] R;
}

template<typename T>
void merge_sort_recursive(row<T>& s, uint32_t left, uint32_t right)
{
    if (left < right) {
        uint32_t mid = left + (right - left) / 2;

        merge_sort_recursive(s, left, mid);
        merge_sort_recursive(s, mid + 1, right);
        merge(s, left, mid, right);
    }
}

template<typename T>
void merge_sort(row<T>& s)
{
    if (s.size() > 1)
        merge_sort_recursive(s, 0, s.size() - 1);
}


/* =========================
   QUICK SORT
   ========================= */

template<typename T>
int partition(row<T>& s, int low, int high)
{
    T pivot = s[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (s[j] < pivot) {
            ++i;
            std::swap(s[i], s[j]);
        }
    }

    std::swap(s[i + 1], s[high]);
    return i + 1;
}

template<typename T>
void quick_sort_recursive(row<T>& s, int low, int high)
{
    if (low < high) {
        int pi = partition(s, low, high);

        quick_sort_recursive(s, low, pi - 1);
        quick_sort_recursive(s, pi + 1, high);
    }
}

template<typename T>
void quick_sort(row<T>& s)
{
    if (s.size() > 1)
        quick_sort_recursive(s, 0, s.size() - 1);
}

/* =========================
   ENUMERATION SORT (RANK SORT)
   ========================= */

template<typename T>
void enumeration_sort(row<T>& s)
{
    uint32_t n = s.size();

    if (n <= 1)
        return;

    T* temp = new T[n];

    for (uint32_t i = 0; i < n; ++i) {

        uint32_t rank = 0;

        for (uint32_t j = 0; j < n; ++j) {

            if (s[j] < s[i])
                ++rank;

            // Handle duplicates safely
            if (s[j] == s[i] && j < i)
                ++rank;
        }

        temp[rank] = s[i];
    }

    for (uint32_t i = 0; i < n; ++i)
        s[i] = temp[i];

    delete[] temp;
}
#endif
