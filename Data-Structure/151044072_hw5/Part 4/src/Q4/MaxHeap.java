package Q4;
/**
 * HW5 Part 4 !
 * Q3 by using a max_heap (where the maximum element is in the root node) this time.
 * Implementing heap by using ArrayList. Implementing MaxHeap class to handle the ArrayList
 * heap operations. Using the AgeData class implemented in Q3 to hold age and the number
 * of people at that age data. The key of heap will be "number of people" this time.
 * So, the age which the highest number of people is at, will be at the root. Writing
 * a Comparator to compare two objects of class AgeData.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-05-01
 */
import java.util.ArrayList;

public class MaxHeap<E> {
    ArrayList<E> age;
    /** Return value from the public add method. */
    protected boolean addReturn;

    /**
     * constructor an create an empty arraylist
     */
    MaxHeap(){
        age = new ArrayList<E>();
    }

    /**
     * when added new person if it is exist
     * incrementing in add function and check
     * number of people. If added person number
     * is bigger than parent change to of them until root
     * or less than parent person number
     * @param isfound index
     */
    private void swap(int isfound){
        if(isfound > 0){
            AgeData temp = (AgeData) age.get(isfound);
            AgeData temp2 = (AgeData) age.get((isfound-1)/2);
            if(temp.person > temp2.person){
                age.set(isfound,(E)temp2);
                age.set((isfound-1)/2,(E)temp);
                swap((isfound-1)/2);
            }
        }
    }

    /**
     * add new person to list. firstly check
     * it is exist. if exist increment person number
     * and change if parent person number less than it.
     * Else add end of list.
     * @param addingAge AgeData
     */
    public void add(E addingAge){
        int isfound = age.indexOf(addingAge);
        if(isfound != -1){
            AgeData temp = (AgeData) age.get(isfound);
            temp.person++;
            age.set(isfound,(E)temp);
            swap(isfound);
        }
        else
        age.add(addingAge);
    }
    /**
     * when removed new person if it is decremented
     * person number less than child person numbert
     * than swap them until bigger than person number
     * or end.
     * @param isfound index
     */
    private void removalSwap(int isfound){
        AgeData temp = (AgeData) age.get(isfound);
        AgeData temp2 = (AgeData) age.get((isfound*2)+1);
        if(temp2.person > temp.person){
            age.set(isfound,(E)temp2);
            age.set((isfound*2)+1,(E)temp);
            removalSwap((isfound*2)+1);
        }

    }
    /**
     * check the arraylist size. If bigger
     * than 0 then assign root new AgeData.
     * if it is person number bigger than 1
     * decrement person number and swap with
     * child. Else remove root and change last
     * element to root. Then swap until person
     * number bigger than child.
     *
     */
    public void remove(){
        if(age.size() > 0){
            AgeData temp = (AgeData) age.get(0);
            if(temp.person > 1){
                temp.person--;
                age.set(0,(E)temp);
                removalSwap(0);
            }
            else{
                age.remove(0);
                age.add(0,age.get(age.size()-1));
                age.remove(age.size()-1);
                removalSwap(0);
            }
        }
    }

    /**
     * @param data searching element.
     * @return if element is exist.
     */
    public E find(E data){
        int isfound = age.indexOf(data);
        if (isfound == -1)
            return null;
        else
            return age.get(isfound);
    }

    /**
     *
     * @param data
     * @return number of people are younger than given age.
     */
    public int youngerThan(int data){
        return youngerThan(data,0);
    }

    /**
     * recursively search age and return person number.
     * @param data
     * @param size
     * @return
     */
    public int youngerThan(int data,int size){
        if(size < age.size()){
            AgeData temp = (AgeData) age.get(size);
            if (temp.age < data) {
                return youngerThan(data, ++size) + temp.person;
            }
            else return youngerThan(data,++size);
        }
        return 0;
    }
    /**
     *
     * @param data
     * @return number of people are older than given age.
     */
    public int olderThan(int data){
        return olderThan(data,0);
    }
    /**
     * recursively search age and return person number.
     * @param data
     * @param size
     * @return
     */
    public int olderThan(int data,int size){
        if(size < age.size()){
            AgeData temp = (AgeData) age.get(size);
            if (temp.age > data) {
                return olderThan(data, ++size) + temp.person;
            }
            else return olderThan(data,++size);
        }
        return 0;
    }

    public String toString(){
        return age.toString();
    }


}
