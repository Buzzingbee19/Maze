#include <iostream>
#include "d_except.h"
#include "maze.h"

using namespace std;

void print (stack<edge> &path, maze &m);
void solveMaze(string filename);

int main()
//controls the program flow. Prints out of each maze file.
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

void solveMaze(string fileName)
//solveMaze takes in the name of a maze file, attempts to open it, and if
// success, recursively and non-recursively attempts to solve the maze
{
    char x;
    ifstream fin;
    fin.open(fileName.c_str());

    if (!fin) //if the program is unable to open the specified file
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        graph g;

        //reads characters in fromthe file until the end of file character Z
        // is detected
        while (fin && fin.peek() != 'Z')
        {
            //instantiates a maze object, prints out the initial problem, and
            // creates a graph object based on the maze.
            maze m(fin);
            m.print(m.getRows() - 1,m.getCols() - 1,0,0);
            m.mapMazeToGraph(g);

            //initializes the path to not be found
            bool pathFound = false;

            //attempts to solve the maze through a recursive DFS algorithm
            cout << "All the commands needed to find the destination: \n";
            stack<edge> recursivePath = m.findPathRecursive(g, 0, pathFound);

            print(recursivePath, m);

            cout << "========PRESS ENTER TO DO A NON-RECURSIVE SEARCH=========";
            cin.ignore();

            //attempts to solve the maze through a non-recursive DFS algorithm
            cout << "All the commands needed to find the destination: \n";
            stack<edge> nonRecursive = m.findPathNonRecursive(g);

            print(nonRecursive, m);
        } //end the while loop
    } //end the try condition

    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }

    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
}

void print(stack<edge> &path, maze &m)
//controls printing of the path through the maze
{
    //determines if a path exists for the graph
    if(path.empty())
        cout << "No path exists" << endl;

    //prints out a correct path to traverse the maze using graph nodes
    while(!path.empty())
    {
        edge pathstep = path.top();
        path.pop();

        pair<int, int> coordinates = m.nodeLookup(pathstep.getSource());

        m.print(m.getRows() - 1,m.getCols() - 1, coordinates.first,
                coordinates.second);

        pathstep.printInstruction();
    }
}