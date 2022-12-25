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

bool AStar::check_data() const
{
    int start_value = 1;
    int end_value = pow(this->_N, 2);
    int i, j;
    int i_max, j_max;
    int i_min, j_min;
    bool is_vertical = true;
    bool is_reverse = false;

    i = j = 0;
    i_max = j_max = this->_N - 1;
    i_min = j_min = 0;
    while (start_value < end_value)
    {
        std::cout << this->_Data[i][j] << std::endl;
        if (this->_Data[i][j] != start_value)
            return false;
        if (is_vertical && !is_reverse)
        {
            if (j < j_max)
                j++;
            else
            {
                i++;
                i_min++;
                is_vertical = false;
            }
        }
        else if (!is_vertical && !is_reverse)
        {
            if (i < i_max)
                i++;
            else
            {
                j--;
                j_max--;
                is_vertical = true;
                is_reverse = true;
            }
        }
        else if (is_vertical && is_reverse)
        {
            if (j > j_min)
                j--;
            else
            {
                i--;
                i_max--;
                is_vertical = false;
            }
        }
        else if (!is_vertical && is_reverse)
        {
            if (i > i_min)
                i--;
            else
            {
                j++;
                j_min++;
                is_vertical = true;
                is_reverse = false;
            }
        }
        
        start_value++;
    }
    return true;
}

void AStar::run_algo()
{
    while (true)
    {

    }
}
