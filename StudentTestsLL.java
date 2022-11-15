

package tests;

import org.junit.*;
import static org.junit.Assert.*;
import listVersions.NormalLinkedList;
import listVersions.InorderLinkedList;

//tests that test methods from the listVersions package
public class StudentTests {

	//tests the compareTo(NormalLinkedList<T> obj) method for 3 different cases
	//one where everything is the same, one where it is greater than other obj
	//and one where it is less than the other obj
  @Test public void studentTest1(){
	  assertEquals(1, TestData.list1().compareTo(TestData.list4()));
	  assertEquals(0, TestData.list1().compareTo(TestData.list1()));
	  assertEquals(-1, TestData.list4().compareTo(TestData.list1()));
  }
  
  //tests the addNewEltList(T value) method for both unsorted and sorted objects
  //utilizes the toString() method to ensure all values were inserted in the
  //correct order
  @Test public void studentTest2() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(3);
	  
	  assertEquals("13 16 3", list.toString());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("zebra");
	  newList.addNewEltToList("kite");
	  
	  assertEquals("apple kite koala zebra", newList.toString());
  }
  
  //tests the length() method for both unsorted and soreted lists
  @Test public void studentTest3() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(3);
	  
	  assertEquals(3, list.length());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("zebra");
	  newList.addNewEltToList("kite");
	  
	  assertEquals(4, newList.length());
	  
  }
  
  //tests the toString() method for edge cases (1 element) bor both unsorted and 
  //sorted lists
  @Test public void studentTest4() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  
	  assertEquals("13", list.toString());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  assertEquals("koala", newList.toString());
	  
	  
  }
  
  //checks that the clear() method works for unsorted and sorted lists
  //utilizes the length() method to test that list is empty
  @Test public void studentTest5() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(3);
	  
	  list.clear();
	  
	  assertEquals(0, list.length());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("zebra");
	  newList.addNewEltToList("kite");
	  
	  newList.clear();
	  
	  assertEquals(0, newList.length());
  }
  
  //tests the occurrencesOfValue() method for both sorted and unsorted
  //lists
  @Test public void studentTest6() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(16);
	  
	  assertEquals(1, list.occurrencesOfValue(13));
	  assertEquals(2, list.occurrencesOfValue(16));
	  assertEquals(0, list.occurrencesOfValue(3));
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("kite");
	  
	  assertEquals(1, newList.occurrencesOfValue("koala"));
	  assertEquals(2, newList.occurrencesOfValue("apple"));
	  assertEquals(0, newList.occurrencesOfValue("look"));
	  
  }
  
  //tests the indexOfValue() method for both unsorted and sorted lists
  //checks for error cases and edge cases as well as normal cases
  @Test public void studentTest7() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(16);
	  
	  assertEquals(1, list.indexOfValue(16));
	  assertEquals(0, list.indexOfValue(13));
	  assertEquals(-1, list.indexOfValue(5));
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("kite");
	  
	  assertEquals(0, newList.indexOfValue("apple"));
	  assertEquals(-1, newList.indexOfValue("bugs"));
	  assertEquals(2, newList.indexOfValue("kite"));
  }
  
  //tests the valueLocatedAtIndex() method for unsorted and sorted lists
  //checks that an exception is thrown when position is out of range
  //checks for edge cases and normal cases too
  @Test public void studentTest8() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(16);
	  
	  try {
		  list.valueLocatedAtIndex(3);
		  fail();
	  }
	  catch (IndexOutOfBoundsException iae) {
	  }
	  
	  assertEquals("16", list.valueLocatedAtIndex(1).toString());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("kite");
	  
	  try {
		  newList.valueLocatedAtIndex(4);
		  fail();
	  }
	  catch (IndexOutOfBoundsException iae) {
	  }
	  
	  assertEquals("apple", newList.valueLocatedAtIndex(1).toString());
	  newList.clear();
	  
	  assertEquals(null, newList.valueLocatedAtIndex(0));
	  
  }
  
  //checks the removeValuesBetween method for unsorted and sorted lists
  //removes from head, middle, and tail (end)
  @Test public void studentTest9() {
	  NormalLinkedList<Integer> list= new NormalLinkedList<>();
	  list.addNewEltToList(13);
	  list.addNewEltToList(16);
	  list.addNewEltToList(16);
	  
	  list.removeValuesBetween(12, 13);
	  assertEquals ("13 16 16", list.toString());
	  
	  list.removeValuesBetween(13, 16);
	  assertEquals("16", list.toString());
	  
	  InorderLinkedList<String> newList = new InorderLinkedList<>();
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("kite");
	  
	  newList.removeValuesBetween("koala", "apple");
	  assertEquals("apple apple kite koala", newList.toString());
	  
	  newList.removeValuesBetween("koala", "ape");
	  assertEquals("apple apple kite koala", newList.toString());
	  
	  newList.removeValuesBetween("apple", "apple");
	  assertEquals("apple kite koala", newList.toString());
	  
	  newList.addNewEltToList("kite");
	  
	  newList.removeValuesBetween("kite", "koala");
	  assertEquals("apple", newList.toString());
	  
	  newList.addNewEltToList("koala");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("apple");
	  newList.addNewEltToList("kite");
	  
	  newList.removeValuesBetween("apple", "koala");
	  assertEquals("", newList.toString());
	  
  }
  
}
