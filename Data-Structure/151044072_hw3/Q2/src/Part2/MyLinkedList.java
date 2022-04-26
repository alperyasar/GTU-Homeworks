package Part2;


public class MyLinkedList {
    private char data;
    private MyLinkedList head;
    private MyLinkedList next;
    private int size;

    //constructors

    /**
     * new empty constructor
     */
    public MyLinkedList(){
        head = null;
        next = null;
        size = 0;
    }

    /**
     * new constructor with new item
     * @param item add new character to data
     */
    public MyLinkedList(char item){
        data = item;
        next = null;
        head = null;
    }
    /**
     * Add a new item to first node
     * @param item The item to insert
     */
    public void addFirst(char item){
        if(head == null){
            head = new MyLinkedList(item);
            size++;
        }
        else{
            MyLinkedList temp = new MyLinkedList(item);
            temp.next = head;
            head = temp;
        }

    }

    /**
     * Add a node after a given node
     * @param item  The item to insert
     */
    private void addAfter(char item){
        MyLinkedList node = getNode(size);
        node.next = new MyLinkedList(item);
        node = node.next;
        size++;
    }

    /**
     * add character to specific location
     * @param item adding character
     * @param index specific location
     */
    private void addAfter(char item,int index){
        MyLinkedList temp = new MyLinkedList(item);
        MyLinkedList node = getNode(index-1);
        temp.next = node.next;
        node.next = temp;
        size++;
    }
    /**
     * Insert the specified item at index
     * @param item The item to be inserted
     */
    public void add(char item) {

        if(size == 0){
            addFirst(item);
        }
        else{
            addAfter(item);
        }
    }

    /**
     * add new item to specific location
     * @param item adding character
     * @param index specific location
     */
    public void add(String item, int index) {
        if(index == 0){
            int i = 0;
            int stringSize = item.length();
            while(i< stringSize){
                addFirst(item.charAt(stringSize-i-1));
                i++;
            }

        }
        else{
            int i = 0;
            int stringSize = item.length();
            while(i< stringSize){
                addAfter(item.charAt(stringSize-i-1),index);
                i++;
            }
        }
    }
    /**
     * returns the start index of the first occurrence of the searched group of characters.
     * @param key gruop of characters which searching
     * @return where found first occurenced
     */
    public int locationFound(String key){
        int i=0;
        int control = 0;
        int j=0;
        MyLinkedList temp = new MyLinkedList();
        temp = head;
        while(temp != null){
            j++;
            if(temp.data == key.charAt(i)){
                control++;
                if(control == key.length()){
                    return j-control;
                }
                i++;
            }
            else {
                control = 0;
                i=0;
            }
            temp = temp.next;
        }
        return -1;
    }
    /**
     * replaces all occurrences of a character with another character
     * @param newChar new character added
     * @param oldChar old character changing
     */
    public void replace(char newChar, char oldChar){
        MyLinkedList temp = new MyLinkedList();
        temp = head;
        while (temp != null){
            if(temp.data == oldChar){
                temp.data = newChar;
            }
            temp = temp.next;
        }
    }
    /**
     * Find the node at a specified position
     * @return The node at index or null if it does not exist
     */
    private MyLinkedList getNode(int index){
        MyLinkedList node = head;
        int i =0;
        while (i < index && node.next != null){
            node = node.next;
            i++;
        }
        return node;
    }


    /**
     * Write all linked list
     */
    public void write(){
        MyLinkedList temp= new MyLinkedList();
        temp = head;
        do {
            System.out.print(temp.data);
            temp = temp.next;
        }while (temp.next != null);
        System.out.println("\n----------------------------------------------------------------------------------\n");
    }

}
