#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Rendezes.h"

int main() {
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::srand(seed);
    const int N = 100;
    int array1[N], array2[N];

    for (int i = 0; i < N; i++) {
        int randomValue = std::rand() % 1000;
        array1[i] = randomValue;
        array2[i] = randomValue;
    }

    BubbleSortT<int> bubble;
    QuickSortT<int> quick;

    bubble.sort(array1, N);
    std::cout << "BubbleSortT result:\nSorted array: ";
    for (int i = 0; i < N; i++) {
        std::cout << array1[i] << " ";
    }
    std::cout << "\nTime (ms): " << bubble.getTimeElapsed();
    std::cout << "\nNumber of comparisons: " << bubble.getNumComparisons();
    std::cout << "\nNumber of swaps: " << bubble.getNumSwaps() << "\n\n";

    quick.sort(array2, N);
    std::cout << "QuickSortT result:\nSorted array: ";
    for (int i = 0; i < N; i++) {
        std::cout << array2[i] << " ";
    }
    std::cout << "\nTime (ms): " << quick.getTimeElapsed();
    std::cout << "\nNumber of comparisons: " << quick.getNumComparisons();
    std::cout << "\nNumber of swaps: " << quick.getNumSwaps() << "\n";

    return 0;
}
