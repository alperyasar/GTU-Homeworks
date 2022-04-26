import java.util.LinkedList;
import java.util.Random;

public class MergeTest {
    public static void main(String[] args) {
        for (int i=0;i<20;i++){
           // System.out.print(i +" - ");
            test();
        }

    }
    static void test(){
        MergeSort merge = new MergeSort();
        LinkedList<Integer> list1 = new LinkedList<Integer>();
        Random rand = new Random();
        for (int i = 0; i < 1000; i++){
            int int_random = rand.nextInt();
            list1.add(int_random);
            // list1.add(i);
        }
        long startTime = System.currentTimeMillis();
        MergeSort.sort(list1);
        long stopTime = System.currentTimeMillis();
        System.out.print((stopTime - startTime) + ", ");
    }
}
