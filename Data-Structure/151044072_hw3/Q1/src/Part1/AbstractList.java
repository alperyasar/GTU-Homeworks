package Part1;

public abstract class AbstractList <E> {
    /**
     * Set the data value at index
     * @param index The position of the item to change
     * @param newValue The new value
     */
    public abstract void set(int index, E newValue);
    /**
     * Insert the specified item at index
     * @param item The item to be inserted
     */
    public abstract void add(E item);

    /**
     * Get the data value at index
     * @param index The position od the element return
     * @return The data at index
     * @throws IndexOutOfBoundsException if index is out of range
     */
    public abstract E get(int index);

    /**
     * remove an element from array
     * @param index
     */
    public abstract void remove(int index);

    /**
     * Return size
     * @return size
     */
    public abstract int size();

    /**
     * write all data
     */
    public abstract void write();

}
