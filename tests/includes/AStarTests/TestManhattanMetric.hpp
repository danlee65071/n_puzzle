#pragma once

#include "../Tests.hpp"

class TestManhattanMetric: public Tests
{
    // check manhattan metric
    private:
        void _TestManhattanMetric1();
        void _TestManhattanMetric2();
        void _TestManhattanMetric3();

    public:
        void run_tests() override;
};
