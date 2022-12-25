#include <iostream>
#include "Parser.hpp"
#include "AStar.hpp"

int main()
{
    Parser p1("maps/3.txt");
    Parser p2("maps/2.txt");

    AStar& a = AStar::getInstance(p1.getN(), p1.getData());
    std::cout << a.check_data() << std::endl;
    return 0;
}