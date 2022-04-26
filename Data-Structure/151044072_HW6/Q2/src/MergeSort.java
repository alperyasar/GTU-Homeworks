
import java.util.LinkedList;


public class MergeSort {
    public static <T extends Comparable<T>> void sort(LinkedList<T> table){
        // A table with one element is sorted already.
        if( table.size() > 1){
            // Split table into halves
            int halfSize =table.size()/2;
            LinkedList<T> leftTable = new LinkedList<T>();
            LinkedList<T> rightTable = new LinkedList<T>();
            copy(table,0,leftTable,0,halfSize);
            copy(table,halfSize,rightTable,0,table.size() - halfSize);
            // Sort the halves
            sort(leftTable);
            sort(rightTable);
            // Merge the halves
            merge(table,leftTable,rightTable);
        }
    }

    private static <T extends Comparable<T>> void copy(LinkedList<T> table, int i, LinkedList<T> splitTable, int i1, int halfSize) {
        while (i1 < halfSize){
            splitTable.add(table.get(i++));
            i1++;
        }
    }

    private static <T extends Comparable<T>> void merge(LinkedList<T> table, LinkedList<T> leftTable, LinkedList<T> rightTable) {
        int i=0,j=0,k=0;
        while ( i < leftTable.size() && j < rightTable.size()){
            // Find the smaller and insert it into the table
            if (leftTable.get(i).compareTo(rightTable.get(j)) < 0){
                table.set(k++, leftTable.get(i++));
            }
            else {
                table.set(k++, rightTable.get(j++));
            }
        }

        while (i< leftTable.size()){
            table.set(k++, leftTable.get(i++));
        }

        while (j< rightTable.size()){
            table.set(k++, rightTable.get(j++));
        }
    }

}
