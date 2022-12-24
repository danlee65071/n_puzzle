#pragma once

#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

class Parser
{
    private:
        std::string _MapPath;
        int _N;
        int** _Data;
    public:
        Parser(std::string Path);
        Parser(const Parser&) = delete;
        void operator=(const Parser&) = delete;
        ~Parser();

        [[nodiscard]] int getN() const;
        [[nodiscard]] int** getData() const;
};
