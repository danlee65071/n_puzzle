#include <iostream>
#include "Parser.hpp"
#include "AStar.hpp"

int main(int argc, char** argv)
{
    if (argc == 2 || argc == 3)
    {
        std::string map(argv[1]);
        std::string heuristic;
        if (argc == 3)
            heuristic = argv[2];
        else
            heuristic = "manhattan";

        Parser p(map);
        AStar &a = AStar::GetInstance(p.getN(), p.getData(), heuristic);
        a.RunAlgo();
    }
    return 0;
}