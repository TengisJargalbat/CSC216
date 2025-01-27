#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    int numSteps = 10;
    int numTrials = 10;
    int currentPosition = 0;
    int finalPositions[numTrials];
    srand(time(0)); 

    for (int i = 0; i < numTrials; i++) {
        currentPosition = 0;
        for (int j = 0; j < numSteps; j++) {
            int randNum = rand() % 2;
            if (randNum == 1) {
                currentPosition++;
            } else {
                currentPosition--;
            }
        }
        finalPositions[i] = currentPosition;
    }

    for (int i = 0; i < numTrials; i++) {
        std::cout << "Trial " << i + 1 << " Final Position: " << finalPositions[i] << "\n";
    }

    std::cout << "Number of Steps (N): " << numSteps << "\nNumber of Trials (M): " << numTrials << "\n";
    return 0;
}
