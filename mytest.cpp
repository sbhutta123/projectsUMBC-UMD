#include "elevator.h"
class Tester{
public:
  bool insertAtHeadNorm();//tests that insertAtHead() works fro a normal case
  bool insertAtHeadError(); //Tests that insertAtHead() does not work for an error case (floor != (m_ground -1))
  bool insertAtTailNorm();//Tests that insertAtTail() works for a normal case
  bool insertAtTailError();// Tests that insertAtTail() works for an error case (floor != (m_top + 1))
  bool removeFloorNorm(); //tests that removefloor() works correctly for a normal case
  bool removeFloorError1(); //tests that removeFloor() throws an error when deleting floor that is out of range
  bool removeFloorError2(); // tests that removeFloor() does not return true when deleting a non-exisiting floor
  bool insertFloorNorm();//tests that insertFloor() works in a normal case
  bool insertFloorError(); //tests that insertFloor() throws an error when asked to insert something out of range
  bool insertFloorEdge(); //tests that insertFloor() does not insert a floor that already exists
  bool testAssignEdgeCase(); //tests an edge case for assignment operator
  bool testAssignNormCase();//tests a normal case for assignment operator
  bool testAssignEdgeCase2();//tests an edge case for assignment operator
  bool testCopyEdgeCase();//tests edge case for copy constructor
  bool testCopyNormCase();//tests normal case for copy constructor
  bool testValues(const Elevator& t1, const Elevator& t2);//checks if all values are equal in 2 objects
  bool testPointers(const Elevator& t1, const Elevator& t2);//checks that all pointers are inequal in 2 objects
  bool enterExitMove(); //checks enter,exit, and move function

};
int main(){
  Tester tester;
  { cout << "\nTesting insertAtTail() normal case:\n\n";
   if (tester.insertAtTailNorm() == true)
     cout << "\tNormal case (node inserted) passed!\n";
   else
    cout << "\tNormal case failed (node did not get inserted)!\n";
  }
  {
    cout <<"\nTesting insertAtTail() Error Case:\n\n";
    if (tester.insertAtTailError() == true)
      cout << "\tError case (node not inserted) passed!\n";
    else{
      cout << "\tError case (node inserted) failed!\n";
    }
  }
  {
    cout << "\nTesting insertAtHead() normal case:\n\n";
    if (tester.insertAtHeadNorm() == true)
      cout << "\tNormal case (node inserted) passed!\n";
    else
      cout << "\tNormal case failed (node did not get inserted)!\n";
  }
  {
    cout <<"\nTesting insertAtHead() Error Case:\n\n";
    if (tester.insertAtHeadError() == true)
      cout << "\tError case (node not inserted) passed!\n";
    else
      cout << "\tError case (node inserted) failed!\n";
  }
  {
    cout << "\nTesting insertFloor() normal case:\n\n";
    if (tester.insertFloorNorm() == true)
      cout << "\tNormal case (node inserted) passed!\n";
    else
      cout << "\tNormal case failed (node did not get inserted)!\n";
  }
  {
    cout << "\nTesting insertFloor() error case:\n\n";
    if (tester.insertFloorError() == true)
      cout << "\tError case passed!\n";
    else
      cout << "\tError case failed!\n";
  }
  {
    cout << "\nTesting insertFloor() edge case:\n\n";
    if (tester.insertFloorEdge() == true)
      cout << "\tEdge case (node not inserted) passed!\n";
    else
      cout << "\tEdge case failed (node inserted)!\n";
  }
  {
   cout << "\nTesting removeFloor() normal case:\n\n";
    if (tester.removeFloorNorm() == true)
      cout << "\tNormal case (everything was removed) passed!\n";
    else
      cout << "\tNormal case failed (not everything was removed)!\n"; 
  }
  {
    cout << "\nTesting removeFloor() error case:\n\n";
    if (tester.removeFloorError1() == true)
      cout << "\tError case passed!\n";
    else
      cout << "\tError case failed!\n";
  }
  {
    cout << "\nTesting removeFloor() error case:\n\n";
    if (tester.removeFloorError2() == true)
      cout << "\tError case (nothing was removed) passed!\n";
    else
      cout << "\tError case failed (deleted non-existing floor))!\n"; 
  }
  {
    cout << "\nTesting assignment operator edge case:\n\n";
    if (tester.testAssignEdgeCase() == true)
      cout << "\tEdge case (1 floor)) passed!\n";
    else
      cout << "\tEdge case failed (values and/or pointers are wrong))!\n";
  }
  {
    cout << "\nTesting assignment operator normal case:\n\n";
    if (tester.testAssignNormCase() == true)
      cout << "\tNormal case passed!\n";
    else
      cout << "\tNormal case failed (values and/or pointers are wrong))!\n";
  }
  {
    cout << "\nTesting assignment operator edge case:\n\n";
    if (tester.testAssignEdgeCase2() == true)
      cout << "\tEdge case (2 floors) passed!\n";
    else
      cout << "\tEdge case failed (values and/or pointers are wrong))!\n";
  }
  {
    cout << "\nTesting copy constructor edge case:\n\n";
    if (tester.testCopyEdgeCase() == true)
      cout << "\tEdge case (1 floors) passed!\n";
    else
      cout << "\tEdge case failed (values and/or pointers are wrong))!\n";
  }
  {
    cout << "\nTesting copy constructor normal case:\n\n";
    if (tester.testCopyNormCase() == true)
      cout << "\tNormal case passed!\n";
    else
      cout << "\tNormal case failed (values and/or pointers are wrong))!\n";
  }
  {
    cout << "\nTesting enter/exit/move normal case:\n\n";
    if (tester.enterExitMove() == true)
      cout << "\tNormal case passed!\n";
    else
      cout << "\tNormal case failed!\n";
  }
  cout << endl;
   return 0;
}

bool Tester::insertAtTailNorm(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i =0; i < 300; i++){
    trueFalse = anElev.insertAtTail(i); //inserts 300 floors
    if (trueFalse == false){
      return false;
    }
  }
  return true;
}

bool Tester::insertAtTailError(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 0; i < 300; i++){ 
    if (i ==3){ //changes input to be out of range
      i = 10;
    }
    trueFalse = anElev.insertAtTail(i);
    if (i == 10 && trueFalse == false){ //if floor is too high to be inserted, return true
      anElev.dump();
      return true;
    }
    else if (trueFalse == false && i != 10){ //if floor is inserted even though out of bounds, returns false
      return false;
    }
  }
  return true;
}

bool Tester::insertAtHeadNorm(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 300; i > 0; i--){ //inserts 300 floors using insertAtHead()
    trueFalse = anElev.insertAtHead(i);
    if (trueFalse == false){
      return false;
    }
  }
  return true;
}

bool Tester::insertAtHeadError(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 300; i > 0; i--){
    if (i == 297){ //changes value to be out of range
      i = 295;
    }
    trueFalse = anElev.insertAtHead(i);
    if (trueFalse == false && i != 295){ // if inserted, returns false
      return false;
    }
    else if (trueFalse == false && i == 295){ //if not inserted, returns true
      return true;
    }
  }
  return false;
}

bool Tester::insertFloorNorm(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 0; i < 16; i++){ //populates list
    anElev.insertAtTail(i);
  }
  for (int i = 1; i < 15; i++){
    anElev.removeFloor(i); //removes floor from list
    trueFalse = anElev.insertFloor(i);//inserts it back into list
    if (trueFalse == false){
      return false;
    }
  }
  return true;
}

bool Tester::insertFloorError(){
  Elevator anElev;
  for (int i = 0;i <= 1; i++){
     if (i > 0){
       try{ //tries to insert floor into a list with only 1 floor
        anElev.insertFloor(i);
       }
        catch(std::out_of_range &e){ //catches an error
          cout << e.what() << endl;
          return true;
      }
     }
     anElev.insertFloor(i);
  }
  return false;
}

bool Tester::insertFloorEdge(){
 Elevator anElev;
 bool trueFalse = false;
  for (int i = 0;i <= 1; i++){
    trueFalse = anElev.insertFloor(0);//tries to insert the floor twice
    if (i > 0 && trueFalse != false){
      return false;
    }
    else if (i > 0 && trueFalse == false){
      return true;
    }
  }
  return false;
}

bool Tester::removeFloorNorm(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 0; i < 50; i++){ //populates list with 50 floors
    anElev.insertAtTail(i);
  }
  for (int i = 0; i < 50; i++){
    trueFalse = anElev.removeFloor(i); //removes all floors
    if (trueFalse == false){
      return false;
    }
  }
  anElev.dump();
  return true;
}

bool Tester::removeFloorError1(){
  Elevator anElev;
  for (int i = 0; i < 20; i++){
    anElev.insertAtTail(i); //populates list
  }
  try{
      anElev.removeFloor(21); //tries to remove floor that is out of range
    }
    catch(std::out_of_range &e){ //catches error
      cout << e.what() << endl;
      return true;
    }
    return false;
}
bool Tester::removeFloorError2(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 0; i< 15; i++){ //populates list
    anElev.insertAtTail(i);
  }
  trueFalse = anElev.removeFloor(2); //tries to remove the same floor twice
  trueFalse = anElev.removeFloor(2);
  if (trueFalse == false){
    return true;
  }
  return false;
}

bool Tester::testAssignEdgeCase(){
  Elevator anElev;
  bool trueFalse = false;
  anElev.insertAtHead(0);//inserts one floor into anElev
  Elevator anElev2;
  anElev2.insertAtHead(3);//inserts one floor to anElev2
  anElev2 = anElev; //assigns anElev2 to anElev

  //checks values and pointers
  trueFalse = testValues(anElev,anElev2);
  trueFalse = trueFalse + testPointers(anElev,anElev2);
  return trueFalse;
} 
bool Tester::testAssignNormCase(){
  Elevator anElev;
  Elevator anElev2;
  bool trueFalse = false;
  for (int i = 0; i < 15; i++){ //populates both elevators
    if (i > 5){
      anElev2.insertAtTail(i);
    }
    anElev.insertAtTail(i);
  }
  anElev.dump();
  anElev2 = anElev; //assigns amElev2 to anElev
  anElev2.dump();
  trueFalse = testValues(anElev,anElev2); //checks values and pointers
  trueFalse = trueFalse + testPointers(anElev,anElev2);
  return trueFalse;
}
bool Tester::testAssignEdgeCase2(){
  Elevator anElev;
  Elevator anElev2;
  bool trueFalse;
  anElev.insertAtTail(1); //puts 2 floors in
  anElev.insertAtTail(2);
  anElev2 = anElev;
  trueFalse = testValues(anElev2,anElev); //checks values and pointers
  trueFalse = trueFalse + testPointers(anElev2,anElev);
  return trueFalse;
}

bool Tester::testValues(const Elevator& t1, const Elevator& t2){
  bool result = true;
  int count = 0;
  //checks if any values differ from each other
	Floor *curr = t1.m_ground;
  Floor *curr2 = t2.m_ground;
  while (curr != nullptr){
    if (curr->m_floorNum != curr2->m_floorNum){
      count++;
    }
    curr = curr->m_next;
    curr2 = curr2->m_next;
  }
  //makes sure member vars are equal
  if (count == 0){
    result = true;
  }
  else
    result = false;
  return result;
}
bool Tester::testPointers(const Elevator& t1, const Elevator& t2){
  bool result = true;
  int count = 0;
  //checks that pointers are different
  Floor *curr = t1.m_ground;
  Floor *curr2 = t2.m_ground;
  while (curr != nullptr){
    if (curr == curr2){
      count++;
    }
    curr = curr->m_next;
    curr2 = curr2->m_next;
  }
  //checks that pointers are not equal
  if (count == 0){
    result = true;
  }
  else
    result = false;
  return result;
}

bool Tester::testCopyEdgeCase(){
  Elevator anElev;
  bool trueFalse;
  for (int i = 0; i < 1; i++){ //populates list with 1 floor
    anElev.insertAtTail(i);
  }
  Elevator *anElev2 = new Elevator(anElev); //calls copy constructor
  trueFalse = testValues(*anElev2,anElev); //checks values and pointers
  trueFalse = trueFalse + testPointers(*anElev2,anElev);
  delete anElev2;
  return trueFalse;
}

bool Tester::testCopyNormCase(){
  Elevator anElev;
  bool trueFalse;
  for (int i = 0; i < 12; i++){ //populates list
    anElev.insertAtTail(i);
  }
  //anElev.dump();
  Elevator *anElev2 = new Elevator (anElev); //calls copy constructor
  trueFalse = testValues(*anElev2,anElev);
  trueFalse = trueFalse + testPointers(*anElev2,anElev);//checks values and pointers
  anElev.removeFloor(2);
  delete anElev2;
  return trueFalse;
}

bool Tester::enterExitMove(){
  Elevator anElev;
  bool trueFalse = false;
  for (int i = 0; i < 14; i++){ //populates list
    anElev.insertAtTail(i);
  }
  trueFalse = trueFalse + anElev.enter(3,"Alice"); //checks enter()
  trueFalse = trueFalse + anElev.move(3,7);//checks move()
  if (anElev.exit(7,"Alice") == "Alice"){ // checks exit()
    trueFalse = trueFalse + true;
  }
  
  return trueFalse;
}