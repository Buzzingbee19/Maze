#include <iostream>
#include <iomanip>
#include "d_except.h"
#include "d_matrix.h"
#include "maze.h"

using namespace std;

void solveMaze(string filename);

int main()
{

    // Read the maze from the file.
    string maze1 = "Maze1.txt";
    string maze2 = "Maze2.txt";
    string maze3 = "Maze3.txt";

    //solve the mazes
    cout << "==============PRESS ENTER TO SOLVE THE FIRST MAZE================";
    cin.ignore();
    solveMaze(maze1);
    cout << "==============PRESS ENTER TO SOLVE THE NEXT MAZE================";
    cin.ignore();
    solveMaze(maze2);
    cout << "==============PRESS ENTER TO SOLVE THE NEXT MAZE================";
    cin.ignore();
    solveMaze(maze3);
}

void solveMaze(string fileName) {
    char x;
    ifstream fin;

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

            m.print(m.getRows() - 1,m.getCols() - 1,0,0);
            m.mapMazeToGraph(g);

            bool pathFound = false;
            stack<edge> recursivePath = m.findPathRecursive(g, 0, pathFound);

            if(recursivePath.empty())
                cout << "No path exists" << endl;

            while(!recursivePath.empty()) {
                edge path = recursivePath.top();
                recursivePath.pop();

                pair<int, int> coordinates = m.nodeLookup(path.getSource());

                m.print(m.getRows() - 1,m.getCols() - 1, coordinates.first, coordinates.second);
                path.printInstruction();
            }

            cout << "========PRESS ENTER TO DO A NON-RECURSIVE SEARCH=========";
            cin.ignore();

            stack<edge> nonRecursive = m.findPathNonRecursive(g);

            if(nonRecursive.empty())
                cout << "No path exists" << endl;

            stack<edge> reverseStack;
            while(!nonRecursive.empty()) {
                edge e = nonRecursive.top();
                nonRecursive.pop();
                reverseStack.push(e);
            }

            while(!reverseStack.empty()) {
                edge path = reverseStack.top();
                reverseStack.pop();

                pair<int, int> coordinates = m.nodeLookup(path.getSource());

                m.print(m.getRows() - 1,m.getCols() - 1, coordinates.first, coordinates.second);
                path.printInstruction();
            }
        }
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
