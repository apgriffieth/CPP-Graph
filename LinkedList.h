//************************************************************************
// ASU CSE310 Assignment #6
// ASU ID: 1212575453
// Name: Alan Griffieth
// Description: this is a linked list used to store arrival cities

#include <iostream>
#include <iomanip> //to format the output
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information
struct ArrCity
{
  string arrCity;
  double price;
  struct ArrCity * next;
};

//class LinkedList will contains a linked list of arrival cities
class LinkedList
{
 private:
  struct ArrCity* head;

 public:
  LinkedList();
  ~LinkedList();
  ArrCity* getHead();
  bool isFound(string aCity);
  bool addArrCity(string aCity, double price);
  bool removeArrCity(string aCity);
  void printArrCityList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
  head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory.
//It deletes all the ArrCitys including the head and finally prints the number
//of ArrCitys deleted by it.
LinkedList::~LinkedList()
{
  int cityCount = 0;

  ArrCity* cur = head;
  ArrCity* next = cur;

  while(cur != NULL) {
    next = cur->next;
    delete(cur);
    cur = next;
    cityCount++;
  }

  head = NULL;
  cout<< "The number of deleted arrival cities are: " << cityCount <<"\n";
}

//Accessor to the header of the linked list
ArrCity* LinkedList::getHead()
{
  return head;
}

//A function to check if the parameterized arrival city is
//inside the LinkedList or not. Return true if it exists and
//false otherwise.
bool LinkedList::isFound(string aCity)
{
  struct ArrCity* start = head;
  bool found = false;
  while(start != NULL) {
    if(start->arrCity == aCity) {
      found = true;
      break;
    }

    else {
      start = start->next;
    }
  }
  return(found);
}

//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCitys
//while inserting it into the list. Note: you cannot insert duplicated ArrCitys
//Return value: true if it is successfully inserted and false otherwise
bool LinkedList::addArrCity(string aCity, double price)
{
  if(isFound(aCity)) {//City is already in the list
    return(false);
  }

  else {
    ArrCity* newCity = new ArrCity;
    newCity->arrCity = aCity;
    newCity->price = price;
    newCity->next = NULL;

    if(head == NULL) {//The list is empty
      head = newCity;
      return(true);
    }

    else {
      ArrCity* cur = head;
      ArrCity* pre = head;

      while(newCity->arrCity > cur->arrCity && cur->next != NULL) {//Gets newCity in alphabetical order
	pre = cur;
	cur = cur->next;
      }

      if(cur == head) {//Special case when cur is head
	if(head->next == NULL) {
	  if(newCity->arrCity > head->arrCity) {//newCity goes after the head
	    head->next = newCity;
	    return(true);
	  }

	  else {//newCity should be the head
	    newCity->next = cur;
	    head = newCity;
	    return(true);
	  }
	}

	else {//newCity should be the head
	  newCity->next = cur;
	  head = newCity;
	  return(true);
	}
      }

      else if(cur->next == NULL) {//Special case when cur is at the tail
	if(newCity->arrCity > cur->arrCity) {//newCity should be the last item in the list
	  cur->next = newCity;
	  return(true);
	}

	else {//newCity should be the second to last item in the list
	  pre->next = newCity;
	  newCity->next = cur;
	  return(true);
	}
      }

      else {//We are somewhere in the middle of the list
	pre->next = newCity;
	newCity->next = cur;
	return(true);
      }
    }
  }
}

//Removes the given ArrCity from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeArrCity(string aCity)
{
  if(!isFound(aCity)) {//City isn't in the list
    return(false);
  }

  else {
    ArrCity* cur = head;
    ArrCity* pre = cur;
    while(cur->arrCity != aCity) {//Moves cur to the city we want to remove
      pre = cur;
      cur = cur->next;
    }

    if(cur == head) {//Special case when removing head
      head = head->next;
      delete(cur);
      return(true);
    }

    else {
      pre->next = cur->next;
      delete(cur);
      return(true);
    }
  }
}

//Prints all the arrival cities info. in the linked list starting from the head.
void LinkedList::printArrCityList()
{
  struct ArrCity *temp = head;
  if(head == NULL)
    {
      cout << "The arrival city list is empty\n";
      return;
    }
  while(temp!= NULL)
    {
      cout << temp->arrCity << fixed << setprecision(2) << "(" << temp->price << "), ";
      temp = temp->next;
    }
  cout <<"\n";
}
