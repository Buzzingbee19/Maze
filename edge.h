#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>

using namespace std;

typedef int WeightType;
typedef int NodeType;

//int const MaxNumNodex = 9999;

typedef int NodeWeight;
typedef int EdgeWeight;

class edge
{
   public:
      edge();
      edge(int, int, EdgeWeight = 0, string instructions = "n/a");
      edge(const edge &);
      edge &operator=(const edge &);   

      void setWeight(EdgeWeight);
      EdgeWeight getWeight() const; 

      int getSource() const;
      int getDest() const;

      void setValid();
      void setInvalid();
      bool isValid() const;

      void mark();
      void unMark();
      bool isMarked() const;

      void visit();
      void unVisit();
      bool isVisited() const;

      void setEdge(int, int, EdgeWeight);
      void setInstructions(string instructions);
      void printInstruction();

   private:
      int source;
      int dest;
      EdgeWeight weight;
      bool valid;         // equals true if edge is valid, otherwise the
      bool visited;
      bool marked;
      string instructions;
      // edge is invalid
};

edge::edge()
// Constructor, sets edge to invalid, unmarked and unvisited.
{
   setInvalid();
   unMark();
   unVisit();
}

edge::edge(int i, int j, EdgeWeight w, string instructions)
// Constructor creates an edge with weight w, and marks the edge as valid, unvisited
// and unmarked.
{
   setEdge(i,j,w);
   unMark();
   unVisit();
   setInstructions(instructions);
}

edge::edge(const edge &e)
// Copy constructor.  Also copies visited and marked state.
{
   setEdge(e.source, e.dest, e.getWeight());

   setInstructions(e.instructions);

   if (e.isValid())
      setValid();
   else
      setInvalid();

   if (e.isVisited())
      visit();
   else
      unVisit();

   if (e.isMarked())
      mark();
   else
      unMark();
}

edge &edge::operator=(const edge &e)
// Overloaded assignment operator
{
   setEdge(e.source, e.dest, e.getWeight());

   if (e.isValid())
      setValid();
   else
      setInvalid();

   if (e.isVisited())
      visit();
   else
      unVisit();

   if (e.isMarked())
      mark();
   else
      unMark();

   return *this;
}

void edge::setEdge(int i, int j, EdgeWeight w = 0)
// Initialize edge with source, destination and weight and mark edge
// as valid.  Do not change visited or marked state.
{
   source = i;
   dest = j;
   weight = w;
   setValid();
}

void edge::setWeight(EdgeWeight w)
// Set edge weight to w.
{
   weight = w;
}

EdgeWeight edge::getWeight() const
// Return edge weight.
{
   return weight;  
}

EdgeWeight edge::getSource() const
// Return source node;
{
   return source;
}

EdgeWeight edge::getDest() const
// Return destination node.
{
   return dest;
}

void edge::setValid()
// Set the edge as valid.
{
   valid = true;
}

void edge::setInvalid()
// Set the edge as invalid.
{
   valid = false;
}

bool edge::isValid() const
// Return true if edge is valid.  Otherwise return false;
{
   return valid;
}

void edge::mark()
// Mark edge
{
   marked = true;
}

void edge::unMark()
// Un-mark edge
{
   marked = false;
}

bool edge::isMarked() const
// Return true if edge is marked, and false otherwise.
{
   return marked;
}

void edge::visit()
// Set visited to true;
{
   visited = true;
}

void edge::unVisit()
// Set visited to false;
{
   visited = false;
}

bool edge::isVisited() const
// Return true if edge is visited, and false otherwise.
{
   return visited;
}

ostream &operator<<(ostream &ostr, const edge &e)
// Print all edge information for a valid edge;
{
   cout << "edge (" << e.getSource() << "," << e.getDest() << "): ";
   cout << " weight: " << e.getWeight() << " visited: " << e.isVisited() 
	<< " marked " << e.isMarked() << endl;

   return ostr;
}

void edge::setInstructions(string instr)

{
   instructions = instr;
}

void edge::printInstruction()
//print out the instructions contained in the edge
{
    cout << this->instructions << endl;
}