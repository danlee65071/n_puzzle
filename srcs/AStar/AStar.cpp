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
        else if (is_vertical)
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
        else {
            if (i > i_min)
                i--;
            else {
                j++;
                j_min++;
                is_vertical = true;
                is_reverse = false;
            }
        }
        k++;
        start_value++;
    }
    this->_History.insert(this->GetCopy(this->_Data));
}

int** AStar::GetCopy(int **Array)
{
    int** cpy = new int*[this->_N];
    for (int i = 0; i < this->_N; i++)
    {
        cpy[i] = new int[this->_N];
        for (int j = 0; j < this->_N; j++)
            cpy[i][j] = Array[i][j];
    }
    return cpy;
}

int AStar::ManhattanMetric(Point p, Point goal)
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
        else if (is_vertical)
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
        else {
            if (i > i_min)
                i--;
            else {
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

bool AStar::CopyData(int*** Array, int swap_id, bool is_done)
{
    for (int i = 0; i < this->_N; i++)
        for (int j = 0; j < this->_N; j++)
            (*Array)[i][j] = this->_Data[i][j];
    switch (swap_id)
    {
        case 0: {
            if (this->_EmptyPos.y > 0) {
                std::swap((*Array)[this->_EmptyPos.y][this->_EmptyPos.x],
                          (*Array)[this->_EmptyPos.y - 1][this->_EmptyPos.x]);
            }
            else
                is_done = false;
            break;
        }
        case 1: {
            if (this->_EmptyPos.y < this->_N - 1) {
                std::swap((*Array)[this->_EmptyPos.y][this->_EmptyPos.x],
                          (*Array)[this->_EmptyPos.y + 1][this->_EmptyPos.x]);
            }
            else
                is_done = false;
            break;
        }
        case 2: {
            if (this->_EmptyPos.x < this->_N - 1) {
                std::swap((*Array)[this->_EmptyPos.y][this->_EmptyPos.x],
                          (*Array)[this->_EmptyPos.y][this->_EmptyPos.x + 1]);
            }
            else
                is_done = false;
            break;
        }
        case 3: {
            if (this->_EmptyPos.x > 0) {
                std::swap((*Array)[this->_EmptyPos.y][this->_EmptyPos.x],
                          (*Array)[this->_EmptyPos.y][this->_EmptyPos.x - 1]);
            }
            else
                is_done = false;
            break;
        }
    }
    return is_done;
}

int AStar::GetLinearConflicts(int** Array)
{
    int conflicts = 0;

//    checks rows
    for (int i = 0; i < this->_N; i++)
        for (int cur_row = 0; cur_row < this->_N - 1; cur_row++)
            for (int j = cur_row + 1; j < this->_N; j++) {
                if (!Array[i][j] || !Array[i][cur_row])
                    continue;
                if (this->_NumPos[Array[i][cur_row] - 1].y == this->_NumPos[Array[i][j] - 1].y \
                    && this->_NumPos[Array[i][cur_row] - 1].y == i && this->_NumPos[Array[i][cur_row] - 1].x > this->_NumPos[Array[i][j] - 1].x)
                    conflicts++;
            }

//    checks columns
    for (int j = 0; j < this->_N; j++)
        for (int cur_col = 0; cur_col < this->_N - 1; cur_col++)
            for (int i = cur_col + 1; i < this->_N; i++)
            {
                if (!Array[i][j] || !Array[cur_col][j])
                    continue;
                if (this->_NumPos[Array[cur_col][j] - 1].x == this->_NumPos[Array[i][j] - 1].x \
                    && this->_NumPos[Array[cur_col][j] - 1].x == j && this->_NumPos[Array[cur_col][j] - 1].y > this->_NumPos[Array[i][j] - 1].y)
                    conflicts++;
            }
    return conflicts;
}

int AStar::GetMatrixHeuristic(int **Array)
{
    int res = 0;

    for (int i = 0; i < this->_N; i++)
    {
        for (int j = 0; j < this->_N; j++)
        {
            if (!Array[i][j])
                continue;
            Point p = {j, i, Array[i][j]};
            res += this->_Heuristics(p, this->_NumPos[Array[i][j] - 1]);
        }
    }
    res += 2 * AStar::GetLinearConflicts(Array);
    return res;
}

bool AStar::CheckExistMatrixInHistory(int **Array)
{
    bool flag = true;
    for (auto it : this->_History) {
        flag = true;
        for (int i = 0; i < this->_N; i++) {
            for (int j = 0; j < this->_N; j++) {
//                std::cout << it[i][j] << ' ' << Array[i][j] << std::endl;
                if (it[i][j] != Array[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (!flag)
                break;
        }
        if (flag) {
            std::cout << "1\n";
            return true;
        }
    }
    std::cout << "0\n";
    return false;
}

void AStar::RunAlgo()
{
    int** cpy1 = new int*[this->_N]; // up 0
    int** cpy2 = new int*[this->_N]; // down 1
    int** cpy3 = new int*[this->_N]; // right 2
    int** cpy4 = new int*[this->_N]; // left 3
    int prev;

    prev = -1;

    int g = 0;

    for (int i = 0; i < this->_N; i++)
    {
        cpy1[i] = new int[this->_N];
        cpy2[i] = new int[this->_N];
        cpy3[i] = new int[this->_N];
        cpy4[i] = new int[this->_N];
    }
    for (int i = 0; i < this->_N; i++)
    {
        for (int j = 0; j < this->_N; j++)
            std::cout << this->_Data[i][j] << ' ';
        std::cout << std::endl;
    }
    while (!this->CheckData())
    {
        bool is_cpy1 = this->CopyData(&cpy1, 0);
        bool is_cpy2 = this->CopyData(&cpy2, 1);
        bool is_cpy3 = this->CopyData(&cpy3, 2);
        bool is_cpy4 = this->CopyData(&cpy4, 3);

        int f[4];

        f[0] = f[1] = f[2] = f[3] = std::numeric_limits<int>::max();
        std::cout << is_cpy1 << ' ' << is_cpy2 << ' ' << is_cpy3 << ' ' << is_cpy4 << std::endl;
        if (is_cpy1 && prev != 1 && !this->CheckExistMatrixInHistory(cpy1))
            f[0] = g + this->GetMatrixHeuristic(cpy1);
        if (is_cpy2 && prev != 0 && !this->CheckExistMatrixInHistory(cpy2))
            f[1] = g + this->GetMatrixHeuristic(cpy2);
        if (is_cpy3 && prev != 3 && !this->CheckExistMatrixInHistory(cpy3))
            f[2] = g + this->GetMatrixHeuristic(cpy3);
        if (is_cpy4 && prev != 2 && !this->CheckExistMatrixInHistory(cpy4))
            f[3] = g + this->GetMatrixHeuristic(cpy4);

        int min_val = f[0];
        int min_id = 0;
        for (int i = 1; i < 4; i++) {
            if (f[i] < min_val) {
                min_val = f[i];
                min_id = i;
            }
        }

        for (int i : f)
            std::cout << i << ' ';
        std::cout << std::endl;

        switch (min_id) {
            case 0: {
//                this->_History.insert(cpy1);
                for (int i = 0; i < this->_N; i++)
                    for (int j = 0; j < this->_N; j++)
                        this->_Data[i][j] = cpy1[i][j];
                this->_EmptyPos.y--;
                prev = 0;
                std::cout << "up" << std::endl;
                break;
            }
            case 1: {
//                this->_History.insert(cpy2);
                for (int i = 0; i < this->_N; i++)
                    for (int j = 0; j < this->_N; j++)
                        this->_Data[i][j] = cpy2[i][j];
                (this->_EmptyPos.y)++;
                prev = 1;
                std::cout << "down" << std::endl;
                break;
            }
            case 2: {
//                this->_History.insert(cpy3);
                for (int i = 0; i < this->_N; i++)
                    for (int j = 0; j < this->_N; j++)
                        this->_Data[i][j] = cpy3[i][j];
                (this->_EmptyPos.x)++;
                prev = 2;
                std::cout << "right" << std::endl;
                break;
            }
            case 3: {
//                this->_History.insert(cpy4);
                for (int i = 0; i < this->_N; i++)
                    for (int j = 0; j < this->_N; j++)
                        this->_Data[i][j] = cpy4[i][j];
                (this->_EmptyPos.x)--;
                prev = 3;
                std::cout << "left" << std::endl;
                break;
            }
        }

        this->_History.insert(this->GetCopy(this->_Data));

        std::cout << std::endl;
        for (int i = 0; i < this->_N; i++)
        {
            for (int j = 0; j < this->_N; j++)
                std::cout << this->_Data[i][j] << ' ';
            std::cout << std::endl;
        }

//        std::cout << "\nHistory start\n";
//        for (auto it : this->_History)
//        {
//            for (int i = 0; i < this->_N; i++)
//            {
//                for (int j = 0; j < this->_N; j++)
//                    std::cout << it[i][j] << ' ';
//                std::cout << std::endl;
//            }
//            std::cout << std::endl;
//        }
//        std::cout << "History end\n";

//        if (g == 23)
//            exit(0);
        std::cout << g << std::endl;
        g++;
    }
}
