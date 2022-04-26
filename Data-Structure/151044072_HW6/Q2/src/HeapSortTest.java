import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class HeapSortTest {

    public static void main(String[] args) {
        for (int i=0;i<1;i++){
            // System.out.print(i +" - ");
            test();
        }
    }
    static void test(){
        int size = 1000;
        HeapSort heap = new HeapSort();
        Integer[] ar1 = new Integer[size];
        Random rand = new Random();
        for (int i = 0; i < size; i++){
            // int int_random = rand.nextInt();
            //  ar1[i] = int_random;
             ar1[i] = i;
        }
        long startTime = System.currentTimeMillis();
        heap.sort(ar1);
        long stopTime = System.currentTimeMillis();
        System.out.print((stopTime - startTime) + ", ");
    }


}
