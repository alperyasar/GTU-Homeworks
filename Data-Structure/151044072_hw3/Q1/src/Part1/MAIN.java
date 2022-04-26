package Part1;

/**
 * <h1>HW3 Part 1 !</h1>
 * in this part should keep a linked list where each node contains an array of elements with constant capacity.
 * These arrays should be partially filled arrays.
 * Arrays in the nodes of the linked list, may contain different number of elements.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-03-31
 */
public class MAIN {
    public static void main(String[] args) {
        LinkedArrayList<Integer> temp = new LinkedArrayList<Integer>();

        temp.add(1);         temp.add(2);
        temp.add(3);
        temp.remove(1);
        temp.add(4);        temp.add(5);
        temp.add(11);        temp.add(12);
        temp.add(13);        temp.add(14);
        temp.add(15);        temp.add(21);
        temp.add(22);        temp.add(23);
        temp.add(24);        temp.add(35);
        temp.add(31);        temp.add(32);
        temp.add(33);        temp.add(34);
        temp.add(35);
        temp.remove(0);

        temp.remove(1);

        temp.add(123);
        temp.set(0,227);        temp.set(6,237);
        temp.set(17,247);


        temp.write();

    }
}
