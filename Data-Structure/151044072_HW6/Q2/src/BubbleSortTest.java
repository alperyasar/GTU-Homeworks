import java.util.Random;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

public class BubbleSortTest {

    public static void main(String[] args) {
        for (int i=0;i<1;i++){
            // System.out.print(i +" - ");
            test();
        }
    }
    static void test(){
        BubbleSort bubble = new BubbleSort();
        Integer[] ar1 = new Integer[1000];
        Random rand = new Random();
        for (int i = 0; i < 1000; i++){
           // int int_random = rand.nextInt();
          //  ar1[i] = int_random;
              ar1[i] = i;
        }
        long startTime = System.currentTimeMillis();
        bubble.sort(ar1);
        long stopTime = System.currentTimeMillis();
        System.out.print((stopTime - startTime) + ", ");

    }


}
