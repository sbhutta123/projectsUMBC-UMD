import java.util.Collection;

abstract public class PBST<K extends Comparable<K>, V> {

  abstract public NonemptyPBST<K, V> addKeyValuePair(K newKey, V newValue);
  abstract public int numPairs();
  abstract public V getValueByKey(K keyToLookUp);
  abstract public K largestKey() throws EmptyPBSTException;
  abstract public K smallestKey() throws EmptyPBSTException;
  abstract public int pathBalance(K keyToFind);
  abstract public Collection<K> collectionOfKeys();
  abstract public PBST<K, V> removeKeyValuePair(K keyToRemove);
  abstract public Collection<K> keyCollection(Collection<K> elements);
  

}
