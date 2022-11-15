import java.util.ArrayList;
import java.util.Collection;

//This class is a singleton class and it implements an EmptyPBST object
//it contains all of the methods for an EmptyPBST object
@SuppressWarnings({"unchecked", "rawtypes"})
public class EmptyPBST<K extends Comparable<K>, V> extends PBST<K, V> {
	
	private static EmptyPBST emptyTree;
	
  //constructor, and it is private because it is only used within the class
  //so that only one instance of this class can be made
  private EmptyPBST() {
	  
  }

  //creates the instance of this class (if not already made) and returns it
  public static EmptyPBST getInstance() {
	  if (emptyTree == null) {
		  emptyTree = new EmptyPBST();
	  }
    return emptyTree;
  }

  //returns new nonEmpty object containing the key and value passed in
  public NonemptyPBST<K, V> addKeyValuePair(K newKey, V newValue) {
	  if (newKey == null || newValue == null) {
		  throw new IllegalArgumentException("Invalid");
	  }
    return new NonemptyPBST(newKey, newValue);
  }

  //returns 0 because it contains no values
  public int numPairs() {
    return 0;
  }

  //returns null because there are no values in the object
  public V getValueByKey(K keyToLookUp) {
    return null;
  }

  //throws an EmptyPBSTException because the tree is empty
  public K largestKey() throws EmptyPBSTException {
    throw new EmptyPBSTException();
  }

  //throws an EmptyPBSTException because the tree is empty
  public K smallestKey() throws EmptyPBSTException {
    throw new EmptyPBSTException();
  }

  //throws an IllegalArgumentException becasue the tree is empty
  public int pathBalance(K keyToFind) {
    throw new IllegalArgumentException("invalid");
  }

  //returns an empty Collection because the object is empty
  public Collection<K> collectionOfKeys() {
	Collection<K> elements = new ArrayList<K>();  
    return elements;
  }

  //returns the emptyPBST
  public PBST<K, V> removeKeyValuePair(K keyToRemove) {
    return this;
  }

  //returns an empty string because the tree is empty
  public String toString() {
    return "";
  }

 @Override
 //returns null because it is not needed to fill the Collection
 public Collection<K> keyCollection(Collection<K> elements) {
	return null;
}

}
