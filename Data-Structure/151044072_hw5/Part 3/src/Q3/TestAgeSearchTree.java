package Q3;

public class TestAgeSearchTree {
    public static void main(String[] args) {
        //Create an empty age tree
        AgeSearchTree<AgeData> ageTree = new AgeSearchTree<AgeData>();
//Add nodes for some ages, remove method works similarly
        ageTree.add(new AgeData(10));
        ageTree.add(new AgeData(20));
        ageTree.add(new AgeData(5));
        ageTree.add(new AgeData(15));
        ageTree.add(new AgeData(10));

//Create a string representing the tree and print it
        String treeStr = ageTree.toString();
        System.out.println(treeStr);

//Print the number of people younger than 15
        System.out.println(ageTree.youngerThan(15));
//output will be 3
//Find the number of people at any age
        System.out.println(ageTree.find(new AgeData(10)).toString());
//It will print:
//10 - 2
        System.out.println(ageTree.olderThan(15));
//output will be 1

    }
}
