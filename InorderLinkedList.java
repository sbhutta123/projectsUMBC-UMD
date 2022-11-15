

package listVersions;

import listVersions.NormalLinkedList.Node;

//this calss implements a sorted list by impelementing the comparable<T> 
//interface and extending the NormlaLinkedList<T> class. Also overrides
//some methods if they could be more efficient for a sorted list

public class InorderLinkedList<T extends Comparable<T>>
               extends NormalLinkedList<T> {
	
	
	//constructor
	public InorderLinkedList() {
		super();
		
	}
	
	@Override
	//adds new element in the place where its value is greater than the one
	//before and less than the one after it
	public void addNewEltToList(T newValue) {
		//if the value passed in is null, an exception is thrown
		 if (newValue == null)
			 throw new IllegalArgumentException("Cannot add null to object");
		 //if list is empty, makes head equal to the new node
		 if (head == null) {
			 head = new Node(newValue);
		 }
		 //if list is not empty, checks that the value is greter than head
		 else if (head != null) {
			 Node newNode = new Node(newValue);
			 //if the value is less than head's value, then makes newValue, 
			 //head's value and head.next equal to the old head value
			 if (head.getData().compareTo(newValue) > 0) {
				 newNode.setNextNode(head);
				 head = newNode;
			 }
			 //if value is greater than head's value, then traverses through
			 //list to find spot where newValue is less than the value of the
			 //next node
			 else {
				 Node curr = head;
				 while(curr.getNextNode() != null 
						 && curr.getNextNode().getData().compareTo(newValue) 
						 <= 0) {
					 curr = curr.getNextNode();
				 }
				 //updates list by putting the new node in between curr and 
				 //curr.next
				 newNode.setNextNode(curr.getNextNode());
				 curr.setNextNode(newNode);
			 }
		 }
	}
	
	@Override
	//counts the number of times a value occurs in the list
	public int occurrencesOfValue(T value) {
		//if null is passed in, an exception is thrown
		if (value == null) {
			throw new IllegalArgumentException("value cannot be null");
		}
	    Node curr = head;
	    int numOccurrences = 0;
	    int comparedTo = -1;
	    //traverses through list until a value greater than value occurs
	    //and counts number of times the value occurs before that happens and
	    //returns that number
	    while (curr != null) {
	    	comparedTo = curr.getData().compareTo(value);
	    	if (comparedTo == 0) {
	    		numOccurrences++;
	    	}
	    	else if (comparedTo > 0) {
	    		return numOccurrences;
	    	}
	    	curr = curr.getNextNode();
	    }
	    return numOccurrences;
	}
	
	@Override
	//finds the index of the value, but if the value does not occur in the list,
	//-1 is returned
	public int indexOfValue(T value) {
		//if null is passed in, an exception is thrown
		if (value == null) {
			throw new IllegalArgumentException("value cannot be null");
		}
	    int index = 0;
	    Node curr = head;
	    int comparedTo = -1;
	    //traverses through list and if value is found, returns the index
	    //if a value that is greater than the value occurs, then -1 is 
	    //returned because that means that the value does not occur in the list
	    while (curr != null) {
	    	comparedTo = curr.getData().compareTo(value);
	    	if (comparedTo == 0) {
	    		return index;
	    	}
	    	else if (comparedTo > 0) {
	    		return -1;
	    	}
	    	index++;
	    	curr = curr.getNextNode();
	    }
	    return -1;
	}
	
}
