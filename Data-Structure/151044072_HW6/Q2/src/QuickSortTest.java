import java.util.LinkedList;
import java.util.Random;

public class QuickSortTest {

    public static void main(String[] args) {
        for (int i=0;i<20;i++){
            test();
        }
    }
    static void test(){
        QuickSort quick = new QuickSort();
        LinkedList<Integer> list1 = new LinkedList<Integer>();
        Random rand = new Random();
        for (int i = 0; i < 4000; i++){
             int int_random = rand.nextInt();
             list1.add(int_random);
           //  list1.add(i);
        }
        long startTime = System.currentTimeMillis();
          QuickSort.sort(list1);
      //    System.out.println(list1);
          long stopTime = System.currentTimeMillis();
          System.out.print(stopTime - startTime + ", ");
    }
}
