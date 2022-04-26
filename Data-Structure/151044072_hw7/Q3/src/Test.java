import java.util.LinkedList;
import java.util.Random;

public class Test {
    public static void main(String[] args) {

        for(int i = 0; i < 10; i++){
            test();
        }
    /*    for(int i = 99; i > 5; i--){
            test.remove(i);
        }*/
    }
    static void test(){
        BTree<Integer> test = new BTree<Integer>(4);
        Random rand = new Random();
        int size = 80000;
        long startTime = System.currentTimeMillis();
        for(int i = 0; i < size; i++){
            test.add(rand.nextInt());
        }
        long stopTime = System.currentTimeMillis();
        System.out.print(stopTime - startTime + ", ");


    }
    static void test2(){
        BinarySearchTree<Integer> test = new BinarySearchTree<Integer>();
        int [] temp = new int[11];
        Random rand = new Random();
        int size = 10000;
        int j = 0;
        for(int i = 0; i < size; i++){
            int numb = rand.nextInt();
            test.add(numb);
            if ((100 + (999*j)) == i){
                temp[j] = numb;
                j++;
            }
        }
        long startTime = System.currentTimeMillis();
        for(int i = 0; i < 10; i++){
            //    System.out.println(test.remove(temp[i]));
            test.remove(temp[i]);
        }
        long stopTime = System.currentTimeMillis();
        System.out.print(stopTime - startTime + ", ");

    }
}
