package Part1;

public class MyArray<E> {
    private E data;
    private MyArray<E> head;
    private MyArray<E> next;
    private int size;
    private final int MAX_SIZE = 5;

    public int size(){
        return size;
    }
    public MyArray(){
        head = null;
        next = null;
        size = 0;
    }
    MyArray(E item){
        head = null;
        next=null;
        data = item;
    }
    private boolean maxSize(){
        return MAX_SIZE!=size;
    }

    /**
     * Insert the specified item at index
     * @param item The item to be inserted
     */
    public boolean add(E item) {
        if(maxSize()){
            if(size == 0){

                addFirst(item);
            }
            else{
                addAfter(item);
            }
            return true;
        }
        return false;

    }
    /**
     * Add a new item to first node
     * @param item The item to insert
     */
    public void addFirst(E item){
        head = new MyArray<E>(item);
        size++;
    }

    /**
     * Add a node after a given node
     * @param item The item to insert
     */
    private void addAfter(E item){
        MyArray<E> node = head;
        for (int i = 0; i<size-1 ; i++){
            node = node.next;
        }
        node.next = new MyArray<E>(item);
        size++;
    }

    /**
     * remove an element from array
     * @param index
     */
    public void remove(int index) {

        if(index == 0){
            removeFirst();
        }
        else{
            MyArray<E> node = getNode(index-1);
            removeAfter(node);
        }
    }

    /**
     * Remove the node after a given node
     * @param node The node before the one to be removed
     * @return The data from the removed node, or null
     * if there is no node to remove
     */
    private E removeAfter(MyArray<E> node) {
        MyArray<E> temp = node.next;
        if (temp != null) {
            node.next = temp.next;
            size--;
            return temp.data;
        } else {
            return null;
        }
    }

    /**
     * Remove the first node from the list
     * @return The removed node's data or null if the list is empty
     */
    private E removeFirst(){
        MyArray<E> temp = head;
        if(head != null){
            head = head.next;
        }
        //Return data at old head or null if list is empty
        if(temp != null){
            size--;
            return temp.data;
        }
        else {
            return null;
        }
    }
    /**
     * Find the node at a specified position
     * @param index The positin of the node sought
     * @return The node at index or null if it does not exist
     */
    private MyArray<E> getNode(int index){
        MyArray<E> node = head;
        for (int i = 0; i<index && node != null; i++){
            node = node.next;
        }
        return node;
    }

    /**
     * Get the data value at index
     * @param index The position od the element return
     * @return The data at index
     * @throws IndexOutOfBoundsException if index is out of range
     */
    public E get(int index){
        if(index < 0 || index >= size ){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        MyArray<E> node = getNode(index);
        return node.data;
    }
    /**
     * Set the data value at index
     * @param index The position of the item to change
     * @param newValue The new value
     * @throws IndexOutOfBoundsException if index is out of range
     */
    public void set(int index, E newValue){
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        MyArray<E> node =getNode(index);
        E result = node.data;
        node.data = newValue;
    }
    public void write(){
        MyArray <E> temp = head;
        while (temp != null){
            System.out.println(temp.data);
            temp = temp.next;
        }
    }
}
