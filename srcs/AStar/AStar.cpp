#include "AStar.hpp"

AStar::AStar(int n, int** data, std::string heuristic): _N(n), _Data(data)
{
    if (heuristic == "manhattan")
        this->_Heuristics = &AStar::manhattan_metric;
}

double AStar::manhattan_metric(Point p, Point goal)
{
    return abs(p.x - goal.x) + abs(p.y - goal.y);
}
