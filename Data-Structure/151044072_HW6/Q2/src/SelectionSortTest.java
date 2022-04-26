import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class SelectionSortTest {
    public static void main(String[] args) {
        for (int i=0;i<20;i++){
            // System.out.print(i +" - ");
            test();
        }
    }
    static void test(){
        SelectionSort select = new SelectionSort();
        Integer[] ar1 = new Integer[18000];
        Random rand = new Random();
        for (int i = 0; i < 18000; i++){
            int int_random = rand.nextInt();
            ar1[i] = int_random;
          //  ar1[i] = i;
        }
        long startTime = System.currentTimeMillis();
        select.sort(ar1);
        long stopTime = System.currentTimeMillis();
        System.out.print((stopTime - startTime) + ", ");
    }
}
