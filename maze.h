// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "edge.h"
#include "graph.h"
#include <queue>

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool getValue(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      void mapMazeToGraph(graph &g);

      bool isLegal(int i, int j);

      stack<edge> findPathRecursive(graph& g, int nodeIndex, bool& pathFound);
      stack<edge> findPathNonRecursive(graph& g, int nodeIndex = 0);

        pair<int, int> nodeLookup(int n);
        int getRows();
        int getCols();


   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
      matrix<int> map;   // Mapping from maze (i,j) values to node index values

};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
    this->map[i][j] = n;
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
    return this->map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::getValue(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

bool maze::isLegal(int i, int j)
// is it safe to access this value in the matrices?
{
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

int maze::getRows()
// return the number of rows in the maze
{
    return this->rows;
}

int maze::getCols()
// return the number of rows in the maze
{
    return this->cols;
}


void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
    //create the vector of nodes and update the map matrix for this maze
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->value[i][j]) {
                int index = g.addNode();
                this->map[i][j] = index;
            }
        }
    }

    g.setEnd(g.numNodes() - 1);

    //create the matrix of edges for the graph
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->value[i][j]) {
                int fromIndex = this->map[i][j];
                //check the adjacent nodes
                if (isLegal(i, j + 1) && this->value[i][j + 1])
                    //look right and connect
                {
                    int toIndex = this->map[i][j + 1];
                    g.addEdge(fromIndex, toIndex, 1, "go right");
                }
                if (isLegal(i, j - 1) && this->value[i][j - 1])
                    //look left and connect
                {
                    int toIndex = this->map[i][j - 1];
                    g.addEdge(fromIndex, toIndex, 1, "go left");
                }
                if (isLegal(i + 1, j) && this->value[i + 1][j])
                    //look down and connect
                {
                    int toIndex = this->map[i + 1][j];
                    g.addEdge(fromIndex, toIndex, 1, "go down");
                }
                if (isLegal(i - 1, j) && this->value[i - 1][j])
                    //look up and connect
                {
                    int toIndex = this->map[i - 1][j];
                    g.addEdge(fromIndex, toIndex, 1, "go up");
                }
            }
        }
    }
}

stack<edge> maze::findPathRecursive(graph& g, int nodeIndex, bool& pathFound)
// looks for a path between the start node and end node
{
    //mark n as visted
    g.visit(nodeIndex);

    //check if current node is the final node
    if(g.isEnd(nodeIndex)) {
        pathFound = true;
        stack<edge> s;
        return s;
    }


    //create vector of neighbors
    vector<edge> paths = g.getEdges(nodeIndex);

    stack<edge> nodeOrder;

    //for each node w of node n
    for(auto path : paths) {
        if(!g.isVisited(path.getDest()) && !pathFound) {
            path.printInstruction();
            nodeOrder = findPathRecursive(g, path.getDest(),
                                                   pathFound);
            if(pathFound)
                nodeOrder.push(path);
            else
                cout << "go back" << endl;
        }
    }
    return nodeOrder;
}


stack<edge> maze::findPathNonRecursive(graph &g, int nodeIndex)
// look for a path between the start node and the end node
{
    //reset the nodes in the graph
    g.unVisitAll();

    //declare DFS stack
    stack<edge> mazePath;

    //find the paths
    vector<edge> startPath = g.getFirstNewEdge(nodeIndex);
    g.visit(nodeIndex);

    if(!startPath.empty())
        mazePath.push(startPath[0]);

    while(!mazePath.empty()) {
        edge path = mazePath.top();

        g.visit(path.getSource(), path.getDest());
        int dest = path.getDest();

        if(!g.isVisited(dest)) {
            path.printInstruction();
            if(g.isEnd(dest))
                return mazePath;
            g.visit(dest);
            vector<edge> continuePath = g.getFirstNewEdge(dest);
            if(!continuePath.empty())
                mazePath.push(continuePath[0]);
        }
        else {
            mazePath.pop();
            vector<edge> continuePath = g.getFirstNewEdge(path.getSource());
            if(!continuePath.empty())
                mazePath.push(continuePath[0]);
            else {
                cout << "go back" << endl;
            }
        }
    }
    return mazePath;
}

pair<int, int> maze::nodeLookup(int n)
// lookup the coordinates of the node on this object's map matrix
{
    for(int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if(this->map[i][j] == n)
            {
                pair<int, int> coordinates = make_pair(i,j);
                return coordinates;
            }
        }
    }

    throw rangeError("No coordinates for this node maze::nodeLookup");
}