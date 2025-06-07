// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "train.h"

struct ExperimentResult
{
    int n;
    long long time_us;
    int operations;
};

std::vector<ExperimentResult> run_experiment(int condition)
{
    std::vector<ExperimentResult> results;
    std::vector<int> ns = {2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000};

    for (int n : ns)
    {
        Train train;

        if (condition == 0)
        {
            for (int i = 0; i < n; i++)
                train.addCar(false);
        }
        else if (condition == 1)
        {
            for (int i = 0; i < n; i++)
                train.addCar(true);
        }
        else
        {
            for (int i = 0; i < n; i++)
                train.addCar(rand() % 2);
        }

        int length = train.getLength();

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; ++i)
            train.getLength();
        auto end = std::chrono::high_resolution_clock::now();

        ExperimentResult res;
        res.n          = n;
        res.time_us    = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        res.operations = train.getOpCount();
        results.push_back(res);

        std::cout << "n=" << n
                  << ", length=" << length
                  << ", time=" << res.time_us << " mcs"
                  << ", ops=" << res.operations
                  << std::endl;
    }

    return results;
}

int main()
{
    std::ofstream csv_file("results.csv");
    csv_file << "n,condition,time_us,operations\n";

    auto results_off = run_experiment(0);
    for (const auto &res : results_off)
        csv_file << res.n << ",0," << res.time_us << "," << res.operations << "\n";

    auto results_on = run_experiment(1);
    for (const auto &res : results_on)
        csv_file << res.n << ",1," << res.time_us << "," << res.operations << "\n";

    auto results_rand = run_experiment(2);
    for (const auto &res : results_rand)
        csv_file << res.n << ",2," << res.time_us << "," << res.operations << "\n";

    csv_file.close();
    return 0;
}
