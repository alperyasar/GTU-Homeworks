
import java.util.AbstractMap;
import java.util.AbstractSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * Hash table implementation using open addressing.
 * @author alper yasar
 */
public class HashtableOpen<K, V> extends AbstractMap<K, V>
        implements KWHashMap<K, V> {
    // Data Fields

    private Entry<K, V>[] table;
    private static final int START_CAPACITY = 101;
    private double LOAD_THRESHOLD = 0.75;
    private int numKeys;
    private int numDeletes;
    private final Entry<K, V> DELETED =
            new Entry<K, V>(null, null);

    // Constructor
    public HashtableOpen() {
        table = new Entry[START_CAPACITY];
    }

    /** Contains key-value pairs for a hash table. */
    public static class Entry<K, V> implements Map.Entry<K, V> {

        /** The key */
        private K key;
        /** The value */
        private V value;

        /**
         * Creates a new key-value pair.
         * @param key The key
         * @param value The value
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
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

    }


    /** Returns true if empty */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }

    /**
     * Finds either the target key or the first empty slot in the
     * search chain using linear probing.
     * The table is not full.
     * @param key The key of the target object
     * @return The position of the target or the first empty slot if
     *         the target is not in the table.
     */
    private int find(Object key) {
// Insert solution to programming exercise 6, section 4, chapter 7 here
        // Calculate the starting index.
        int i = 0;
        int index = h(key, i);
        // or the key is found.
        while ((table[index] != null)
                && (!key.equals(table[index].key))) {
            index = h(key,++i);
        }
        return index;
    }

    /**
     * Method get for class HashtableOpen.
     * @param key The key being sought
     * @return the value associated with this key if found;
     *         otherwise, null
     */
    @Override
    public V get(Object key) {
        // Find the first table element that is empty
        // or the table element that contains the key.
        int index = find(key);
        // If the search is successful, return the value.
        if (table[index] != null) {
            return table[index].value;
        } else {
            return null; // key not found.
        }
    }
    /**
     * Method put for class HashtableOpen.
     *       This key-value pair is inserted in the
     *       table and numKeys is incremented. If the key is already
     *       in the table, its value is changed to the argument
     *       value and numKeys is not changed. If the LOAD_THRESHOLD
     *       is exceeded, the table is expanded.
     * @param key The key of item being inserted
     * @param value The value for this key
     * @return Old value associated with this key if found;
     *         otherwise, null
     */
    @Override
    public V put(K key, V value) {
        // Find the first table element that is empty
        // or the table element that contains the key.

        int index = find(key);
        // If an empty element was found, insert new entry.
        if (table[index] == null) {
            table[index] = new Entry<K, V>(key, value);
            numKeys++;
            // Check whether rehash is needed.
            double loadFactor =
                    (double) (numKeys + numDeletes) / table.length;
            if (loadFactor > LOAD_THRESHOLD) {
                rehash();
            }
            return null;
        }

        // assert: table element that contains the key was found.
        // Replace value for this key.
        V oldVal = table[index].value;
        table[index].value = value;
        return oldVal;
    }

    /**
     * Expands table size when loadFactor exceeds LOAD_THRESHOLD
     * The size of table is doubled and is an odd integer.
     *       Each nondeleted entry from the original table is
     *       reinserted into the expanded table.
     *       The value of numKeys is reset to the number of items
     *       actually inserted; numDeletes is reset to 0.
     */
    private void rehash() {
        // Save a reference to oldTable.
        Entry<K, V>[] oldTable = table;
        // Double capacity of this table.
        table = new Entry[2 * oldTable.length + 1];

        // Reinsert all items in oldTable into expanded table.
        numKeys = 0;
        numDeletes = 0;
        for (int i = 0; i < oldTable.length; i++) {
            if ((oldTable[i] != null) && (oldTable[i] != DELETED)) {
                // Insert entry in expanded table
                put(oldTable[i].key, oldTable[i].value);
            }
        }
    }
    /**
     * Returns a set view of the entries in the Map
     * @return a Set view of the entries in the Map
     */
    @Override
    public Set<Map.Entry<K, V>> entrySet() {
        return new EntrySet();
    }

    /** Inner class to implement the set view. */

    private class EntrySet extends AbstractSet<Map.Entry<K, V>> {

        /** Return the size of the set. */
        @Override
        public int size() {
            return numKeys;
        }

        /**
         * Return an iterator over the set
         * @return null
         */
        @Override
        public Iterator<Map.Entry<K, V>> iterator() {
            return null;
        }
    }

    /**
     * linear
     * @param key key
     * @param i index
     * @return formul
     */
    public int h_linear(Object key, int i) {

        return key.hashCode() + i;
    }

    /**
     * quadratic
     * @param key key
     * @param i index
     * @return formul
     */
    public int h_quadratic(Object key, int i) {

        return key.hashCode() + i * i ;
    }

    /**
     * double
     * @param key key
     * @param i index
     * @return formul
     */
    public int h_double(Object key, int i) {

        return key.hashCode() + i*key.hashCode();
    }

    public int size(){
        return table.length;
    }
    /**
     * hash
     * @param key key
     * @param i index
     * @return formul
     */
    public int h(Object key, int i) {
        if (h_double(key, i) % 2 == 0)
            return h_quadratic(key, i)% table.length;
        return h_linear(key, i) % table.length;
    }

}
