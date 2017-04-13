#include <iostream>
#include <iomanip>
#include "d_except.h"
#include "d_matrix.h"
#include "maze.h"

using namespace std;

int main()
{
    char x;
    ifstream fin;

    // Read the maze from the file.
    string fileName = "Maze1.txt";



    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {

        graph g;
        while (fin && fin.peek() != 'Z')
        {
            maze m(fin);
            m.print(6,9,1,0);
            m.mapMazeToGraph(g);

            bool pathFound = false;
            stack<edge> pathToDest;
            m.findPathRecursive(g, 0, pathFound, pathToDest);
            m.findPathNonRecursive(g);
        }

        cout << "test";
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }


}
