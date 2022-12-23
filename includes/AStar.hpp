#pragma once

class AStar
{
    private:
        AStar() {}

    public:
        static AStar& getInstance()
        {
            static AStar instance;

            return instance;
        }
        AStar(const AStar&) = delete;
        void operator=(const AStar&) = delete;
};