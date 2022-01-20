package Part2;
/**
 * HW4 Part 2 !
 * Deque is a queue that supports adding or removing items from both ends of
 * the data structure. To implement it, your class should keep two linked list.
 * One for the elements in the deque and the other to keep the nodes removed.
 * You should use a removed node, if any available, when a new node is needed
 * instead of creating a new node. With this type of operation you can save time
 * for constructing new nodes and garbage collection the nodes that are not used anymore.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-04-09
 */
public class MAIN {
    public static void main(String[] args) {
        DequeClass<Integer> den = new DequeClass<Integer>();
        den.addFirst(1);
        den.addFirst(2);
        System.out.println("First item " + den.peekFirst());
        System.out.println("Last item " + den.peekLast());
        den.addFirst(3);
        den.addLast(7);
        den.addLast(8);
        den.addLast(9);

        System.out.println("First item " + den.peekFirst());
        System.out.println("Last item " + den.peekLast());

        System.out.println("Deleted item " + den.pollFirst());
        System.out.println("Deleted item " + den.pollLast());
        den.addFirst(11);
        den.addFirst(12);
        den.addFirst(9);
        den.addLast(17);
        den.addLast(5);

        System.out.println("First Element : "+ den.peekFirst());

        System.out.println("Last Element : "+ den.peekLast());
    }
}
