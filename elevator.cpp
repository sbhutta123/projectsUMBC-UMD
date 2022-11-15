// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
Elevator::Elevator(){ //constructor
  m_ground = nullptr;
  m_top = m_ground;
}

Elevator::~Elevator(){//destructor (calls clear() to deallocate memory)
  clear();
}

void Elevator::clear(){ //deallocates all memory in doubly linked list
  Floor *curr = m_ground;
  int count = 0;
  while (curr != nullptr){
    m_ground = curr;
    curr = curr->m_next;
    delete m_ground;
    count++;
  }
  m_ground = nullptr;
  m_top = nullptr;
}

bool Elevator::insertAtHead(int floor, string passenger){
  //takes in the floor number and empty string and inserts it into the head of the list if empty or if floor is = (m_ground - 1)
  if (m_ground == nullptr){
    Floor *temp = new Floor(floor, passenger);//new Floor object
    temp->m_previous = nullptr;
    temp->m_next = nullptr;
    m_ground = temp;//sets m_ground and m_top equal to new floor object because list has no other objects in it
    m_top = temp;
    return true;
  }
  else{
    if (floor == (m_ground->m_floorNum) - 1){ //checks if floor should be inserted
      Floor *temp = new Floor(floor, passenger);
      m_ground->m_previous = temp; //sets the pointers
      temp->m_next = m_ground;
      m_ground = temp;//changes m_ground 
      return true;
    }
  }
  return false;
}

bool Elevator::insertAtTail(int floor, string passenger){
  //takes in the floor number and empty string and inserts it at the end of the list if list is empty or floor = (m_top + 1)
  if (m_ground == nullptr){ //checks if list is empty
    Floor *temp = new Floor (floor, passenger);
    temp->m_next = nullptr; //sets the pointers
    temp->m_previous = nullptr;
    m_top = temp; //sets m_top and m_ground = temp because it only object in the list
    m_ground = temp;
    return true;
  }
  else if (m_top != nullptr){
    if ((m_top->m_floorNum) + 1 == floor){ //checks if floor should be inserted
      Floor *temp = new Floor (floor, passenger);
      //sets the pointers
      m_top->m_next = temp;
      temp->m_previous = m_top;
      m_top = temp; // sets m_top = temp (new floor object)
      return true;
    }
  }
  return false;
}

bool Elevator::removeFloor(int floor){
  //function takes in floor number and removes it from list if it exists in the list
    Floor *curr = m_ground;
    if (m_ground->m_floorNum == floor){ //checks to see if removing m_ground
      if (m_ground->m_next != nullptr){ //if m_ground is not only object in the list, deletes m_ground and sets m_ground to m_ground->m_next
        curr = m_ground->m_next;
        curr->m_previous = nullptr;
        delete m_ground;
        m_ground = curr;
        return true;
      }
      else if (m_ground->m_next == nullptr){ //if m_ground is only thing in list, deletes m_ground and sets it and m_top to nullptr
        delete m_ground;
        m_ground = nullptr;
        m_top = nullptr;
        return true;
      }
    }

    if (m_ground->m_floorNum > floor || m_top->m_floorNum < floor){ //if out of range, throws an error
      throw out_of_range("\tERROR in removeFloor(). Floor is out of range");
      return false;
    }

    if (checkFloor(floor) == false){ //checks that floor exists
      return false;
    }

    //checks to see if floor is closer to m_ground or m_top
    int count = 0;
    int tailDiff = m_top->m_floorNum - floor;
    if (tailDiff < 0){
      tailDiff = tailDiff* -1;
    }
    int headDiff = floor - m_ground->m_floorNum;
    if (headDiff < 0){
      headDiff = headDiff * -1;
    } 
    //if closer to m_top, traverses from m_top
    if (tailDiff < headDiff){
      curr = m_top;
      while (curr != nullptr){
        if (curr->m_floorNum == floor){ //finds floor in list if it exists and removes it
          if (curr->m_next != nullptr){
            curr->m_next->m_previous = curr->m_previous;
            curr->m_previous->m_next = curr->m_next;
            delete curr;
            return true;
          }
          else if (curr->m_next == nullptr){ //checks to see if m_top is the floor being removed and deletes it if needed
            curr = curr->m_previous;
            curr->m_next = nullptr;
            delete m_top;
            m_top = curr;
            return true;
          }
          count++;
        }
        curr = curr->m_previous;
      }
    }
    //if closer to m_ground or equidistant, it traverses from m_ground to m_top
    else if (headDiff < tailDiff || headDiff == tailDiff){
      curr = m_ground;
      while (curr != nullptr){
        if (curr->m_floorNum == floor){
          if (curr->m_next != nullptr){ //deletes floor if not last in the list
            curr->m_next->m_previous = curr->m_previous;
            curr->m_previous->m_next = curr->m_next;
            delete curr;
            return true;
          }
          else if (curr->m_previous != nullptr){ //deletes floor if not first in the list
            curr->m_previous->m_next = curr->m_next;
            delete curr;
            return true;
          }
          count++;
        }
        curr = curr->m_next;
      }
    }
  return false;
}
bool Elevator::insertFloor(int floor){
  //takes in floor number and inserts it 
    Floor *curr = m_ground;
    if (m_ground == nullptr){ //if list is empty, inserts floor
      insertAtHead(floor,"");
      return true;
    }
    else if (m_ground->m_floorNum > floor || m_top->m_floorNum < floor){ // if floor is out of range, throws an error
      throw out_of_range("\tERROR in insertFloor(). Floor is out of range");
      return false;
    }
    if (checkFloor(floor) == true){ //checks that floor does not already exist 
      return false;
    }

    //checks to see if floor is closer to m_ground or m_top
    int tailDiff = m_top->m_floorNum - floor;
    if (tailDiff < 0){
      tailDiff = tailDiff* -1;
    }
    int headDiff = floor - m_ground->m_floorNum;
    if (headDiff < 0){
      headDiff = headDiff * -1;
    } 

    //if closer to m_top, traverses from m_top
    if (tailDiff < headDiff){
      curr = m_top;
      Floor *temp = new Floor(floor,"");
      while (curr != nullptr){
        if (curr->m_previous->m_floorNum < floor){ //finds location where floor needs to be inserted
        //inserts floor
          temp->m_next = curr; 
          temp->m_previous = curr->m_previous;
          curr->m_previous->m_next = temp;
          curr->m_previous = temp;
          return true;
        }
        curr = curr->m_previous;
      }
    }

    //traverses from m_ground if closer or equidistant to m_ground
    else if (headDiff < tailDiff || headDiff == tailDiff){
      curr = m_ground;
      Floor *temp = new Floor(floor,"");
      while (curr != nullptr){
        if (curr->m_next->m_floorNum > floor){ //finds location where floor needs to be inserted
        //inserts floor
          temp->m_previous = curr;
          temp->m_next = curr->m_next;
          curr->m_next->m_previous = temp;
          curr->m_next = temp;
          return true;
        }
        curr = curr->m_next;
      }
    }
  return false;
}
bool Elevator::checkFloor(int floor){
  if (m_ground->m_floorNum > floor || m_top->m_floorNum < floor){ //throws an error if floor is out of range
    throw out_of_range("\tERROR in checkFloor(). Floor is out of range");
    return false;
  }
  Floor *curr = m_ground;
  while (curr != nullptr){ //traverses list to see if floor is in list
    if (curr->m_floorNum == floor){ //if in list, return true
      return true;
    }
    curr = curr->m_next;
  }
  return false;
}
bool Elevator::move(int origin, int destination){
  if (m_ground->m_floorNum > origin || m_top->m_floorNum < destination ){ //if origin or destination is out of range, throws an error
    throw out_of_range("\tERROR in move(). Origin and/or destination is out of range");
    return false;
  }

  string passenger = "";
  if (origin < destination){ //if origin is < destination, traverses from m_ground
    Floor *curr = m_ground; 
    while (curr != nullptr){
      if (curr->m_floorNum == origin){ // if floor is origin makes m_passenger = ""
        passenger = curr->m_passenger;
        curr->m_passenger = "";
      }
      if (curr->m_floorNum == destination){ //if floor is destination makes m_passenger = passenger
        curr->m_passenger = passenger;
        return true;
      }
      curr = curr->m_next;
    }
    return false;
  }

  // if origiin > destination, traverses from m_top
  else if (origin > destination){
    Floor *curr = m_top;
    while (curr != nullptr){
      if (curr->m_floorNum == origin){ // if the floor is origin, makes m_passeneger = ""
        passenger = curr->m_passenger;
        curr->m_passenger = "";
      }
      if (curr->m_floorNum == destination){ //if the floor is destination, m_passenger = passenger 
        curr->m_passenger = passenger;
        return true;
      }
      curr = curr->m_previous;
    }
  }
  return false;  
}
string Elevator::exit(int floor, string passenger){
  Floor *curr = m_ground;
  while(curr != nullptr){ //traverses list to find floor where passeneger is exiting
    if (curr->m_floorNum == floor && curr->m_passenger == passenger){ //if floor is found and there is a passenger on it with the name passed in, passeneger is returned
      curr->m_passenger = "";
      return passenger;
    }
    curr = curr->m_next;
  }
  return "";
}
bool Elevator::enter(int floor, string passenger){
  Floor *curr = m_ground;
  while (curr != nullptr){ //traverses list
    if (curr->m_floorNum == floor && curr->m_passenger == ""){ //if floor is found and no passenege ron it, passengeer enters elevator
      curr->m_passenger = passenger;
      return true;
    }
    curr = curr->m_next;
  }  
  return false;
}
Elevator::Elevator(const Elevator & rhs){
  if (rhs.m_ground == nullptr){ // if rhs is empty, makes m_gorund and m_top = nullptr
    m_ground = nullptr;
    m_top = nullptr;
  }
  else if (rhs.m_ground != nullptr){ //if rhs is not empty, sets all values qual to rhs values
    Floor *curr = rhs.m_ground->m_next;
    m_ground = nullptr;
    m_top = nullptr;
    insertAtTail(rhs.m_ground->m_floorNum, rhs.m_ground->m_passenger);
    while (curr != nullptr){ //traverses list and creates a deep copy of rhs 
      Floor *temp = new Floor(curr->m_floorNum, curr->m_passenger);
      m_top->m_next = temp;
      temp->m_previous = m_top;
      m_top = temp;
      curr = curr->m_next;
    }  
  }
}

const Elevator & Elevator::operator=(const Elevator & rhs){
 if (this != &rhs){ //checks for self-assignment 

   if (m_ground != nullptr){ //clears everything from the list
    clear();
   }
   if (rhs.m_ground != nullptr){
    insertAtHead(rhs.m_ground->m_floorNum, rhs.m_ground->m_passenger);
    Floor *curr = rhs.m_ground->m_next;
    while(curr != nullptr){ //populates list with rhs values
      Floor *temp = new Floor(curr->m_floorNum, curr->m_passenger);
      m_top->m_next = temp;
      temp->m_previous = m_top;
      m_top = temp;
      curr = curr->m_next;
    }
   } 
   else if (rhs.m_ground == nullptr){ // if rhs is empty makes this empty
     m_ground = nullptr;
     m_top = nullptr;
  }
 }
 return *this;   
}
void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}
