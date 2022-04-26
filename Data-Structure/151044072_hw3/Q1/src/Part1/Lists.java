package Part1;

public interface Lists<E> {
    void set(int index, E newValue);
    void add(E item);
    E get(int index);
    void remove(int index);
    int size();
    void write();
    void addFirst(E item);
    void addAfter(E item);
    LinkedArrayList<E> getNode(int index);
    void removeAfter(LinkedArrayList<E> node,int index);
    void removeFirst(int index);

    // ---- Just MyArray-----
 //   boolean maxSize();
}
