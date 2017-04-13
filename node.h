//This is the node header file which was included for us on Blackboard

#include <iostream>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <stack>

using namespace std;

typedef int WeightType;
typedef int NodeType;

int const MaxNumNodex = 9999;

typedef int NodeWeight;
typedef int EdgeWeight;

class node
{
   public:
      node();
      node(const node &);
      node &operator=(const node &);
   
      void setId(int i);
      int getId() const;

      void setWeight(NodeWeight);
      NodeWeight getWeight() const;
   
      void setNode(int, NodeWeight, bool, bool);

      void mark();
      void unMark();
      bool isMarked() const;

      void visit();
      void unVisit();
      bool isVisited() const;

        void setEnd();
        bool getEnd();

   private:
      int id;
      NodeWeight weight;
      bool marked;
      bool visited;
      bool endNode;
};

node::node()
// Constructor, creates a new, uninitialized node. Id is initialized
// elsewhere (by the graph constructor).
{
   unMark();
   unVisit();
   setWeight(0);
    endNode = false;
}

node::node(const node &n)
// Copy constructor
{
   setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited());
}

node &node::operator=(const node &n)
// Overloaded assignment operator.
{
   setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited());
   return *this;
}

NodeWeight node::getWeight() const
// Return node's weight
{
   return weight;
}

void node::setWeight(NodeWeight w)
// Set node's weight to w.
{
   weight = w;
}
   
void node::setId(int i)
// Set node's id to i.  Throws an exception if i < 0.
{
   if (i < 0)
      throw rangeError("Bad value in node::setId");
   
   id = i;
}
   
int node::getId() const
// Return node's id
{
   return id;
}

void node::setNode(int id, NodeWeight w = 0, bool m = false, bool v = false)
// Initializes a node
{
   setId(id);
   setWeight(w);

   if (m)
      mark();
   else
      unMark();
   
   if (v)
      visit();
   else
      unVisit();
}

void node::mark()
// Mark node.
{
   marked = true;
}

void node::unMark()
// Un-mark node.
{
   marked = false;
}

bool node::isMarked() const
// Return true if node is marked, and false otherwise.
{
   return marked;
}

void node::visit()
// Set visited to true;
{
   visited = true;
}

void node::unVisit()
// Set visited to false;
{
   visited = false;
}

bool node::isVisited() const
// Return true if node is visited, and false otherwise.
{
   return visited;
}

ostream &operator<<(ostream &ostr, const node &n)
//controls formatted printing out of nodes, for debug information
{
   ostr << "node: " << n.getId() << " weight: " << n.getWeight() 
        << " visited: " << n.isVisited() << " marked " << n.isMarked() << endl;

   return ostr;
}

void node::setEnd()
// set this node to be the destination node
{
    this->endNode = true;
}

bool node::getEnd()
// Determines if node is the end node of the maze
{
    return this->endNode;
}