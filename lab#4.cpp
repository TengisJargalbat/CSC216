#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

std::vector<int> worstShuffle(std::vector<int> array) {
    std::vector<int> copy{};
    int n = array.size();
    std::srand(std::time(0));

  // While there remain elements to shuffle…
    while (n) {

    // Pick a remaining element…
        int i = std::rand() % array.size();

    // If not already shuffled, move it to the new array.
        if (std::find(array.begin(), array.end(), array[i]) != array.end()) {
            copy.push_back(array[i]);
            auto newEnd = std::remove(array.begin(), array.end(), array[i]);
            array.erase(newEnd, array.end());
            n--;
        }
    }

  return copy;
}

std::vector<int> betterShuffle(std::vector<int> array) {
    std::vector<int> copy{};
    int n = array.size();
    std::srand(std::time(0));

  // While there remain elements to shuffle…
    while (n) {

    // Pick a remaining element…
        int i = std::rand() % n--;
        copy.push_back(array[i]);
        auto newEnd = std::remove(array.begin(), array.end(), array[i]);
        array.erase(newEnd, array.end());
    }

  return copy;
}

std::vector<int> bestShuffle(std::vector<int> array) {
    int n = array.size();
    std::srand(std::time(0));

    while (n) {

        int i = std::rand() % n--;
        int t = array[n];
        array[n] = array[i];
        array[i] = t;
    }

  return array;
}

static const std::vector<int> arr1 = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

static const std::vector<int> arr2 = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25
};

static const std::vector<int> arr3 = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50
};

static const std::vector<int> arr4 = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,
    51,52,53,54,55,56,57,58,59,60,
    61,62,63,64,65,66,67,68,69,70,
    71,72,73,74,75,76,77,78,79,80,
    81,82,83,84,85,86,87,88,89,90,
    91,92,93,94,95,96,97,98,99,100
};

template <typename Functor>
long long measureShuffleTime(const std::vector<int>& source, Functor func) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    std::vector<int> result = func(source);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    std::vector<std::vector<int>> allArrays = {arr1, arr2, arr3, arr4};
    std::vector<std::string> arrayNames = {"arr1(10)", "arr2(25)", "arr3(50)", "arr4(100)"};

    int trialCount = 4;

    for (int i = 0; i < (int)allArrays.size(); i++) {
        const auto& currentArray = allArrays[i];
        std::cout << "=== Testing " << arrayNames[i] << " ===\n";

        for (int trial = 1; trial <= trialCount; ++trial) {
            long long worstTime  = measureShuffleTime(currentArray, worstShuffle);
            long long betterTime = measureShuffleTime(currentArray, betterShuffle);
            long long bestTime   = measureShuffleTime(currentArray, bestShuffle);

            std::cout << "Trial " << trial << ":\n"
                      << "  worstShuffle:  " << worstTime  << " µs\n"
                      << "  betterShuffle: " << betterTime << " µs\n"
                      << "  bestShuffle:   " << bestTime   << " µs\n\n";
        }

        std::cout << "---------------------------------------------\n\n";
    }

    return 0;
}
