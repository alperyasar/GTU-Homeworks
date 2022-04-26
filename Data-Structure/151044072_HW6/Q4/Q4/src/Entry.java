public class Entry<K,V> {
    private boolean removed;
    protected K key;
    protected V value;

    public Entry(K k, V v) {
        key = k;
        value = v;
    }

    public boolean isRemoved() {
        return removed;
    }

    public void setRemoved(boolean removed) {
        this.removed = removed;
    }

    public K getKey() {
        return key;
    }

    public void setKey(K key) {
        this.key = key;
    }

    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public boolean equals(Object o) {
        if (!(o instanceof Entry)) {
            return false;
        } else {
            @SuppressWarnings("unchecked")
            Entry<K, V> that = (Entry<K, V>) o;
            return that.getKey().equals(key) && that.getValue().equals(value);
        }
    }

    public String toString() {
        return key.toString() + ": " + value.toString();
    }
}
