//*******************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1212575453
// Name: Alan Griffieth
// Description: this is a linked list of LinkedList used to represent
// the adjacency list of a graph.
//*****************************************************************

#include "LinkedList.h"

using namespace std;

//Node represents a departure city info. this includes
//the departure city name, its arrival city list and
//other DFS info.
struct Node
{
  string depCity;
  string color, pi;   //pi is the parent
  int dTime, fTime;   //discover & finish time

  LinkedList* arrCityList;
  struct Node* next;
};

class CityList
{
 private:
  struct Node* head;

 public:
  CityList();
  void destructor();
  Node* getHead();
  bool CityListInsert(string deptCityName, LinkedList* arrCityList);
  bool CityListDelete(string deptCityName);
  Node* CityListSearch(string deptCityName);
  void CityListDisplay();
};

//constructor
CityList::CityList()
{
  head = NULL;
}

//Destructor
void CityList::destructor()
{
  int cityCount = 0;

  //make sure you release memory for the arrCityList
  //and the node
  Node* cur = head;
  Node* next = cur;

  while(cur != NULL) {
    next = cur->next;
    delete(cur->arrCityList);//Calls destructor for LinkedList
    delete(cur);//Deletes the node
    cur = next;
    cityCount++;
  }

  head = NULL;
  cout<< "The number of deleted departure cities is: " << cityCount <<"\n";
}

//This function is accessor for head
Node* CityList::getHead()
{
  return head;
}

//Given a departure city name, this function searches
//the adjacency list and return a pointer that points
//to it, otherwise it return NULL
Node* CityList::CityListSearch(string deptCityName)
{
  struct Node* start = head;
  bool found = false;
  while(start != NULL) {
    if(start->depCity == deptCityName) {//breaks out of the while loop if the city is found
      found = true;
      break;
    }

    else {
      start = start->next;
    }
  }

  if(found) {
    return(start);
  }
  
  else {//City was not part of the list
    return(NULL);
  }
}

//This function inserts a departure city with its arrival city list into
//the cityList. It returns true if the data is inserted successfully
//and false otherwise. Note: departure cities are inserted in alphabetical
//order
bool CityList::CityListInsert(string deptCityName, LinkedList* arrCityList )
{
  Node* newNode = new Node;
  newNode->depCity = deptCityName;
  newNode->arrCityList = arrCityList;
  newNode->pi = "none";
  newNode->dTime = 0;
  newNode->fTime = 0;
  newNode->next = NULL;
  
  if(head == NULL) {//List is empty
    head = newNode;
    return(true);
  }

  else {
    Node* cur = head;
    Node* pre = head;
    while(newNode->depCity > cur->depCity && cur->next != NULL) {//gets newNode in alphabetical order
      pre = cur;
      cur = cur->next;
    }

    if(cur == head) {//Special case when cur is the head
      if(head->next == NULL) {//Special case when only one item in the list
	if(newNode->depCity > head->depCity) {//newNode goes after head
	  head->next = newNode;
	  return(true);
	}
	
	else {//newNode goes before head
	  newNode->next = cur;
	  head = newNode;
	  return(true);
	}
      }
      
	else {//newNode should be the head
	  newNode->next = cur;
	  head = newNode;
	  return(true);
	}
    }

    else if(cur->next == NULL) {//Special case when cur is the tail
      if(newNode->depCity > cur->depCity) {//newNode should be the tail
	cur->next = newNode;
	return(true);
	}
      
      else {//newNode should be before the tail
	pre->next = newNode;
	newNode->next = cur;
	return(true);
      }
    }
    
    else {//normal insertion
      pre->next = newNode;
      newNode->next = cur;
      return(true);
    }
  }
}

//Given a departure city name, this function deletes it from the CityList.
//it returns true if it is deleted successfully and false otherwise
bool CityList::CityListDelete(string deptCityName)
{
  Node* cur = head;
  Node* pre = cur;
  while(cur->depCity != deptCityName) {//Moves through the list until we're at the city we want to remove
    pre = cur;
    cur = cur->next;
  }
  
  if(cur == head) {//Special case when removing the head
    head = head->next;
    delete(cur->arrCityList);
    delete(cur);
    return(true);
  }
  
  else {
    pre->next = cur->next;
    delete(cur->arrCityList);
    delete(cur);
    return(true);
  }  
}

//This function print the CityList on screen. It will
//print departure cities in alphabetical order, and for
//each departure city's reachable arrival city, it will
//also display them in alphabetical order
void CityList::CityListDisplay()
{
  struct Node* temp = head;
  if(head == NULL) {
    cout << "The departure city list is empty\n";
    return;
  }

  else {
    while(temp!= NULL) {     
      cout << left;
      cout << setw(15) << temp->depCity;
      temp->arrCityList->printArrCityList();
      temp = temp->next;
    }
    cout << endl;
  }
}
