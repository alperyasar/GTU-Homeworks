package Q3;
/**
 * HW5 Part 3 !
 * Assume need to record the number of people in each age for a population. Extended the
 * BinarySearchTree class AgeSearchTree class. Implement AgeData  class to handle both age
 * and number of people at that age values. Keep instances of AgeData in your tree.
 * AgeData Comparable. CompareTo  method of AgeData class will be used and the comparison
 * will be done considering the age only.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-04-29
 */
public class AgeSearchTree<E extends Comparable<E>> extends BinarySearchTree<E> {

    AgeSearchTree(){ }

    @Override
    public AgeData find(AgeData target) {

        return super.find(target);
    }

    @Override
    public boolean add(AgeData item) {
        return super.add(item);
    }

    @Override
    public AgeData delete(AgeData target) {
        return super.delete(target);
    }

    @Override
    public String toString() {
        return super.toString();
    }

    @Override
    public int youngerThan(int age) {
        return super.youngerThan(age);
    }

    @Override
    public int olderThan(int age) {
        return super.olderThan(age);
    }
}
