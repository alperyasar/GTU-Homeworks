package LinkedArrayList;

public class LinkedArrayList <E> extends AbstractList  implements List{
    private E data;
    private LinkedArrayList<E> head;
    private LinkedArrayList<E> next;
    private int size;

    //Constructors

    /**
     * Initial constructor
     */
    public LinkedArrayList(){
        head = null;
        next = null;
        size = 0;
    }
    /**
     * Creates a new node with a null next field
     * @param dataItem The data stored
     */
    public LinkedArrayList(E dataItem){
        data = dataItem;
        next = null;
    }

    /**
     * Creates a new node that references another node
     * @param dataItem the data stored
     * @param nodeRef The node referenced by new node
     */
    public LinkedArrayList(E dataItem, LinkedArrayList<E> nodeRef){
        data = dataItem;
        next = nodeRef;
    }

    /**
     * Add a new item to first node
     * @param item The item to insert
     */
    public void addFirst(E item){
        head = new LinkedArrayList<E>(item,head);
        size++;
    }

    /**
     * Add a node after a given node
     * @param node  Thenode preceding the new item
     * @param item  The item to insert
     */
    private void addAfter(LinkedArrayList<E> node, E item){
        node.next = new LinkedArrayList<E>(item,node.next);
        size++;
    }

    /**
     * Remove the node after a given node
     * @param node The node before the one to be removed
     * @return The data from the removed node, or null
     * if there is no node to remove
     */
    private E removeAfter(LinkedArrayList<E> node) {
        LinkedArrayList<E> temp = node.next;
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
        LinkedArrayList<E> temp = head;
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
    private LinkedArrayList<E> getNode(int index){
        LinkedArrayList<E> node = head;
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
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        LinkedArrayList<E> node = getNode(index);
        return node.data;
    }

    /**
     * Set the data value at index
     * @param index The position of the item to change
     * @param newValue The new value
     * @return The data value priviously at index
     * @throws IndexOutOfBoundsException if index is out of range
     */
    public E set(int index, E newValue){
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        LinkedArrayList<E> node =getNode(index);
        E result = node.data;
        node.data = newValue;
        return result;
    }

    /**
     * Insert the specified item at index
     * @param index The position where item is to be inserted
     * @param item The item to be inserted
     * @throws IndexOutOfBoundsException if index is out of range
     */
    public void add(int index, E item) {
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }
        if(index == 0){
            addFirst(item);
        }
        else{
            LinkedArrayList<E> node = getNode(index-1);
            addAfter(node,item);
        }
    }

    /**
     * Append item to the end of the list
     * @param item The item to be appended
     * @return true (as specified by the Collection interface)
     */
    public boolean add(E item){
        add(size, item);
        return true;
    }
}
