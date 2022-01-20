package Part2;

import java.util.*;

public class DequeClass<E> extends AbstractCollection<E> implements Deque<E> {

    private ElementsInDeque front,rear;
    private ElementsInDeque removedElements;
    private int size;

    private class ElementsInDeque implements ListIterator<E> {
        E elements;
        ElementsInDeque next;
        ElementsInDeque prev;
        // constructors
        ElementsInDeque(){
            elements = null;
            next = null;
            prev = null;
        }
        ElementsInDeque(E elements){
            this.elements = elements;
            this.next = null;
            this.prev= null;
        }
        ElementsInDeque(ElementsInDeque node,E elements){
            this.elements = elements;
            this.next = null;
            this.prev= node;
            node = this;
        }

        /**
         * @return true if has next
         */
        @Override
        public boolean hasNext() {
            if(next != null){
                return true;
            }
            return false;
        }

        /**
         * @return next element
         */
        @Override
        public E next() {
            return elements;
        }

        /**
         * @return true if has previous
         */
        @Override
        public boolean hasPrevious() {
            if(prev != null)
                return true;
            return false;
        }

        @Override
        public E previous() {
            return null;
        }

        @Override
        public int nextIndex() {
            return 0;
        }

        @Override
        public int previousIndex() {
            return 0;
        }

        /**
         * remove this element and connect
         * next to previous
         */
        @Override
        public void remove() {
            ElementsInDeque temp=this;
            if(this.hasPrevious()){
                temp.prev.next = temp.next;

            }
            else if(this.hasNext()){
                removedElements = temp.next;
                removedElements.prev = null;            }
            else
                removedElements = null;
        }

        /**
         * set element
         * @param e element
         */
        @Override
        public void set(E e) {
            elements = e;
        }

        /**
         * add to node new element
         * @param e element
         */
        @Override
        public void add(E e) {
            ElementsInDeque iter = this;
            while (iter.hasNext()){
                iter = iter.next;
            }
            if(iter.elements != null){
                iter.next = new ElementsInDeque(e);
                iter.next.prev = iter;
                iter = iter.next;
            }
            else{
                iter.elements = e;
            }


        }

        /**
         * check if item is deleted before
         * @param e element
         * @return found element
         */
        public ElementsInDeque chechkItem(E e){

            ElementsInDeque iter = this;
            ElementsInDeque temp = this;

            while (iter.hasNext()){
                if(iter.elements == e){
                    return iter;
                }
                iter=iter.next;
            }
            if(iter.elements == e){
                return iter;
            }
            return null;
        }

    }

    /**
     * Constructor
     */
    DequeClass(){
        front = null;
        rear = null;
        removedElements = new ElementsInDeque();

        size = 0;

    }

    /**
     * check if item is deleted before
     * @param e element
     * @param node removedElement
     * @return found deleted element
     */
    private ElementsInDeque itemCheck(E e, ElementsInDeque node){
        ElementsInDeque iter = removedElements;
        while (iter.hasNext()){
            if(iter.elements == e){
                node = iter;
                iter.remove();
                return node;
            }
            iter = iter.next;
        }
        if(iter.elements == e){

            node = iter;
            iter.remove();

            return node;
        }
        return null;
    }
    /**
     * Insert item at the front ıf the deque
     * @param e adding element
     */
    @Override
    public void addFirst(E e) {
     // check this element was removed

       ElementsInDeque iter = removedElements;

       if(iter.chechkItem(e)!= null){
           iter = itemCheck(e,iter);
           if(isEmpty()){
               front = iter;
               rear = front;
           }
           else{
               iter.next = front;
               front.prev=iter;
               front = iter;
           }
       }
       else {
           if(isEmpty()){

               front = new ElementsInDeque(e);
               rear = front;
           }
           else{
               ElementsInDeque temp = new ElementsInDeque(e);
               temp.next = front;
               front.prev= temp;
               front = temp;
           }
       }


    }
    /**
     * Insert item at the rear ıf the deque.
     * @param e adding element
     */
    @Override
    public void addLast(E e) {
        //check removed
        ElementsInDeque iter = removedElements;
        if(iter.chechkItem(e)!= null){
            iter = itemCheck(e,iter);
            rear.next = iter;
            iter.prev=rear;
            rear = iter;
        }
        else{
            ElementsInDeque temp = new ElementsInDeque(rear,e);
            rear.next = temp;
            rear = temp;
        }

    }


    @Override
    public boolean offerFirst(E e) { return false; }

    @Override
    public boolean offerLast(E e) { return false; }


    @Override
    public E removeFirst() { return null; }

    @Override
    public E removeLast() { return null; }

    /**
     * Removes the entry at the front of the deque
     * @return elements
     */
    @Override
    public E pollFirst() {
        if(front== null)
            return null;
        else{
            // take last Removed node and assign removed element
            E tempElement = getFirst();
            removedElements.add(tempElement);
            front= front.next;
            return tempElement;
        }
    }
    /**
     * Removes the entry at the rear of the deque
     * @return elements
     */
    @Override
    public E pollLast() {
        if(front== null)
            return null;
        else{
            // take last Removed node and assign removed element
            E tempElement = getLast();
            removedElements.add(tempElement);
            rear= rear.prev;
            rear.next = null;
            return tempElement;
        }
    }

    /**
     * the entry at the front of the deque
     * @return front element
     */
    @Override
    public E getFirst() {
        return front.elements;
    }
    /**
     * the entry at the last of the deque
     * @return rear element
     */
    @Override
    public E getLast() {
        return rear.elements;
    }

    /**
     * @return the item at the front of the deque
     */
    @Override
    public E peekFirst() {
        if(front == null)
            return null;
        else return front.elements;
    }
    /**
     * @return the item at the rear of the deque
     */
    @Override
    public E peekLast() {
        if(front == null)
            return null;
        else return rear.elements;
    }

    @Override
    public boolean removeFirstOccurrence(Object o) {
        return false;
    }

    @Override
    public boolean removeLastOccurrence(Object o) {
        return false;
    }

    @Override
    public boolean add(E e) {
        return false;
    }

    @Override
    public boolean offer(E e) {
        return false;
    }

    @Override
    public E remove() {
        return null;
    }

    @Override
    public E poll() {
        return null;
    }

    @Override
    public E element() {
        return null;
    }

    @Override
    public E peek() {
        return null;
    }

    @Override
    public boolean addAll(Collection<? extends E> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public void push(E e) {

    }

    @Override
    public E pop() {
        return null;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        if (front == null){
            return true;
        }
        return false;
    }

    @Override
    public Iterator<E> iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }


    @Override
    public Iterator<E> descendingIterator() {
        return null;
    }
}
