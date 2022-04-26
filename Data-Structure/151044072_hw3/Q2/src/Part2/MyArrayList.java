package Part2;

public class MyArrayList {
    private char data;
    private MyArrayList head;
    private MyArrayList next;
    private int size;

    //Constructors

    /**
     * initial constructor
     */
    public MyArrayList(){
        head = null;
        next =null;
        size = 0;
    }
    /**
     * new constructor with new item
     * @param item add new character to data
     */
    public MyArrayList(char item){
        data = item;
        next=null;
    }

    /**
     *Insert the specified item at index
     * @param item The item to be inserted
     */
    public void add(char item){
        if(size == 0){
            head = new MyArrayList(item);
            size++;
        }
        else{
            MyArrayList temp;
            temp = head;
            for (int i = 0; i<size-1; i++){
                temp = temp.next;
            }
            temp.next = new MyArrayList(item);
            size++;
        }

    }


    /**
     * add character to specific location
     * @param item adding character
     * @param index specific location
     */
    public void add(String item,int index){
        MyArrayList temp = head;
       // temp = head;
        for (int i = 0; i<index; i++){
            temp = temp.next;
        }
        for (int i = 0; i<item.length();i++){
            MyArrayList temp2 = new MyArrayList(item.charAt(item.length()-i-1));
            temp2.next = temp.next;
            temp.next = temp2;
            size++;
        }

    }

    /**
     * returns the start index of the first occurrence of the searched group of characters.
     * @param key gruop of characters which searching
     * @return where found first occurenced
     */
    public int locationFound(String key){
       MyArrayList temp = head;
       int control = 0;
       for (int i=0; i<size;i++){
           if(temp.data == key.charAt(control)){
               control++;
               if(control == key.length()){
                   return i-control;
               }
           }
           else {
               control = 0;
           }
           temp=temp.next;
       }
        return -1;
    }

    /**
     *  replaces all occurrences of a character with another character
     * @param newChar new character added
     * @param oldChar old character changing
     */
    public void replace(char newChar, char oldChar){
        MyArrayList temp = head;
        for (int i = 0; i< size;i++){
            if(temp.data == oldChar){
                temp.data = newChar;
            }
            temp = temp.next;
        }
    }
    /**
     * Write all linked list
     */
    public void write(){
        MyArrayList temp = head;
        for(int i = 0;i<size;i++){
            System.out.print(temp.data);
            temp= temp.next;
        }
    }
}
