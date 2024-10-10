#pragma once
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <functional>
#include <vector>

#include "InsertionSort.h"

template<class T>
class QuickSort
{
public:
    static void Sort(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp = std::less<T>{});
    static void Sort(std::vector<T>& vec, std::function<bool(const T& lhs, const T& rhs)> comp = std::less<T>{});

private:
    static int Partition(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp);
    static T& MedianOf3(std::vector<T>& vec, int low, int middle, int high, std::function<bool(const T& lhs, const T& rhs)> comp);
    static void SortRecursion(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp);
    
};

template <class T>
void QuickSort<T>::Sort(std::vector<T>& vec, std::function<bool (const T& lhs, const T& rhs)> comp)
{
    Sort(vec, 0, vec.size() - 1, comp);
}

template <class T>
void QuickSort<T>::Sort(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    SortRecursion(vec, low, high, comp);
}

template <class T>
void QuickSort<T>::SortRecursion(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    if(high - low < 10)
    {
        InsertionSort<T>::Sort(vec, low, high, comp);
        return;
    }
    int i = Partition(vec, low, high, comp);
    
    SortRecursion(vec, low, i - 1, comp);
    SortRecursion(vec, i + 1, high, comp);
}

template <class T>
int QuickSort<T>::Partition(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    int middle = (high + low) / 2;
    const auto& pivot = MedianOf3(vec, low, middle, high, comp);

    int i = low;
    int j = high - 1;
    
    for(;;)
    {
        while (comp(vec[++i], pivot)) { }
        while (comp(pivot, vec[--j])) { }
        if(i < j)
            std::swap(vec[i], vec[j]);
        else
            break;
    }

    std::swap(vec[i], vec[high - 1]);

    return i;
}

template <class T>
T& QuickSort<T>::MedianOf3(std::vector<T>& vec, int low, int middle, int high, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    if(comp(vec[middle], vec[low]))
        std::swap(vec[low], vec[middle]);
    if(comp(vec[high], vec[low]))
        std::swap(vec[high], vec[low]);
    if(comp(vec[high], vec[middle]))
        std::swap(vec[high], vec[middle]);

    std::swap(vec[high - 1], vec[middle]);

    return vec[high - 1];
}

#endif
