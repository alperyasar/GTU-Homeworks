public class TestSkipList {
    public static void main(String[] args) {
        SkipList b = new SkipList(3);
        b.insert(8);
        b.insert(9);
        b.insert(10);
        b.insert(11);
        b.insert(15);
        b.insert(20);
        b.insert(17);

        b.print();

        b.remove(10);
        System.out.println();
        b.print();

    }
}
