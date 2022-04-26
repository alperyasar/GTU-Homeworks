package Part3;
/**
 * <h1>HW4 Part 3 !</h1>
 * Define each of the following problem recursively:
 *  Identify the base case (or base cases) that stops the recursion
 *  Define the smaller problem (or problems)
 *  Explain how to combine solutions of smaller problems to get the solution of original problem
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-04-13
 */
import java.util.Arrays;
import java.util.Stack;

public class MAIN {

   public static void main(String[] args) {
       //reverse string
        String str = "this function writes the sentence in reverse";
        System.out.println("\nBefore string is reverse : " + str);
        String[] strArr = str.split(" ");
        String reversed = reverse(strArr,0);
        System.out.println("The reversed string is: " + reversed);

        //check elfish
        System.out.println();
       String[] strElfish = {"whiteleaf", "tasteful" , "Computer" , "unfriendly", "and", "waffles","Science"};
       for(String strElf : strElfish){
           if(elfish(strElf,0))
               System.out.println( strElf+" is an elfish");
           else
               System.out.println(strElf+ " is not an elfish");
       }

        // sorting array
       System.out.println();
       int intArr[] = {12, 11, 13, 5, 6};
       System.out.println("Before sorting" + Arrays.toString(intArr));
       insertionSortRecursive(intArr, intArr.length);
       System.out.println("After Sorting" + Arrays.toString(intArr));

       //postfix
           String postfixStr = "2421*-2/563/-++";
       Stack<Integer> stack=new Stack<>();
       System.out.println("\nThe equation of this postfix \"" + postfixStr + "\" : is : " + postfixEvelaute(postfixStr,stack));

       //prefix
       Stack<Character> stack1=new Stack<>();
       String prefixStr = "++42*3-51";
       System.out.println("\nThe equation of this prefix \"" + prefixStr + "\" : is : " + prefixEvelaute(prefixStr,stack1) +  "\n");

       //printing the element on screen
       Integer doubleArray[][]={   {1,2,3,4},
                               {5,6,7,8},
                               {9,10,11,12},
                               {13,14,15,16},
                               {17,18,19,20}};
        printArray(doubleArray,0,0,0,0);


   }

    /**
     * Reversing a string. Word by word
     * @param x Words
     * @param index index
     * @return word
     */
    public static String reverse(String[] x, int index){
        if(index==x.length-1 ){
            return x[index];
            //Recursive
        }
        return reverse(x, ++index)  +" "+ x[index-1];
    }

    /**
     *  Determining whether a word is elfish or not if it contains the letters: e, l, and f.
     * @param str word
     * @param control how many found e,l and f
     * @return true if 3 of them is found
     */
    public static boolean elfish(String str,int control){
        if(control == 3)
            return true;
        else if(str.isEmpty())
            return false;
        else if(str.charAt(0) == 'e' || str.charAt(0) == 'l' ||str.charAt(0) == 'f' )
           return  elfish(str.substring(1),++control);
        else
            return elfish(str.substring(1),control);

   }
    // Recursive function to sort an array using
    // insertion sort

    /**
     * sort an integer array
     * @param arr integer array
     * @param index index
     */
    static void insertionSortRecursive(int arr[], int index)
    {
        // Base case
        if (index <= 1)
            return;

        // Sort first n-1 elements
        insertionSortRecursive( arr, index-1 );

        // Insert last element at its correct position
        // in sorted array.
        int last = arr[index-1];
        int j = index-2;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > last)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = last;
    }

    /**
     *  Evaluating a Postfix expression
     * @param postfixStr postfix expression
     * @param stack hold number
     * @return result
     */
    public static int postfixEvelaute(String postfixStr,Stack<Integer> stack){
        if(postfixStr.isEmpty()){
            return stack.pop();
        }
        switch (postfixStr.charAt(0)){
            case '+' : int val1 = stack.pop();
                       int val2 = stack.pop();
                       stack.push(val2 + val1);
                break;
            case '-' : val1 = stack.pop();
                        val2 = stack.pop();
                      stack.push(val2 - val1);
                break;
            case '*' : val1 = stack.pop();
                     val2 = stack.pop();
                     stack.push(val2 * val1);
                break;
            case '/' : val1 = stack.pop();
                         val2 = stack.pop();
                         stack.push(val2 / val1);
                break;
            default: stack.push(Character.getNumericValue(postfixStr.charAt(0)));

        }
        return postfixEvelaute(postfixStr.substring(1),stack);
    }

    /**
     * Evaluating a Prefix expression
     * @param prefixStr prefix expression
     * @param stack hold number
     * @return result
     */
    public static int prefixEvelaute(String prefixStr,Stack<Character> stack){
        if(prefixStr.isEmpty()){
            return Character.getNumericValue(prefixStr.charAt(0));
        }
        if(prefixStr.substring(1).isEmpty()){
            return Character.getNumericValue(prefixStr.charAt(0));
        }
        else if(Character.getNumericValue(prefixStr.charAt(0)) >= 0 && Character.getNumericValue(prefixStr.charAt(0)) <= 9){
            switch (stack.pop()){
                case '+' : return Character.getNumericValue(prefixStr.charAt(0)) + prefixEvelaute(prefixStr.substring(1),stack);

                case '-' : return Character.getNumericValue(prefixStr.charAt(0)) - prefixEvelaute(prefixStr.substring(1),stack);

                case '*' : return Character.getNumericValue(prefixStr.charAt(0)) * prefixEvelaute(prefixStr.substring(1),stack);

                case '/' : return Character.getNumericValue(prefixStr.charAt(0)) / prefixEvelaute(prefixStr.substring(1),stack);

            }
        }


        stack.push(prefixStr.charAt(0));
        return prefixEvelaute(prefixStr.substring(1),stack);
    }

    /**
     *  Printing the elements of an array on the screen as in the example below.
     *  input: 1 2 3 4
     *         5 6 7 8
     *         9 10 11 12
     *         13 14 15 16
     *         17 18 19 20
     * Output:  1 2 3 4 8 12 16 20 19 18 17 13 9 5 6 7 11 15 14 10
     * @param arr input
     * @param col coloumn
     * @param row row
     * @param todo if 0 go to right
     *             if 1 go to down
     *             if 2 go to left
     *             if 3 go to up
     * @param size check size equal to array size
     */
    public static void printArray(Integer [][] arr,int col,int row,int todo,int size){
        if (arr[0].length * arr.length > size){
            if(todo == 0 && col < arr[row].length ){
                if(arr[row][col] == 0){
                    --col;
                    ++row;
                    todo = ++todo %4;
                    --size;                }
                else{
                    System.out.print(arr[row][col] + " ");
                    arr[row][col] = 0;
                    ++col;
                    if(col == arr[row].length){
                        todo = ++todo % 4;
                        --col;
                        ++row;
                    }
                }
            }
            else if(todo == 1 && row < arr.length){
                if(arr[row][col] == 0){
                    --row;
                    --col;
                    todo = ++todo %4;
                    --size;                }
                else {
                    System.out.print(arr[row][col] + " ");
                    arr[row][col] = 0;
                    ++row;
                    if(row == arr.length){
                        todo = ++todo % 4;
                        --row;
                        --col;
                    }
                }

            }
            else if(todo == 2 && col >= 0 ){
                if(arr[row][col] == 0){
                    ++col;
                    --row;
                    todo = ++todo %4;
                    --size;                }
                else {
                    System.out.print(arr[row][col] + " ");
                    arr[row][col] = 0;
                    --col;
                    if(col < 0){
                        todo = ++todo % 4;
                        ++col;
                        --row;
                    }
                }

            }
            else if(todo == 3 && row > 0 ){
                if(arr[row][col] == 0){
                    ++col;
                    ++row;
                    todo = ++todo %4;
                    --size;
                }
                else{
                    System.out.print(arr[row][col] + " ");
                    arr[row][col] = 0;
                    --row;
                    if(row == 0){
                        todo = ++todo %4;
                        ++col;
                        ++row;
                    }
                }


            }
            printArray(arr,col,row,todo,++size);
        }


    }
}
