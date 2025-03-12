#pragma once

#include <chrono>
#include <vector>

template <class T>
class Sort {
protected:
    virtual bool less(T a, T b) = 0;
    virtual void swap(T& a, T& b) = 0;
public:
    virtual void sort(T* array, int n) = 0;
};

class Statistics {
private:
    double timeElapsed; // in milliseconds
    unsigned int numComparisons, numSwaps;
    std::chrono::high_resolution_clock::time_point startTime;

protected:
    void start();
    void end();
    void init();
    void incComparison();
    void incSwap();

public:
    Statistics();
    double getTimeElapsed();
    unsigned int getNumComparisons();
    unsigned int getNumSwaps();
};

template <class T>
class BubbleSort : public Sort<T> {
protected:
    bool less(T a, T b) override;
    void swap(T& a, T& b) override;
public:
    void sort(T* array, int n) override;
};

template <class T>
class BubbleSortT : public BubbleSort<T>, public Statistics {
protected:
    bool less(T a, T b) override;
    void swap(T& a, T& b) override;
public:
    void sort(T* array, int n) override;
};

template <class T>
class QuickSort : public Sort<T> {
private:
    void qsort(T* a, int left, int right);
    int partition(T* a, int left, int right);
protected:
    bool less(T a, T b) override;
    void swap(T& a, T& b) override;
public:
    void sort(T* array, int n) override;
};

template <class T>
class QuickSortT : public QuickSort<T>, public Statistics {
protected:
    bool less(T a, T b) override;
    void swap(T& a, T& b) override;
public:
    void sort(T* array, int n) override;
};

template <class T>
bool BubbleSort<T>::less(T a, T b)
{
    return a < b;
}

template <class T>
void BubbleSort<T>::swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void BubbleSort<T>::sort(T* array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (!less(array[j], array[j + 1]))
            {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

template <class T>
bool BubbleSortT<T>::less(T a, T b)
{
    incComparison();
    return BubbleSort<T>::less(a, b);
}

template <class T>
void BubbleSortT<T>::swap(T& a, T& b)
{
    incSwap();
    BubbleSort<T>::swap(a, b);
}

template <class T>
void BubbleSortT<T>::sort(T* array, int n)
{
    init();
    start();
    BubbleSort<T>::sort(array, n);
    end();
}

template <class T>
void QuickSort<T>::qsort(T* a, int left, int right)
{
    if (left < right)
    {
        int p = partition(a, left, right);
        qsort(a, left, p);
        qsort(a, p + 1, right);
    }
}

template <class T>
int QuickSort<T>::partition(T* a, int left, int right)
{
    T pivot = a[left];
    int i = left - 1;
    int j = right + 1;
    while (true)
    {
        do { i++; } while (less(a[i], pivot));
        do { j--; } while (less(pivot, a[j]));
        if (i >= j)
            return j;
        swap(a[i], a[j]);
    }
}

template <class T>
bool QuickSort<T>::less(T a, T b)
{
    return a < b;
}

template <class T>
void QuickSort<T>::swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void QuickSort<T>::sort(T* array, int n)
{
    qsort(array, 0, n - 1);
}

template <class T>
bool QuickSortT<T>::less(T a, T b)
{
    incComparison();
    return QuickSort<T>::less(a, b);
}

template <class T>
void QuickSortT<T>::swap(T& a, T& b)
{
    incSwap();
    QuickSort<T>::swap(a, b);
}

template <class T>
void QuickSortT<T>::sort(T* array, int n)
{
    init();
    start();
    QuickSort<T>::sort(array, n);
    end();
}

Statistics::Statistics()
    : timeElapsed(0), numComparisons(0), numSwaps(0)
{
}

void Statistics::start()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Statistics::end()
{
    timeElapsed = std::chrono::duration<double, std::milli>(
        std::chrono::high_resolution_clock::now() - startTime
    ).count();
}

void Statistics::init()
{
    timeElapsed = 0;
    numComparisons = 0;
    numSwaps = 0;
}

void Statistics::incComparison()
{
    numComparisons++;
}

void Statistics::incSwap()
{
    numSwaps++;
}

double Statistics::getTimeElapsed()
{
    return timeElapsed;
}

unsigned int Statistics::getNumComparisons()
{
    return numComparisons;
}

unsigned int Statistics::getNumSwaps()
{
    return numSwaps;
}
