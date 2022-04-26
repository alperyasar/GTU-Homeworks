package Part3;

public class Node {

    protected char data;
    protected WordLinkedList word;
    protected Node next;
    protected Node previous;

    Node(char item) {
        data = item;
        next = null;
        previous = null;
        word = null;
    }

}
