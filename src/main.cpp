// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "train.h"

int main() {
    const int minN = 2;
    const int maxN = 100;
    const int numRepetitions = 10;

    std::ofstream outOps("ops.txt");
    std::ofstream outTime("time.txt");

    outOps << "n,all_off,all_on,avg_rand\n";
    outTime << "n,all_off,all_on,avg_rand\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    for (int n = minN; n <= maxN; ++n) {
        Train trainOff;
        for (int i = 0; i < n; ++i) {
            trainOff.addCar(false);
        }
        auto startOff = std::chrono::high_resolution_clock::now();
        trainOff.getLength();
        auto endOff = std::chrono::high_resolution_clock::now();
        int opsOff = trainOff.getOpCount();
        auto durationOff = std::chrono::duration_cast<std::chrono::microseconds>(endOff - startOff).count();

        Train trainOn;
        for (int i = 0; i < n; ++i) {
            trainOn.addCar(true);
        }
        auto startOn = std::chrono::high_resolution_clock::now();
        trainOn.getLength();
        auto endOn = std::chrono::high_resolution_clock::now();
        int opsOn = trainOn.getOpCount();
        auto durationOn = std::chrono::duration_cast<std::chrono::microseconds>(endOn - startOn).count();

        double avgOpsRand = 0.0;
        double avgTimeRand = 0.0;
        for (int rep = 0; rep < numRepetitions; ++rep) {
            Train trainRand;
            for (int i = 0; i < n; ++i) {
                trainRand.addCar(distrib(gen) == 1);
            }
            auto startRand = std::chrono::high_resolution_clock::now();
            trainRand.getLength();
            auto endRand = std::chrono::high_resolution_clock::now();
            avgOpsRand += trainRand.getOpCount();
            avgTimeRand += std::chrono::duration_cast<std::chrono::microseconds>(endRand - startRand).count();
        }
        avgOpsRand /= numRepetitions;
        avgTimeRand /= numRepetitions;

        outOps << n << "," << opsOff << "," << opsOn << "," << avgOpsRand << "\n";
        outTime << n << "," << durationOff << "," << durationOn << "," << avgTimeRand << "\n";
        
        std::cout << "Completed n = " << n << std::endl;
    }

    outOps.close();
    outTime.close();
    return 0;
}
