#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include "Point.hpp"
#include "cmath"

class AStar
{
    private:
        int _N;
        int** _Data;
        double (*_Heuristics)(Point p1, Point p2);
        Point _EmptyPos = {0, 0, 0};
        Point* _NumPos;

    // Singleton design
    private:
        AStar(int n, int** data, const std::string& heuristics);

    public:
        static AStar& GetInstance(int n, int** data, const std::string& heuristics="manhattan")
        {
            static AStar instance(n, data, heuristics);

            return instance;
        }
        AStar(const AStar&) = delete;
        void operator=(const AStar&) = delete;
        ~AStar() {}

    // Metrics
    public:
        static double ManhattanMetric(Point p, Point goal);

    // Algorithm
    public:
        bool CheckData() const;
        void RunAlgo();
        void ShiftData();
        bool CopyData(int**& Array, int swap_id, bool is_done=true);
//        int GetMatrixHeuristic(int** Array);
};

