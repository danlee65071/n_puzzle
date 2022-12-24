#pragma once

#include "AStar.hpp"
#include "AStarTests/TestManhattanMetric.hpp"
#include "cassert"
#include "iostream"


class Tests
{
    public:
        virtual void run_tests() = 0;
};
