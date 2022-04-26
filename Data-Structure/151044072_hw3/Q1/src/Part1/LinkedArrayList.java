package Part1;

public class LinkedArrayList<E> extends AbstractList<E> implements Lists<E>{
    private LinkedArrayList<E> head;
    private LinkedArrayList<E> next;
    private MyArray<E> data;
    private int size;
    //Constructors

    /**
     * Initial constructor
     */
    public LinkedArrayList(){
        head = null;
        next = null;
        size = 0;
        data = new MyArray<E>();
    }

    /**
     * Create new array and new node
     * @param item adding item to data
     */
    private LinkedArrayList(E item){
       data = new MyArray<E>();
       data.add(item);
    }

    @Override
    public void set(int index, E newValue) {
        if(index > 5){
            LinkedArrayList<E> node = getNode((index/5)-1);
            node.next.data.set((index % 5) - 1,newValue);
        }
        else{
            head.data.set(index,newValue);
        }
    }

    /**
     * Add a new item to first node
     * @param item The item to insert
     */
    public void addFirst(E item){
        head = new LinkedArrayList<E>(item);
        size++;
    }

    /**
     * Add a node after a given node
     * @param item  The item to insert
     */
    public void addAfter(E item){
        LinkedArrayList<E> node = head;
        while (node.next != null){
            node = node.next;
        }
        if(!(node.data.add(item))){
            node.next = new LinkedArrayList<E>(item);
            size++;
        }
    }
    @Override
    public void add(E item) {
        if(size == 0){
            addFirst(item);
        }
        else{
            addAfter(item);
        }
    }

    @Override
    public E get(int index) {
        int nodeIndex = index / 5;
        if(index < 0 || nodeIndex >= size ){
            throw new IndexOutOfBoundsException(Integer.toString(index));
        }

        LinkedArrayList<E> node = getNode(nodeIndex);
        return node.data.get(nodeIndex % 5);
    }
    /**
     * Find the node at a specified position
     * @param index The positin of the node sought
     * @return The node at index or null if it does not exist
     */
    public LinkedArrayList<E> getNode(int index){
        LinkedArrayList<E> node = head;
        for (int i = 0; i<index; i++){
            node = node.next;
        }
        return node;
    }

    @Override
    public void remove(int index) {
        get(index);
        if(index < 5){
            removeFirst(index);
        }
        else{
            LinkedArrayList<E> node = getNode((index/5)-1);
            removeAfter(node,(index % 5) - 1);
        }
    }
    /**
     * Remove the node after a given node
     * @param node The node before the one to be removed
     * @return The data from the removed node, or null
     * if there is no node to remove
     */
    public void removeAfter(LinkedArrayList<E> node, int index) {
        LinkedArrayList<E> temp = node.next;
        temp.data.remove(index);
        if (temp.data.size()==0) {
            node.next = temp.next;
            size--;
        }
    }

    /**
     * Remove the first node from the list
     * @return The removed node's data or null if the list is empty
     */
    public void removeFirst(int index){
        head.data.remove(index);
        if(head.data.size() == 0){
            head = head.next;
        }
    }


    @Override
    public int size() {
        return size*5 + getNode(size-1).data.size();
    }

    @Override
    public void write() {
        LinkedArrayList<E> temp = head;
        int i =0;
        while (temp != null){
            temp.data.write();
            i++;
            temp = temp.next;
        }
    }
}
