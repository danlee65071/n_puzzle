#pragma once

#include "Point.hpp"
#include "cmath"

class AStar
{
    // Singleton design
    private:
        AStar() {}

    public:
        static AStar& getInstance()
        {
            static AStar instance;

            return instance;
        }
        AStar(const AStar&) = delete;
        void operator=(const AStar&) = delete;
        ~AStar() {}
        // Metrics
        static double manhattan_metric(Point p, Point goal);
};