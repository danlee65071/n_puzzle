#include "AStar.hpp"

float AStar::manhattan_metric(Point p, Point goal)
{
    return abs(p.x - goal.x) + abs(p.y - goal.y);
}
