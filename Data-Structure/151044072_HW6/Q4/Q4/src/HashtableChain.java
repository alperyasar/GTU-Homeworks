
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;

/**
 * Hash table implementation using chaining.
 *  @author alper yasar
 **/
public class HashtableChain<K, V> implements KWHashMap<K, V> {
    private Entry<K,V>[] table;
    /** The table */
    private LinkedList<Entry<K, V>>[] btable;
    /** The number of keys */
    private int numKeys;
    /** The capacity */
    private static final int CAPACITY = 101;
    /** The maximum load factor */
    private static final double LOAD_THRESHOLD = 3.0;

    /** Contains key-value pairs for a hash table. */
    private static class Entry<K, V> implements Map.Entry<K, V>, Comparable<V> {
        protected Entry<K,V> left,right;
        /** The key */
        private K key;
        /** The value */
        private V value;

        /**
         * Creates a new key-value pair.
         * @param value The value
         */
        public Entry(V value) {
            this.key = key;
            this.value = value;
            left = null;
            right = null;
        }

        public Entry() {
            left = null;
            right = null;
        }

        /**
         * Retrieves the key.
         * @return The key
         */
        @Override
        public K getKey() {
            return key;
        }

        /**
         * Retrieves the value.
         * @return The value
         */
        @Override
        public V getValue() {
            return value;
        }

        /**
         * Sets the value.
         * @param val The new value
         * @return The old value
         */
        @Override
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }

        @Override
        public int compareTo(V o) {
            if (value != null){
                String temp1 = value.toString();
                String temp2 = o.toString();
                return temp1.compareTo(temp2);
            }
            return 0;
        }
    }

    // Constructor
    public HashtableChain() {
        table = new Entry[CAPACITY];
    }

    /**
     * Method get for class HashtableChain.
     * @param key The key being sought
     * @return The value associated with this key if found;
     *         otherwise, null
     */
    @Override
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length;
        }
        if (table[index] == null) {
            return null; // key is not in the table.
        }

        // assert: key is not in the table.
        return get(table[index],key);
    }
    private V get(Entry<K,V> nextItem, Object key){
        if (nextItem.key.equals(key)) {
            return nextItem.value;
        }
        get(nextItem.left, key);
        get(nextItem.right, key);
        return null;
    }

    /**
     * Method put for class HashtableChain.
     *       This key-value pair is inserted in the
     *       table and numKeys is incremented. If the key is already
     *       in the table, its value is changed to the argument
     *       value and numKeys is not changed.
     * @param key The key of item being inserted
     * @param value The value for this key
     * @return The old value associated with this key if
     *         found; otherwise, null
     */
    @Override
    public V put(K key, V value) {
        numKeys++;
        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length;
        }
        if (table[index] == null) {
            // Create a new linked list at table[index].
            table[index] = new Entry<K, V>();
        }

        Entry<K,V> temp = table[index];
        temp = put(temp,value);
        table[index]= temp;
        return temp.value;
    }

    private Entry<K,V> put(Entry<K,V> node, V data)
    {
        if (node == null)
            node = new Entry<K,V>(data);
        else
        {
            if ( node.compareTo(data) <= 0) {
                node.left = put(node.left, data);
            } else
                node.right = put(node.right, data);
        }
        return node;
    }

    /** Returns true if empty */
    public boolean isEmpty() {
        return numKeys == 0;
    }

}
