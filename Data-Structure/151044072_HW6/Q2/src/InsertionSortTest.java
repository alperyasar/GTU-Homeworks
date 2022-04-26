import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class InsertionSortTest {

    public static void main(String[] args) {
        for (int i=0;i<20;i++){
            // System.out.print(i +" - ");
            test();
        }
    }
    static void test(){
        int size = 18000;
        InsertionSort insert = new InsertionSort();
        Integer[] ar1 = new Integer[size];
        Random rand = new Random();
        for (int i = 0; i < size; i++){
             int int_random = rand.nextInt();
              ar1[i] = int_random;
             // ar1[i] = i;
        }
        long startTime = System.currentTimeMillis();
        insert.sort(ar1);
        long stopTime = System.currentTimeMillis();
        System.out.print((stopTime - startTime) + ", ");
    }


}