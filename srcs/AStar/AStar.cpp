#include "AStar.hpp"


AStar::AStar(int n, int** data, const std::string& heuristic): _N(n), _Data(data)
{
    if (!this->CheckBoard())
    {
        std::cout << "The puzzle is unsolvable" << std::endl;
        exit(0);
    }
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
    this->_OriginalData = this->GetCopy(this->_Data);
    this->_OriginalEmptyPos.x = this->_EmptyPos.x;
    this->_OriginalEmptyPos.y = this->_EmptyPos.y;
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

float AStar::ManhattanMetric(Point p, Point goal)
{
    return abs(p.x - goal.x) + abs(p.y - goal.y);
}

float AStar::EuclidianMetric(Point p, Point goal)
{
    return sqrt(pow(p.x - goal.x, 2) - pow(p.y - goal.y, 2));
}

int AStar::GetInversionsCount(const int *Array) const
{
    int inv_count = 0;
    for (int i = 0; i < this->_N * this->_N - 1; i++)
        for (int j = i+1; j < this->_N * this->_N; j++)
            if (Array[j] && Array[i] &&  Array[i] > Array[j])
                inv_count++;
    return inv_count;
}

int AStar::FindEpmtyPos()
{
    for (int i = this->_N - 1; i >= 0; i--)
        for (int j = this->_N - 1; j >= 0; j--)
            if (this->_Data[i][j] == 0)
                return this->_N - i;
    return 0;
}

bool AStar::CheckBoard()
{
    int* LineData = new int[this->_N * this->_N - 1];
    int i, j, k;
    int i_max, j_max;
    int i_min, j_min;
    bool is_vertical = true;
    bool is_reverse = false;
    int start_value = 0;

    i = j = k = 0;
    i_max = j_max = this->_N - 1;
    i_min = j_min = 0;
    while (start_value < this->_N * this->_N - 1)
    {
        if (this->_Data[i][j])
            LineData[k++] = this->_Data[i][j];
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

    int InversionsCount = this->GetInversionsCount(LineData);
    if (this->_N % 2 != 0)
    {
        if (InversionsCount % 2 != 0)
            return false;
    }
    else
    {
        int pos = this->FindEpmtyPos();
        if (pos & 1)
            return !(InversionsCount & 1);
        else
            return InversionsCount & 1;
    }
    return true;
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

float AStar::GetMatrixHeuristic(int **Array)
{
    float res = 0;

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
    res += static_cast<float>(2 * AStar::GetLinearConflicts(Array));
    return res;
}

bool AStar::CheckExistMatrixInHistory(int **Array)
{
    bool flag = true;
    for (auto it : this->_History) {
        flag = true;
        for (int i = 0; i < this->_N; i++) {
            for (int j = 0; j < this->_N; j++) {
                if (it[i][j] != Array[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (!flag)
                break;
        }
        if (flag) {
            std::cout << "exists!" << std::endl;
            return true;
        }
    }
    return false;
}

void AStar::RunAlgo()
{
    int** cpy1 = new int*[this->_N]; // up 0
    int** cpy2 = new int*[this->_N]; // down 1
    int** cpy3 = new int*[this->_N]; // right 2
    int** cpy4 = new int*[this->_N]; // left 3
    int prev;
    bool is_inf;

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

        float f[4];

        f[0] = f[1] = f[2] = f[3] = std::numeric_limits<float>::max();
        if (is_cpy1 && prev != 1 && !this->CheckExistMatrixInHistory(cpy1))
            f[0] = static_cast<float>(g + this->GetMatrixHeuristic(cpy1));
        if (is_cpy2 && prev != 0 && !this->CheckExistMatrixInHistory(cpy2))
            f[1] = static_cast<float>(g + this->GetMatrixHeuristic(cpy2));
        if (is_cpy3 && prev != 3 && !this->CheckExistMatrixInHistory(cpy3))
            f[2] = static_cast<float>(g + this->GetMatrixHeuristic(cpy3));
        if (is_cpy4 && prev != 2 && !this->CheckExistMatrixInHistory(cpy4))
            f[3] = static_cast<float>(g + this->GetMatrixHeuristic(cpy4));

        is_inf = true;
        float min_val = f[0];
        int min_id = 0;

        for (int k = 1; k < 4; k++)
        {
            if (f[k] != f[k-1])
                is_inf = false;
        }
        if (is_inf && f[0] == std::numeric_limits<float>::max())
        {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,3);
            min_id = static_cast<int>(dist(rng));
        }
        else
        {
            for (int i = 1; i < 4; i++) {
                if (f[i] < min_val) {
                    min_val = f[i];
                    min_id = i;
                }
            }
        }

        switch (min_id) {
            case 0: {
                if (is_cpy1)
                {
                    for (int i = 0; i < this->_N; i++)
                        for (int j = 0; j < this->_N; j++)
                            this->_Data[i][j] = cpy1[i][j];
                    this->_EmptyPos.y--;
                    prev = 0;
                    std::cout << "up" << std::endl;
                    break;
                }
            }
            case 1: {
                if (is_cpy2) {
                    for (int i = 0; i < this->_N; i++)
                        for (int j = 0; j < this->_N; j++)
                            this->_Data[i][j] = cpy2[i][j];
                    (this->_EmptyPos.y)++;
                    prev = 1;
                    std::cout << "down" << std::endl;
                    break;
                }
            }
            case 2: {
                if (is_cpy3) {
                    for (int i = 0; i < this->_N; i++)
                        for (int j = 0; j < this->_N; j++)
                            this->_Data[i][j] = cpy3[i][j];
                    (this->_EmptyPos.x)++;
                    prev = 2;
                    std::cout << "right" << std::endl;
                    break;
                }
            }
            case 3: {
                if (is_cpy4) {
                    for (int i = 0; i < this->_N; i++)
                        for (int j = 0; j < this->_N; j++)
                            this->_Data[i][j] = cpy4[i][j];
                    (this->_EmptyPos.x)--;
                    prev = 3;
                    std::cout << "left" << std::endl;
                    break;
                }
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
        g++;
    }
    exit(0);
}
