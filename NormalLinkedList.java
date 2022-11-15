//Name: Shifa Bhutta
//DID: sbhutta
//UID: 117275223
//Section: 0102
//I pledge on my honor that I have not given or received any unauthorized 
//assistance on this assignment.

package listVersions;

import java.lang.IndexOutOfBoundsException;

//this class implements an unsorted linked list and possesses an inner Node 
//class that is used to implement the unsorted list as well as the sorted linked
//list in the inOrderLinkedList subclass
public class NormalLinkedList<T extends Comparable<T>>
               implements Comparable<NormalLinkedList<T>> {
 //used to implement both the unsorted and sorted linked lists
  public class Node {
	  private T data;
	  private Node next;
	  
	  //Node constructor
	  public Node(T data) {
		  this.data = data;
		  next = null;
	  }
	  
	  //setter for next node
	  public void setNextNode(Node newNode) {
		  this.next = newNode;
	  }
	  //getter for next node
	  public Node getNextNode() {
		  return this.next;
	  }
	  //getter for data of node
	  public T getData() {
		  return this.data;
	  }
  }
	  
  protected Node head;
  
  //constructor for NormalLinkedList
  public NormalLinkedList() {
	  head = null;
  }

  //throws an error if null is passed in; otherwise, it finds last element in
  //the list and then sets that element.next equal to a new node containing 
  //the data passed in
  public void addNewEltToList(T newValue) {
	//checks if newValue is null and throws an error if it is
    if (newValue == null)
    	throw new IllegalArgumentException("Cannot add null to object");
    //if head is not null, traverses the list to find the last element and then
    //sets that element.next equal to the new node
    else if (head != null) {
    	Node curr = head;
    	while (curr.next != null) {
    		curr = curr.next;
    	}
    	curr.next = new Node(newValue);
    }
    //if head is null, then it sets head equal to a new node containing the data
    //passed in
    else if (head == null){
    	head = new Node(newValue);
    }
  }

  //returns the length of the linked list
  public int length() {
	//if the list is empty, it returns 0
    if (head == null)
    	return 0;
    //if the list is not empty, it traverses the list while counting the number
    //of elements present and then returns that number
    else {
    	int numElems = 0;
    	Node curr = head;
    	while(curr != null) {
    		numElems += 1;
    		curr = curr.next;
    	}
    	return numElems;
    }
  }

  @Override
  //returns a string of all values in the list seperated by a space
  public String toString() {
	  Node curr = head;
	  String newString = "";
	  //if the list is empty, it returns an empty string
	  if (head == null) {
		  return newString;
	  }
	  //if list is not empty, it calls toString() on every value in the list
	  //and it puts a space between every value
	  while (curr.next != null) {
		  newString += curr.data.toString();
		  curr = curr.next;
		  newString += " ";
	  }
	  //when the last element is reached, it is added to the string but a space
	  //is not added
	  newString += curr.data.toString();
	  return newString;
  }

  //clears the linked list
  public void clear() {
    head = null;
  }

  //counts the number of occurrences of a value
  public int occurrencesOfValue(T value) {
	//if value passed in is null, then an exception is thrown
	if (value == null) {
		throw new IllegalArgumentException("value cannot be null");
	}
	//traverses through the list and counts number of times value occurs
	//in the list and then returns the number
    Node curr = head;
    int numOccurences = 0;
    int comparedTo = -1;
    while (curr != null) {
    	comparedTo = curr.data.compareTo(value);
    	if (comparedTo == 0) {
    		numOccurences++;
    	}
    	curr = curr.next;
    }
    return numOccurences;
  }

  //finds the index of the value passed in 
  public int indexOfValue(T value) {
	//if value is passed in as null, then an exception is thrown
	if (value == null) {
		throw new IllegalArgumentException("value cannot be null");
	}
	//traverses through list to find the first occurrence of the value
	//and then returns the index or if the value does not occur in the list,
	//-1 is returned
    int index = 0;
    Node curr = head;
    int comparedTo = -1;
    while (curr != null) {
    	comparedTo = curr.data.compareTo(value);
    	if (comparedTo == 0) {
    		return index;
    	}
    	index++;
    	curr = curr.next;
    }
    return -1;
  }

  //finds the value located at the position passed in
  public T valueLocatedAtIndex(int position) {
	//if poition is an invalid number (out of range), throws an exception
    if ((position >= length() || position < 0) && position != 0) {
    	throw new IndexOutOfBoundsException("That position does not exist");
    }
    //traverses through list until it finds the position and then returns the 
    //value there
    else {
    	int count = 0;
    	Node curr = head;
    	while (curr != null) {
    		if (position == count) {
    			return curr.data;
    		}
    		count++;
    		curr = curr.next;
    	}
    	return null;
    }
  }

  //removes values from the first value passed in to the second value passed in
  public void removeValuesBetween(T fromValue, T toValue) {
    int indexFrom = indexOfValue(fromValue);
    int indexTo = indexOfValue(toValue);
    //checks to make sure the first value exists in the list and the second
    //value exists and occurs after the first value, then proceeds to remove
    //values from the list between first and second values
    if (indexFrom >= 0 && indexTo >= indexFrom) {
    	Node curr = head;
    	while (curr.data.compareTo(fromValue) != 0) {
    		curr = curr.next;
    	}
    	while (curr.data.compareTo(toValue) != 0) {
    		remove(curr.data);
    		curr = curr.next;
    	}
    	remove(curr.data);
    }
  }
  
  //removes value from the list
  private void remove(T value) {
	  if (head.data == value) {
		  head = head.next;
	  }
	  else {
		  Node prev = null;
		  Node curr = head;
		  //finds first occurence of value in the list and then removes it
		  while (curr.data.compareTo(value) != 0) {
			  prev = curr;
			  curr = curr.next;
		  }
		  prev.next = curr.next;
	  }
	  
  }

  @Override
  //compares one object to another
  public int compareTo(NormalLinkedList<T> otherList) {
    Node curr = head;
    Node otherCurr = otherList.head;
    int comparedTo = 0;
    //traverses through the list until either one value is greater than or
    //smaller than the other values and then returns a positive or negative 
    //number depending on if the value from the other lust was greater than or 
    //smaller. If every value is the same and in the same order, then 0 is
    //returned
    while (curr != null) {
    	comparedTo = curr.data.compareTo(otherCurr.data);
    	if (comparedTo != 0) {
    		return comparedTo;
    	}
    	curr = curr.next;
    	otherCurr = otherCurr.next;
    }
    return comparedTo;
  }

}
