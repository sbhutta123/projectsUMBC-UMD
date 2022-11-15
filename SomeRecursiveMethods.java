//this class consists of recursive methods that return the sum of an element's
//location(s), location of an element, a list that is a mirror of the list
//inputted, and returns a new list that is based on the parameters inputted
public class SomeRecursiveMethods {
	
  

  //throws an exception if a null object was given, ele calls a helper recursive 
  //method that returns the sum of the element's location(s) 
  public static <T> int sumEltLocations(UMCPList<T> list, T element) {
	  if (element == null || list == null) {
		  throw new IllegalArgumentException("invalid");
	  }
	  else {
		  return sumLocations(list, element,1);
	  }
  }
  //returns the sum of the element's location, is given same parameters as 
  //parent method but also has an additional field called index that keeps
  //track of which index we are looking at. returns the sum of element's 
  //location(s)
  public static <T> int sumLocations(UMCPList<T> list, T element,int index) {
	  //if list is empty or if index of list does't exist , returns 0
	  if (list.get(index-1) == null) {
		  return 0;
	  }
	  //if the index is equal to a location of the element, then we add index to
	  //the recursive call and call the method on the next index
	  else if (list.get(index-1).equals(element)) {
		  return index + sumLocations(list,element,index+1);
	  }
	  //if the index does not contain the element, then we just call the method 
	  //on the next index
	  else {
		  return sumLocations(list,element,index + 1);
	  }
  }

  //if a null parameter was passed in throws an exception, 
  //else if all parameters are valid then calls the recursive
  //helper method which returns the location of the nth occurence
  public static <T> int locOfOccurrence(UMCPList <T> list, T element,
                                             int n) {
    if (element == null || list == null) {
    	throw new IllegalArgumentException("Invalid");
    }
    else {
	  return locationOfOcc(list,element,n,1,false);
    }
  }
  
  //this method uses all of the same parameters as its parent method, but also
  //contains an additional field called index that keeps track of the index we 
  //are checking. Also contains a field that keeps track of if element occurs in
  //list. Returns the location of the nth occurence of element
  public static <T> int locationOfOcc(UMCPList <T> list, T element,
          int n, int index, boolean found) {
	  //if element is not in list or if not in list n times, then -1 is returned
	  if (n < 1 || index == list.size() && !list.get(index -1).equals(element) 
			  && !found || index == list.size() && 
			  !list.get(index -1).equals(element) && n > 0){
		  return -1;
	  }
	  //if n = 1, and found the elemt in list, then index is returned
	  else if (list.get(index - 1).equals(element) && n == 1) {
		  return index;
	  }
	  //if the list object we are checking is not equal to the object we are
	  //looking for then only index is changed in the recursive call
	  else if (!list.get(index -1).equals(element))
		  return locationOfOcc(list,element, n, index+1,found);
	  
	  //else if we are at a location of element, then n is decremented, found is 
	  //true and index is incremented
	  else {
		  return locationOfOcc(list, element, n-1,index+1,true);
	  }
  }

  //if parameter is null, throws an exception, else calls a recursive helper 
  //method that returns a mirrorImage of the parameter
  public static <T> UMCPList<T> mirrorImage(UMCPList<T> list) {
    if (list == null) {
    	throw new IllegalArgumentException("Invalid");
    }
    else {
    	//creates a new list and calls recursive helper method
    	UMCPList<T> newList = new UMCPList<T>();
    	return mirror(list,newList,1);
    }
  }

  //has 2 additional fields (newList and index). newList is an empty list that 
  //will become a mirror image of the original list and index keeps 
  //track of which index we are looking at
  public static <T> UMCPList<T> mirror(UMCPList<T> list, UMCPList<T> newList,
		  int index){
	  //if newList's size is double that of list, newList is returned
	  if (newList.size() == 2 * list.size()) {
		  return newList;
	  }
	  //adds the element and then calls recursive function and then adds
	  //each element again, in the opposite order (x y --> x y y x)
	  else if (index <= list.size() ){
		  newList.add(list.get(index -1));
		  mirror(list,newList,index + 1);
		  newList.add(list.get(index - 1));
		  
	  }
	  return newList;
  }
  
  //throws an exception if list is null, else calls a recursve helper
  //method that returns a newList that contains every nth element starting from
  //startPos and the size is numValues or smaller if not enough elements in
  //range
  public static <T> UMCPList<T> makeList(UMCPList<T> list, int numValues,
                                         int startPos, int n) {
    if (list == null) {
    	throw new IllegalArgumentException("Invalid");
    }
    else {
    	//creates an empty list and then passes it into the recursive helper 
    	//method
    	UMCPList<T> newList = new UMCPList<T>();
    	return makeNewList(list,newList,numValues,startPos, n);
    }
  }
  
  //method that returns a newList that contains every nth element starting from
  //startPos and the size is numValues or smaller if not enough elements in
  //range
  public static <T> UMCPList<T> makeNewList(UMCPList<T> list, 
		  UMCPList<T> newList, int numValues, int startPos, int n){
	  //if list is of size numValues or not enough elements in list, newList
	  //is returned
	  if (newList.size() == numValues || startPos > list.size()) {
		  return newList;
	  }
	  //else, add element to new list and then add n to startPos in the 
	  //recursive call
	  else {
		  newList.add(list.get(startPos - 1));
		  makeNewList(list,newList,numValues, startPos + n, n);
	  }
	return newList;
  }

}
