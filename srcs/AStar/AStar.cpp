#include "AStar.hpp"


AStar::AStar(int n, int** data, const std::string& heuristic): _N(n), _Data(data)
{
    if (heuristic == "manhattan")
        this->_Heuristics = &AStar::ManhattanMetric;
    bool is_break = false;
    for (int i = 0; i < this->_N; i++)
    {
        for (int j = 0; j < this->_N; j++)
        {
            if (this->_Data[i][j] == 0)
            {
                this->_EmptyPos.x = j;
                this->_EmptyPos.y = i;
                is_break = true;
                break;
            }
        }
        if (is_break)
            break;
    }

    this->_NumPos = new Point [this->_N * this->_N - 1];
    int start_value = 1;
    int end_value = this->_N * this->_N;
    int i, j, k;
    int i_max, j_max;
    int i_min, j_min;
    bool is_vertical = true;
    bool is_reverse = false;

    i = j = k = 0;
    i_max = j_max = this->_N - 1;
    i_min = j_min = 0;
    while (start_value < end_value)
    {
        this->_NumPos[k].x = j;
        this->_NumPos[k].y = i;
        this->_NumPos[k].value = k+1;

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
        k++;
        start_value++;
    }

    for (int i = 0; i < this->_N * this->_N - 1; i++) {
        std::cout << this->_NumPos[i].y << ' ' << this->_NumPos[i].x << ' ' << this->_NumPos[i].value << std::endl;
    }
}

double AStar::ManhattanMetric(Point p, Point goal)
{
    return abs(p.x - goal.x) + abs(p.y - goal.y);
}

bool AStar::CheckData() const
{
    int start_value = 1;
    int end_value = this->_N * this->_N;
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

void AStar::ShiftData()
{

}

bool AStar::CopyData(int**& Array, int swap_id, bool is_done)
{
    std::copy(&(this->_Data[0][0]), &(this->_Data[0][0]) + this->_N * this->_N, &Array[0][0]);

    switch (swap_id)
    {
        case 0: {
            if (this->_EmptyPos.y > 0)
                std::swap(Array[this->_EmptyPos.y][this->_EmptyPos.x], Array[this->_EmptyPos.y-1][this->_EmptyPos.x]);
            else
                is_done = false;
            break;
        }
        case 1: {
            if (this->_EmptyPos.y < this->_N - 1)
                std::swap(Array[this->_EmptyPos.y][this->_EmptyPos.x], Array[this->_EmptyPos.y+1][this->_EmptyPos.x]);
            else
                is_done = false;
            break;
        }
        case 2: {
            if (this->_EmptyPos.x < this->_N - 1)
                std::swap(Array[this->_EmptyPos.y][this->_EmptyPos.x], Array[this->_EmptyPos.y][this->_EmptyPos.x+1]);
            else
                is_done = false;
            break;
        }
        case 3: {
            if (this->_EmptyPos.x > 0)
                std::swap(Array[this->_EmptyPos.y][this->_EmptyPos.x], Array[this->_EmptyPos.y][this->_EmptyPos.x-1]);
            else
                is_done = false;
            break;
        }
    }
    return is_done;
}

//int AStar::GetMatrixHeuristic(int **Array)
//{
//
//}

void AStar::RunAlgo()
{
    int** cpy1 = new int*[this->_N]; // up 0
    int** cpy2 = new int*[this->_N]; // down 1
    int** cpy3 = new int*[this->_N]; // right 2
    int** cpy4 = new int*[this->_N]; // left 3

    for (int i = 0; i < this->_N; i++)
    {
        cpy1[i] = new int[this->_N];
        cpy2[i] = new int[this->_N];
        cpy3[i] = new int[this->_N];
        cpy4[i] = new int[this->_N];
    }


//    std::copy(&(this->_Data[0][0]), &(this->_Data[0][0]) + this->_N * this->_N, &cpy1[0][0]);
//    std::copy(&(this->_Data[0][0]), &(this->_Data[0][0]) + this->_N * this->_N, &cpy2[0][0]);
//    std::copy(&(this->_Data[0][0]), &(this->_Data[0][0]) + this->_N * this->_N, &cpy3[0][0]);
//    std::copy(&(this->_Data[0][0]), &(this->_Data[0][0]) + this->_N * this->_N, &cpy4[0][0]);

//    this->CopyData(cpy1, 0);

//    while (this->CheckData())
//    {
//        bool is_cpy1 = this->CopyData(cpy1, 0);
//        bool is_cpy2 = this->CopyData(cpy2, 0);
//        bool is_cpy3 = this->CopyData(cpy3, 0);
//        bool is_cpy4 = this->CopyData(cpy4, 0);
//    }
}
