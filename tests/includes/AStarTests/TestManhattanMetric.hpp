#pragma once

#include "AStarTests.hpp"

class TestManhattanMetric: public AStarTests
{
    // check manhattan metric
    private:
        void _TestManhattanMetric1();
        void _TestManhattanMetric2();
        void _TestManhattanMetric3();

    public:
        void run_tests() override;
};