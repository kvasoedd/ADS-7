// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <cstdint>
#include <string>
#include "train.h"

int main() {
  std::cout << "Scenario,n,AvgSteps,AvgTimeMicrosec\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution dist(0.5);

  for (int scenario = 0; scenario < 3; ++scenario) {
    std::string scenarioName;
    if (scenario == 0) {
      scenarioName = "AllOff";
    } else if (scenario == 1) {
      scenarioName = "AllOn";
    } else {
      scenarioName = "Random";
    }

    for (int n = 5; n <= 100; n += 5) {
      int64_t totalSteps = 0;
      int64_t totalTime = 0;
      int runs = 10;

      for (int i = 0; i < runs; ++i) {
        Train train;
        for (int j = 0; j < n; ++j) {
          bool light = false;
          if (scenario == 1) {
            light = true;
          } else if (scenario == 2) {
            light = dist(gen);
          }
          train.addCar(light);
        }

        auto start =
            std::chrono::high_resolution_clock::now();
        train.getLength();
        auto end =
            std::chrono::high_resolution_clock::now();

        totalSteps += train.getOpCount();
        totalTime +=
            std::chrono::duration_cast<
                std::chrono::microseconds>(end - start)
                .count();
      }

      double avgSteps = static_cast<double>(totalSteps) / runs;
      double avgTime = static_cast<double>(totalTime) / runs;

      std::cout << scenarioName << "," << n << ","
                << avgSteps << "," << avgTime << "\n";
    }
  }

  return 0;
}
