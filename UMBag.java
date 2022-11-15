import java.util.HashSet;
import java.util.Set;

//this class acts like a set because it does not contain duplicate objects
public class UMBag {

	private int element;
	private int numOfOccurences;
	private Set<UMBag> newSet;
	
  //constructor
  public UMBag() {
	  newSet = new HashSet<>();
  }
  
  //overloaded constructor
  private UMBag(int elt) {
	  element = elt;
	  numOfOccurences = 1;
	  
  }
  
  //adds an object to bag that contains the int passed in or updates
  //the num of occurrences if the value already exists
  public void add(int elt) {
	  //if the value is already in the bag, adds 1 to numOfOccurrences
    if (contains(elt)) {
    	UMBag newObj = find(elt);
    	newObj.numOfOccurences++;;
    }
    //if the value is not in the bag, then a new object that contains the 
    //element is added
    else if (!contains(elt)) {
    	UMBag newObj = new UMBag(elt);
    	newSet.add(newObj);
    }
  }

  //helper function that finds a specific object in the bag
  private UMBag find(int elt) {
	  //iterates through bag until an object that contains the correct value
	  //is found
	  for (UMBag bag : newSet) {
		  if (bag.element == elt) {
			  return bag;
		  }
	  }
	  //if the value is not found, null is returned
	  return null;
  }
  
 //returns true if elt is in the bag and false otherwise
  public boolean contains(int elt) {
	  UMBag result = find(elt);
	  if (result == null) {
		  return false;
	  }
	  return true;
    
  }

  //returns number of occurrences of a specific element
  public int getCount(int elt) {
    UMBag bag = find(elt);
    if (bag == null) {
    	return 0;
    }
    return bag.numOfOccurences;
  }

  //returns number of objects in the bag 
  public int size() {
    int size = 0;
    for (UMBag bag: newSet) {
    	size += bag.numOfOccurences;
    }
    return size;
  }

  //returns a set that contains the values of all elements
  public Set<Integer> uniqueElements() {
	Set<Integer> intSet = new HashSet<>();
    if (newSet.isEmpty()) {
    	return intSet;
    }
    else {
    	for (UMBag bag: newSet) {
    		intSet.add(bag.element);
    	}
    }
    return intSet;
  }

  //removes an element from a bag if it exists
  public void remove(int elt) {
    if (contains(elt)) {
    	UMBag bag = find(elt);
    	bag.numOfOccurences--;
    	if (bag.numOfOccurences == 0) {
    		newSet.remove(bag);
    	}
    }
  }

}
