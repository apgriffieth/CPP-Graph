//************************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1212575453
// Name: Alan Griffieth
// Description: This class defines a directed graph
//********************************************************************

#include "CityList.h"

using namespace std;

class Graph
{
 private:
  int numOfNode;   //number of nodes in the graph
  int time;   //a global timer used to find each node dTime,fTime
  CityList* adjacentList; //a linked list of LinkedList

 public:
  Graph(int numOfNode, CityList* adjacentList);
  void destructor();

  void printGraph();
  void DFS();
  void DFS_Visit(Node *node);
  void printDFSResult();
};

//***************************************************************
//Constructor
Graph::Graph(int numOfNode, CityList* adjacentList)
{
  numOfNode = numOfNode;
  time = 0;
  this->adjacentList = adjacentList;
}

//*******************************************************************
//Destructor. We explicitly defines it as a function, in order to be
//able to call it from other functions, to make sure memory is released.
void Graph::destructor()
{
  adjacentList->destructor();//Calls destructor for CityList
  time = 0;
  numOfNode = 0;
}

//*******************************************************************
//This function prints the graph. The graph is represented by adjacency
//list. It will print the adjacency list.
void Graph::printGraph()
{
  adjacentList->CityListDisplay();
}

//*******************************************************************
//This function performs the DFS on the graph. Note: the DFS starts
//from the first node in adjacency list
void Graph::DFS()
{
  Node* node = adjacentList->getHead();//node is head of CityList
  
  while(node != NULL) {//Makes all nodes in CityList white
    node->color = "WHITE";
    node = node->next;
  }

  time = 0;
  Node* node2 = adjacentList->getHead();//node2 is head of CityList
  while(node2 != NULL) {
    if(node2->color == "WHITE") {
      this->DFS_Visit(node2);
    }
    node2 = node2->next;
  }
}

//*******************************************************************
//This function performs the DFS-Visit from the parameterized node
void Graph::DFS_Visit(Node* node)
{
  time++;
  node->dTime = time;
  node->color = "GRAY";
  
  ArrCity* arrCity = node->arrCityList->getHead();//arrCity is head of the node's adjacent list
  while(arrCity != NULL) {
    string cityName = arrCity->arrCity;
    Node* node3 = adjacentList->CityListSearch(cityName);//node3 is the city in the CityList
    if(node3->color == "WHITE") {//Only do this if the node hasn't been visited yet
      node3->pi = node->depCity;
      DFS_Visit(node3);
    }
    arrCity = arrCity->next;
  }

  node->color = "BLACK";//This node and every node in its adjacent list has been visited
  time++;
  node->fTime = time;
}

//**************************************************************
//This function prints the parent, dTime & fTime info. of
//each node after DFS. Check our solution output.
void Graph::printDFSResult()
{
  cout << left;
  cout << setw(15) << "City Name" << setw(10) << "Parent"
       << setw(10) << "dTime" << setw(10) << "fTime" << endl;

  cout << setw(15) << "=========" << setw(10) << "======"
       << setw(10) <<"=====" <<setw(10) << "=====" << endl;

  Node* node = adjacentList->getHead();
  while(node != NULL) {//Follows output format given
    cout << setw(15) << node->depCity
	 << setw(10) << node->pi
	 << setw(10) << node->dTime
	 << setw(10) << node->fTime << endl;

    node = node->next;
  }
}
