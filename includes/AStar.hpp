#pragma once

#include <string>
#include <iostream>
#include "Point.hpp"
#include "cmath"

class AStar
{
    private:
        int _N;
        int** _Data;
        double (*_Heuristics)(Point p1, Point p2);
    // Singleton design
    private:
        AStar(int n, int** data, std::string heuristics);

    public:
        static AStar& getInstance(int n, int** data, std::string heuristics="manhattan")
        {
            static AStar instance(n, data, heuristics);

            return instance;
        }
        AStar(const AStar&) = delete;
        void operator=(const AStar&) = delete;
        ~AStar() {}

    // Metrics
    public:
        static double manhattan_metric(Point p, Point goal);

    // Algorithm
    public:
        bool check_data() const;
        void run_algo();
};
