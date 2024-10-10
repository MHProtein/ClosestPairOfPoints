#pragma once
#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <functional>
#include <vector>

template<class T>
class InsertionSort
{
public:
    static void Sort(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp = std::less<T>{});
    static void Sort(std::vector<T>& vec , std::function<bool(const T& lhs, const T& rhs)> comp = std::less<T>{});
};

template <class T>
void InsertionSort<T>::Sort(std::vector<T>& vec, int low, int high, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    for(int i = low + 1; i < high + 1; ++i)
    {
        T temp = std::move(vec[i]);

        int j;
        for(j = i; j > 0 && comp(temp, vec[j - 1]); --j)
            vec[j] = std::move(vec[j - 1]);
        vec[j] = std::move(temp);
    }
}

template <class T>
void InsertionSort<T>::Sort(std::vector<T>& vec, std::function<bool(const T& lhs, const T& rhs)> comp)
{
    Sort(vec, 0, vec.size() - 1, comp);
}

#endif
