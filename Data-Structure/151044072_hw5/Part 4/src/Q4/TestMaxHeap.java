package Q4;

public class TestMaxHeap {
    public static void main(String[] args) {
        //Create an empty heap
            MaxHeap<AgeData> heap = new MaxHeap<AgeData>();
        //Add nodes
            heap.add(new AgeData(10));
            heap.add(new AgeData(5));
            heap.add(new AgeData(70));
            heap.add(new AgeData(10));
            heap.add(new AgeData(50));
            heap.add(new AgeData(5));
            heap.add(new AgeData(15));
    //Create a string representing the heap and print it
              String heapStr= heap.toString();
               System.out.println(heapStr);
    //output:
    //10 - 2
    //5 - 2
    //70 - 1
    //50 - 1
    //15 - 1
    //Print the number of people younger than 15
          System.out.println(heap.youngerThan(10));
    //output will be 2
    //Find the number of people at any age
               System.out.println(heap.find(new AgeData(10)).toString());
    //It will print:
    //10 - 2
        System.out.println(heap.olderThan(10));
    }
}
