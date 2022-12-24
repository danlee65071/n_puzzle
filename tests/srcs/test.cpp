#include <iostream>
#include "Units.hpp"

int main()
{
    g_tests.push_back(new TestManhattanMetric());
    for (auto test: g_tests)
    {
        test->run_tests();
    }
    return 0;
}