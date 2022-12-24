#pragma once

#include "AStar.hpp"
#include "cassert"
#include "iostream"


AStar& g_algo = AStar::getInstance();


class Tests
{
    public:
        virtual void run_tests() = 0;
};
