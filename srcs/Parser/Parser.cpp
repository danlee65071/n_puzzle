#include "Parser.hpp"

Parser::Parser(std::string Path): _MapPath(std::move(Path))
{
    std::ifstream file(this->_MapPath);
    std::string header;
    std::string size_str;

    // int i = 0;
    if (file.is_open())
    {
        getline(file, header);
        getline(file, size_str);
        this->_N = std::atoi(size_str.c_str());
        this->_Data = new int*[this->_N];
        for (int i = 0; i < this->_N; i++)
        {
            this->_Data[i] = new int[this->_N];
            std::string line;
            getline(file, line);
            std::stringstream ss(line);
            for (int j = 0; j < this->_N; j++)
            {
                std::string num;
                getline(ss, num, ' ');
                this->_Data[i][j] = atoi(num.c_str());
            }
        }
    }
    file.close();
    // std::cout << this->_N << std::endl;
    // for (int i = 0; i < this->_N; i++)
    // {
    //     for (int j = 0; j < this->_N; j++)
    //         std::cout << this->_Data[i][j] << ' ';
    //     std::cout << std::endl;
    // }
}

Parser::~Parser()
{
    for (int i = 0; i < this->_N; i++)
        delete [] this->_Data[i];
    delete [] this->_Data;
}

int Parser::getN() const
{
    return this->_N;
}

int** Parser::getData() const
{
    return this->_Data;
}
