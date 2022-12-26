#include <iostream>
#include "Parser.hpp"
#include "AStar.hpp"

int main()
{
    Parser p1("maps/1.txt");

    AStar& a = AStar::GetInstance(p1.getN(), p1.getData());
//    std::cout << a.CheckData() << std::endl;
    a.RunAlgo();
    return 0;
}