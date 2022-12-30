#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
#include <set>
#include <random>
#include "Point.hpp"
#include "cmath"

class AStar
{
    private:
        int _N;
        int** _Data;
        float (*_Heuristics)(Point p1, Point p2);
        Point _EmptyPos = {-1, -1, 0};
        Point* _NumPos;
        std::set<int**> _History;
        int** _OriginalData;
        Point _OriginalEmptyPos;

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
        static float ManhattanMetric(Point p, Point goal);
        static float EuclidianMetric(Point p, Point goal);

    // Algorithm
    public:
        bool CheckBoard();
        bool CheckData() const;
        void RunAlgo();
        int GetInversionsCount(const int* Array) const;
        bool CopyData(int*** Array, int swap_id, bool is_done=true);
        float GetMatrixHeuristic(int** Array);
        int GetLinearConflicts(int** Array);
        int** GetCopy(int** Array);
        bool CheckExistMatrixInHistory(int** Array);
        int FindEpmtyPos();
};

