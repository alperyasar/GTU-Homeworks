package Part3;
/**
 * <h1>HW3 Part 3 !</h1>
 * Each node keeps a character and references to previous and next nodes.
 * To link the words, each node may have a reference to a cross node, as well.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-04-01
 */
import java.util.*;

public class WordLinkedList{

    private Node head;
    //constructor
    WordLinkedList() {
        head = null;
    }

    /**
     * @param word is saved to the list as char.
     */
    WordLinkedList (String word) {
        for ( int i = 0; i < word.length() ; i++ ) {
            char data = word.charAt(i);
            add(data);
        }
    }
    /**
     * Creates new node and saving to list.
     * @param data is char type and a node in list.
     */
    public void add(char data) {

        if(head == null ) {
            Node node = new Node(data);
            head = node;
        }else {
            Node iterator = head;
            while (iterator.next != null){
                iterator = iterator.next;
            }
            Node node = new Node(data);
            iterator.next = node;
            node.previous = iterator;
        }
    }

    /**
     * find the element in the list
     * @param index reference to node
     * @return If the element is registered in the node in that index, returns it.
     */
    public char get(int index){
        Node iterator = head;
        int i;
        for ( i = 0; i != index && iterator != null ; i++ ) {
            iterator = iterator.next;
        }
        if( i == index && iterator != null )
            return iterator.data;

        return '\0';
    }


    /**
     * adds a cross between itself and another word at specified indexes.
     * adds for other word that have the corresponding cross
     * @param index Which indexes intersect
     * @param word Which word does it intersect
     */
    public void add( int index , WordLinkedList word ) {
        // bu class içinde node için cross ataması
        Node iterator = head;
        int i;

        for ( i = 0; i != index &&  iterator != null; i++ ){
            iterator = iterator.next;
        }

        if( iterator != null && i == index )
            iterator.word = word;

        char crossChar = this.get(index);

        // crossword için bu node'u ata
        index = word.index(crossChar);
        iterator = word.head;

        for ( i = 0; i != index &&  iterator != null ; i++ )
            iterator = iterator.next;

        if( iterator != null && i == index )
            iterator.word = this;

    }

    /**
     * to find out which nodes the element in the list is in
     * @param data wanted element
     * @return if data is exist in list returns that index, otherwise returns -1
     */
    public int index (char data) {
        Node iterator = head;
        int i;
        for ( i = 0;iterator != null ; i++ ) {
            if(  iterator.data == data)
                return i;
            iterator = iterator.next;
        }
        return -1;
    }
    /**
     * removes a cross between itself and another word at specified indexes.
     * removes for other word that have the corresponding cross
     * @param index Which indexes intersect
     * @param word Which word does it intersect
     */
    public void remove( int index , WordLinkedList word ) {
        Node iterator = head;

        for ( int i = 0; iterator != null ; i++ ){
            if(i == index )
                iterator.word = null;
            iterator = iterator.next;
        }
        iterator = word.head;

        for ( int i = 0; iterator != null ; i++ ){
            if(i == index )
                iterator.word = null;
            iterator = iterator.next;
        }
    }

    /**
     *  checks if there is a word at the intersection.
     * @return if there is returns true, otherwise return false
     */
    public boolean hasCross() {
        Node iterator = head;

        while ( iterator != null ) {
            if( iterator.word != null)
                return true;
            iterator = iterator.next;
        }
        return false;
    }

    /**
     * records which words is intersect with this word
     * @return a list. Intersections words can be more than one.
     */

    public List<WordLinkedList> getWord () {
        Node iterator = head;
        List<WordLinkedList> word = new ArrayList<>();

        while ( iterator != null ) {
            if( iterator.word != null)
                word.add(iterator.word);
            iterator = iterator.next;
        }

        return word;
    }

    /**
     * Write all words ands crossed words
     */
    public void write() {

        Node iterator = head;
        System.out.print("'");
        while ( iterator != null ) {
            System.out.print(iterator.data);
            iterator = iterator.next;
        }
        System.out.print("' was crossed with '");

        iterator = head;
        int control = 0,controlSame = 0;
        for (int i = 0 ; iterator != null ; i++ ) {

            if( iterator.word != null ) {
                // Print cross word
                WordLinkedList crossedWord = iterator.word;
                Node newIter = crossedWord.head;
                if(controlSame != 0)
                    System.out.print(", '");
                while (  newIter != null ) {
                    control++;
                    System.out.print(newIter.data);
                    newIter = newIter.next;
                }
            }
            if(control != 0 ){

                System.out.print("' in " + (i+1) + ". index");
                control = 0;
                controlSame++;
            }
            iterator = iterator.next;

        }
        System.out.println(".\n");
    }


}
