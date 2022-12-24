#include "TestManhattanMetrics.hpp"

void TestManhattanMetric::_TestManhattanMetric1()
{
    Point p1 = {0., -1.};
    Point p2 = {2., 0.};

    float result = g_algo.manhattan_metric(p1, p2);
    assert(result == 3.);
    std::cout << "Test1 manhattan metric succeed!" << std::endl;
}

void TestManhattanMetric::_TestManhattanMetric2()
{
    Point p1 = {3.2, 1.3};
    Point p2 = {2.2, 0.3};

    float result = g_algo.manhattan_metric(p1, p2);
    assert(result == 2.);
    std::cout << "Test1 manhattan metric succeed!" << std::endl;
}

void TestManhattanMetric::_TestManhattanMetric3()
{
    Point p1 = {4.5, -7.2};
    Point p2 = {2.1, 2.3};

    float result = g_algo.manhattan_metric(p1, p2);
    assert(result == 11.9);
    std::cout << "Test1 manhattan metric succeed!" << std::endl;
}

void TestManhattanMetric::run_tests()
{
    std::cout << "----Manhattan metric tests start!----" << std::endl;
    this->_TestManhattanMetric1();
    this->_TestManhattanMetric2();
    this->_TestManhattanMetric3();
    std::cout << "----Manhattan metric tests end!----" << std::endl;
}