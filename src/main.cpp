// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "train.h"

int main() {
  std::ofstream fout("results.csv");
  fout << "n,Scenario,Steps,Time\n";

  std::srand(static_cast<unsigned>(std::time(nullptr)));

  for (int n = 10; n <= 200; n += 10) {
    for (int mode = 0; mode < 3; ++mode) {
      std::vector<bool> lights(n);
      if (mode == 0) {
        std::fill(lights.begin(), lights.end(), false);
      } else if (mode == 1) {
        std::fill(lights.begin(), lights.end(), true);
      } else {
        for (int i = 0; i < n; ++i)
          lights[i] = std::rand() % 2;
      }

      Train train;
      for (bool l : lights)
        train.addCar(l);

      auto start = std::chrono::high_resolution_clock::now();
      train.getLength();
      auto stop = std::chrono::high_resolution_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0;

      std::string scenario = (mode == 0 ? "off" : (mode == 1 ? "on" : "random"));
      fout << n << "," << scenario << "," << train.getOpCount() << "," << ms << "\n";
    }
  }

  fout.close();
  return 0;
}
