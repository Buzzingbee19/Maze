//
// Created by Patrick on 4/10/17.
//

#ifndef MAZE_CELL_H
#define MAZE_CELL_H

#include <vector>

class Cell
{
private:
    int row;
    int col;

public:
};

class Node:Cell
{
private:
    vector<Node> neighbors;

public:
};

class Wall:Cell
{
private:

public:
};


#endif //MAZE_CELL_H
