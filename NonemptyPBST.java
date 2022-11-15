import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collection;

@SuppressWarnings("unchecked")
//this class implements a Nonempty PBST and contains all of the methods for 
//a nonEmptyPBST. Some functions that it contains include: adding, removing,
//finding num of objects in tree, finding max, finding the min, getiing height
//of an object, and getting the value of an object
public class NonemptyPBST<K extends Comparable<K>, V> extends PBST<K, V> {
	
	public K key;
	public V value;
	public PBST<K,V> left;
	public PBST<K,V> right;
	
	

	//constructor
	public NonemptyPBST(K key, V value) {
		this.key = key;
		this.value = value;
		left = EmptyPBST.getInstance();
		right = EmptyPBST.getInstance();
	}

  //adds a key/value pair to the tree by traversing it based on BST properties
  public NonemptyPBST<K, V> addKeyValuePair(K key, V value) {
    if (key == null || value == null) {
    	throw new IllegalArgumentException("Invalid");
    }
    //if the key already exists, it changes the vakue to the value passed in
    //and returns a reference to the current object
    if (this.key.compareTo(key) == 0) {
    	this.value = value;
    	return this;
    }
    else {
    	//if (key is less than this.key, then traverses the left tree
    	if (key.compareTo(this.key) < 0) {
    		left = left.addKeyValuePair(key,value);
    	}
    	//otherwise it traverses the right tree
    	else {
    		right = right.addKeyValuePair(key,value);
    	}
    }
    //adds new object to the tree
    return this;
    
    
  }

  //returns size of tree by finding the sizes of both the left and right 
  //subtrees and then adding one for the root
  public int numPairs() {
    return 1 + left.numPairs() + right.numPairs();
  }

  //finds value of a given key by traversing the tree to find the key and its 
  //value
  public V getValueByKey(K keyToLookUp) {
    if (keyToLookUp == null) {
    	throw new IllegalArgumentException("invalid");
    }
    //if the key is found, we return its value
    if (this.key.compareTo(keyToLookUp) == 0) {
    	return this.value;
    }
    else {
    	//if (keyToLookUp is less than key, we traverse the left subtree
    	if (keyToLookUp.compareTo(this.key) < 0)
    		return left.getValueByKey(keyToLookUp);
    	//if keyToLookUp is greater than the key, we traverse the right subtree
    	if (keyToLookUp.compareTo(this.key) > 0)
    		return right.getValueByKey(keyToLookUp);
    }
    //return null if the key is not in the tree
    return null;
  }
  
  //finds maximum value in the tree
  public K largestKey() throws EmptyPBSTException {
	  //continuously calls largestKey() on right subtree until an exception
	  //occurs
    try {
    	return right.largestKey();
    } catch (EmptyPBSTException e) {
    	//when the exception occurs, the max value is returned 
    	return key;
    }
    
  }

  //finds minimum value in tree by traversing the left subtree
  public K smallestKey() throws EmptyPBSTException {
	  //continuously calls smallesKey() on the left subtree until an exception
	  //occurs
	  try {
	    	return left.smallestKey();
	    } catch (EmptyPBSTException e) {
	    	//when exception occurs, the smallest key is returned
	    	return key;
	    }
  }

  public int pathBalance(K keyToFind) {
	if (keyToFind == null) {
		throw new IllegalArgumentException("Invalid");
	}
	//if the keyToFind is the root, 0 is returned
    if (key.compareTo(keyToFind) == 0) {
    	return 0;
    }
    else {
    	//if keyToFind is less than key, 1 is subtracted from the result, and 
    	//we traverse the left subtree
    	if (keyToFind.compareTo(key) < 0) {
    		return left.pathBalance(keyToFind) - 1;
    	}
    	//else, we add 1 to the result and traverse the right subtree
    	else if (keyToFind.compareTo(key) > 0) {
    		return 1 + right.pathBalance(keyToFind);
    	}
    }
    //if keyToFind is not in the tree, an exception is thrown
    throw new IllegalArgumentException("Invalid");
  }

  //returns a collection of keys by creating a collection object and adding each
  //key value to it
  public Collection<K> collectionOfKeys() {
	  //a collection is created 
	  Collection<K> elements;

	  //object is initialized
	  elements = new ArrayList<K>();
	  //keys are added to the object
	  return keyCollection(elements);
  }
  
  //adds keys to the Collection object passed in
  public Collection<K> keyCollection(Collection<K> elements){
	  //adds the keys on both the left and right subtrees to the collection and
	  //returns the collection
	  left.keyCollection(elements);
	  elements.add(key);
	  right.keyCollection(elements);
	  
	  return elements;
	  
  }
  
  

  //removes an object from the tree by finding the keyToRemove and making
  //the appropriate operations.
  public PBST<K, V> removeKeyValuePair(K keyToRemove) {
	if (keyToRemove == null) {
		throw new IllegalArgumentException("Invalid");
	}
	//if we find the keyToRemove, then we have to figure out if it has a left 
	//and/or right subtree so that we know what operations have to be made in 
	//order to remove the correct object and rearrange the tree, so that
	//it maintains the BST properties 
    if (key.compareTo(keyToRemove) == 0) {
    	boolean hasLeft = true;
    	boolean hasRight = true;
    	//sees if the left tree is empty or not nd updates boolean as needed
    	try{
    		key = left.largestKey();
    		value = left.getValueByKey(key);
    	}catch(EmptyPBSTException e){
    	    hasLeft = false;
    	}
    	//sees if right tree is empty or not and updates boolean as needed
    	try{
    		key = right.smallestKey();
    		value = right.getValueByKey(key);
    	}catch(EmptyPBSTException f){
    		 hasRight = false;
    	}
    	//if it is a leaf, an empty PBST object is returned 
    	 if (!hasLeft && !hasRight) {
    	    return EmptyPBST.getInstance();
    	 }
    	 //if it only has a left subtree, then we call remove on that tree to
    	 //avoid duplicate keys and maintain the BST properties
    	 else if (!hasRight && hasLeft) {
    	      	 
    	    left = left.removeKeyValuePair(key);
    	    	  
    	 }
    	 //if it only has a right subtree, then we call remove on that tree to
    	 //avoid duplicate keys and maintain BST properties
    	 else if (!hasLeft && hasRight) {
    	    right = right.removeKeyValuePair(key);
    	    	 
    	 }
    	 //if both of its trees are nonempty, then we call remove on its right
    	 //tree because the key is the right tree's root value and wee need to
    	 //avoid duplicate values and maintain BST properties
    	 else if (hasRight && hasLeft) {
    	     right = right.removeKeyValuePair(key);
    	 }
    	 //returns the object
    	 return this;
    	      
    	      
    }
    //traverses PBST to find object we are looking for
    else {
    	//traverses left if keyToRemove is smaller than key
    	if (keyToRemove.compareTo(key) < 0) {
    		left = left.removeKeyValuePair(keyToRemove);
    	}
    	//traverses right if keyToRemove is bigger than key
    	else if (keyToRemove.compareTo(key) > 0) {
    		right = right.removeKeyValuePair(keyToRemove);
    	}
    }
    //returns a reference to current object if keyToRemove is not present
    return this;
  }

  //returns a string of the PBST using inOrder traversal and seperates keys and
  //values using a '/'
  public String toString() {
    String finalString = "";
    finalString += left.toString();
    finalString += key;
    finalString += '/';
    finalString += value;
    finalString += " ";
    finalString += right.toString();
    return finalString;
  }

}
